#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <cmath>
#include "sqlitedatasource.h"

void engine::SQLiteDataSource::load_terms()
{
    this->term_set.clear();
    try {
        cppdb::statement stat = sql.prepare("SELECT * from term;");
        cppdb::result res = stat.query();
        while (res.next()) {
            this->term_set.insert(engine::Term(res.get<std::string>("str"), 1, res.get<unsigned>("idf"), 0.0, 0));
        }
    } catch(std::exception const& e) {
        std::cerr << e.what() << std::endl;
    }
}


engine::SQLiteDataSource::SQLiteDataSource():
        sql("sqlite3:db=e8yesDB.db;")
{
    load_terms();
    try {
        sql << "CREATE TABLE IF NOT EXISTS document("
               "did INTEGER PRIMARY KEY AUTOINCREMENT, "
               "hash_id INTEGER NOT NULL, "
               "url VARCHAR(100) NOT NULL, "
               "title VARCHAR(100) NOT NULL,"
               "UNIQUE (hash_id, url));"  << cppdb::exec;
        sql << "CREATE TABLE IF NOT EXISTS term("
               "tid INTEGER PRIMARY KEY AUTOINCREMENT, "
               "hash_id INTEGER NOT NULL, "
               "str VARCHAR(100) NOT NULL, "
               "idf INTEGER NOT NULL,"
               "UNIQUE (hash_id, str));" << cppdb::exec;
        sql << "CREATE TABLE IF NOT EXISTS posting_list("
               "tid INTEGER NOT NULL, "
               "did INTEGER NOT NULL, "
               "tf INTEGER NOT NULL, "
               "PRIMARY KEY (tid, did),"
               "FOREIGN KEY (tid) REFERENCES term(tid) ON DELETE CASCADE,"
               "FOREIGN KEY (did) REFERENCES document(did) ON DELETE CASCADE);"  << cppdb::exec;
    } catch(std::exception const& e) {
        std::cerr << e.what() << std::endl;
    }
}

engine::SQLiteDataSource::~SQLiteDataSource()
{
}

void
engine::SQLiteDataSource::destroy()
{
    sql << "DELETE FROM document;" << cppdb::exec;
    sql << "DELETE FROM term;" << cppdb::exec;
    sql << "DELETE FROM posting_list;" << cppdb::exec;

    term_set.clear();
}

void
engine::SQLiteDataSource::add_documents(const std::vector<Document>& docs)
{
    // Accumulate documents into buffer temporarily.
    for (const Document& doc: docs)
        buffer.push_back(doc);

    if (buffer.size() >= MAX_BUFFER_SIZE)
        force_transaction();
}

void
engine::SQLiteDataSource::force_transaction()
{
    if (buffer.empty())
        return;

    cppdb::transaction guard(sql);
    cppdb::statement doc_insert = sql.prepare("INSERT INTO document(hash_id, url, title) "
                                              "VALUES (?, ?, ?);");
    cppdb::statement term_insert = sql.prepare("INSERT INTO term(hash_id, str, idf) "
                                               "VALUES(?, ?, ?);");
    cppdb::statement pl_insert = sql.prepare("INSERT INTO posting_list(tid, did, tf) "
                                             "VALUES(?, ?, ?);");

    cppdb::statement term_select = sql.prepare("SELECT tid FROM term WHERE hash_id = ? AND str = ?;");
    cppdb::statement doc_select = sql.prepare("SELECT did FROM document WHERE hash_id = ? AND url = ?;");

    std::map<Term, long long> all_terms;
    std::map<Document, long long> all_docs;

    // Save documents.
    for (const Document& doc : buffer) {
        doc_insert.bind(doc.get_hash_id());
        doc_insert.bind(doc.get_url());
        doc_insert.bind(doc.get_heading());

        long long did;
        try {
            doc_insert.exec();
            did = doc_insert.last_insert_id();
        } catch (std::exception const& e) {
            // Repetition, select did from the existing record then.
            doc_select.bind(doc.get_hash_id());
            doc_select.bind(doc.get_url());
            cppdb::result r = doc_select.query(); r.next();
            did = r.get<long long>("did");
            doc_select.reset();
        }
        doc_insert.reset();

        all_docs.insert(std::pair<Document, unsigned>(doc, did));

        // Collect terms.
        for (const Term& term: doc.get_terms())
            all_terms.insert(std::pair<Term, unsigned>(term, 0));
    }

    // Handle terms.
    for (auto it = all_terms.begin(); it != all_terms.end(); ++ it) {
        const Term& term = it->first;
        term_set.insert(term);

        term_insert.bind(term.get_hash_id());
        term_insert.bind(term.get_content());
        term_insert.bind(term.get_idf());

        long long tid;
        try {
            term_insert.exec();
            tid = term_insert.last_insert_id();
        } catch (std::exception const &e) {
            // Repetition, select tid from the existing record then.
            term_select.bind(term.get_hash_id());
            term_select.bind(term.get_content());
            cppdb::result r = term_select.query(); r.next();
            tid = r.get<long long>("tid");
            term_select.reset();
        }
        term_insert.reset();

        it->second = tid;
    }

    // Handle sparse matrix.
    for (const Document& doc: buffer) {
        long long did = all_docs.at(doc);

        for (const Term& term : doc.get_terms()) {
            long long tid = all_terms.at(term);

            pl_insert.bind(tid);
            pl_insert.bind(did);
            pl_insert.bind(term.get_frequency());

            try {
                pl_insert.exec();
            } catch (std::exception const &e) {
            }
            pl_insert.reset();
        }
    }

    guard.commit();

    // Reset buffer.
    buffer.clear();
}

void
engine::SQLiteDataSource::find_documents_by_terms(const std::vector<Term>& terms, std::vector<Document>& docs)
{
    std::map<Document, std::set<Term>> all_docs;

    try {
        cppdb::statement stat = sql.prepare("SELECT D.url, D.title, PL.tf, T.str, T.idf FROM document D, posting_list PL, term T "
                                            "WHERE (T.hash_id = ? AND T.str = ?) AND T.tid = PL.tid AND D.did = PL.did;");

        for (Term term : terms) {
            stat.bind(term.get_hash_id());
            stat.bind(term.get_content());
            cppdb::result res = stat.query();

            while (res.next()) {
                Document doc(res.get<std::string>("url"),
                             res.get<std::string>("title"),
                             0);
                Term term(res.get<std::string>("str"),
                          res.get<unsigned>("tf"),
                          res.get<unsigned>("idf"),
                          .0f,
                          0);

                auto found = all_docs.find(doc);
                if (found != all_docs.end()) {
                    found->second.insert(term);
                } else {
                    std::set<Term> terms;
                    terms.insert(term);
                    all_docs.insert(std::pair<Document, std::set<Term>>(doc, terms));
                }
            }
            stat.reset();
        }
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
    }

    for (auto it = all_docs.begin(); it != all_docs.end(); ++ it) {
        Document doc = it->first;
        for (auto jt = it->second.begin(); jt != it->second.end(); ++ jt) {
            doc.add_term(*jt);
        }
        docs.push_back(doc);
    }
}

engine::Term*
engine::SQLiteDataSource::findTermByContent(const std::string& content)
{
    try {
        cppdb::statement stat = sql.prepare("SELECT * FROM term WHERE term.str = UPPER(?);");
        stat.bind(content);
        cppdb::result res = stat.query();
        if (res.next()) {
            return new engine::Term(content, 1, res.get<unsigned>("idf"), 0.0, 0);
        }
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
    }
    return nullptr;
}

unsigned
calculate_edit_distance(const std::string& a, const std::string& b)
{
    const unsigned a_len = static_cast<unsigned>(a.length()), b_len = static_cast<unsigned>(b.length());

    if (a_len == 0) return b_len;
    if (b_len == 0) return a_len;

    unsigned i, j, i_prv, i_crt, d[2][b_len + 1];

    for (j = 0; j <= b_len; j++) {
        d[0][j] = j;
    }
    i_prv = 0;
    i_crt = 1;
    for (i = 1; i <= a_len; i++) {
        d[i_crt][0] = i;
        for (j = 1; j <= b_len; j++) {
            d[i_crt][j] = std::min(std::min(d[i_prv][j] + 1,d[i_crt][j-1] + 1), d[i_prv][j-1] + (a[i-1] == b[j-1] ? 0 : 1));
        }
        i_prv = i_prv ? 0 : 1;
        i_crt = i_crt ? 0 : 1;
    }

    return d[i_prv][b_len];
}


engine::Term*
engine::SQLiteDataSource::findTermByFuzzyContent(const std::string& content)
{
    unsigned min = 0xFFFFFFFF;
    Term const* min_term = nullptr;
    for (const Term& term : this->term_set) {
        unsigned ed = calculate_edit_distance(content, term.get_content());
        if (ed < min) {
            min_term = &term;
            min = ed;
        }
    }
    return min_term != nullptr ? new Term(*min_term) : nullptr;
}


int
engine::SQLiteDataSource::get_num_doc()
{
    try {
        cppdb::statement stat = sql.prepare("SELECT count(*) AS num from document;");
        cppdb::result res = stat.query();
        res.next();
        return res.get<int>("num");

    } catch(std::exception const& e) {
        std::cerr << e.what() << std::endl;
    }
    return 1;
}












