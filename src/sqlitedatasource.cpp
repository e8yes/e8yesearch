#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <limits>
#include <cmath>
#include "utils.h"
#include "sqlitedatasource.h"

void
engine::SQLiteDataSource::load_terms()
{
        this->term_set.clear();
        try {
                cppdb::statement stat = sql.prepare("SELECT * from term;");
                cppdb::result res = stat.query();
                while (res.next()) {
                        this->term_set.insert(engine::Term(res.get<std::string>("str"),
                                                           res.get<unsigned>("idf")));
                }
        } catch(std::exception const& e) {
                std::cerr << e.what() << std::endl;
        }
}

void
engine::SQLiteDataSource::load_document_count()
{
        try {
                cppdb::statement stat = sql.prepare("SELECT count(*) AS doc_count from document;");
                cppdb::result res = stat.query(); res.next();
                num_docs = res.get<unsigned>("doc_count");
        } catch(std::exception const& e) {
                std::cerr << e.what() << std::endl;
                num_docs = 0;
        }
}

engine::SQLiteDataSource::SQLiteDataSource():
        sql("sqlite3:db=e8yesDB.db;")
{
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
                       "did INTEGER NOT NULL, "
                       "tid INTEGER NOT NULL, "
                       "pos INTEGER NOT NULL, "
                       "lw FLOAT NOT NULL,"
                       "PRIMARY KEY (did, tid, pos),"
                       "FOREIGN KEY (tid) REFERENCES term(tid) ON DELETE CASCADE,"
                       "FOREIGN KEY (did) REFERENCES document(did) ON DELETE CASCADE);"  << cppdb::exec;
                sql << "CREATE TABLE IF NOT EXISTS bag_of_words("
                       "tid INTEGER NOT NULL, "
                       "did INTEGER NOT NULL, "
                       "tf INTEGER NOT NULL, "
                       "PRIMARY KEY (tid, did),"
                       "FOREIGN KEY (tid) REFERENCES term(tid) ON DELETE CASCADE,"
                       "FOREIGN KEY (did) REFERENCES document(did) ON DELETE CASCADE);"  << cppdb::exec;
        } catch(std::exception const& e) {
                std::cerr << e.what() << std::endl;
        }

        load_terms();
        load_document_count();
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
        sql << "DELETE FROM bag_of_words;" << cppdb::exec;

        term_set.clear();
        num_docs = 0;
}

void
engine::SQLiteDataSource::add_document(const Document& doc)
{
        // Accumulate documents into buffer temporarily.
        buffer.insert(doc);

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
        cppdb::statement pl_insert = sql.prepare("INSERT INTO posting_list(tid, did, pos, lw) "
                                                 "VALUES(?, ?, ?, ?);");
        cppdb::statement bow_insert = sql.prepare("INSERT INTO bag_of_words(tid, did, tf) "
                                                  "VALUES(?, ?, ?);");

        cppdb::statement term_select = sql.prepare("SELECT tid FROM term WHERE hash_id = ? AND str = ?;");
        cppdb::statement doc_select = sql.prepare("SELECT did FROM document WHERE hash_id = ? AND url = ?;");

        std::map<Term, long long> batched_terms;
        std::map<Document, long long> batched_docs;

        // Save documents.
        for (const Document& doc: buffer) {
                doc_insert.bind(doc.get_hash_id());
                doc_insert.bind(doc.get_url());
                doc_insert.bind(doc.get_heading());

                long long did;
                try {
                        doc_insert.exec();
                        did = doc_insert.last_insert_id();

                        num_docs ++;
                } catch (std::exception const&) {
                        // Repetition, select did from the existing record then.
                        doc_select.bind(doc.get_hash_id());
                        doc_select.bind(doc.get_url());
                        cppdb::result r = doc_select.query(); r.next();
                        did = r.get<long long>("did");
                        doc_select.reset();
                }
                doc_insert.reset();

                batched_docs.insert(std::pair<Document, unsigned>(doc, did));

                // Collect terms.
                for (const docterm_t& docterm: doc.get_term_info())
                        batched_terms.insert(std::pair<Term, unsigned>(docterm.first, 0));
        }

        // Handle terms.
        for (auto it = batched_terms.begin(); it != batched_terms.end(); ++ it) {
                const Term& term = it->first;
                term_set.insert(term);

                term_insert.bind(term.get_hash_id());
                term_insert.bind(term.get_content());
                term_insert.bind(term.get_idf());

                long long tid;
                try {
                        term_insert.exec();
                        tid = term_insert.last_insert_id();
                } catch (std::exception const &) {
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

        // Handle the posting list and the term-document sparse matrix.
        for (const Document& doc: buffer) {
                long long did = batched_docs.at(doc);

                for (const term_pos_t& termpos: doc.get_terms_pos()) {
                        long long tid = batched_terms.at(termpos.first);

                        pl_insert.bind(tid);
                        pl_insert.bind(did);
                        pl_insert.bind(termpos.second.get_pos());
                        pl_insert.bind(termpos.second.get_weight());

                        try {
                                pl_insert.exec();
                        } catch (std::exception const &) {
                        }
                        pl_insert.reset();
                }

                for (const docterm_t& docterm: doc.get_term_info()) {
                        long long tid = batched_terms.at(docterm.first);

                        bow_insert.bind(tid);
                        bow_insert.bind(did);
                        bow_insert.bind(docterm.second.tf());

                        try {
                                bow_insert.exec();
                        } catch (std::exception const &) {
                        }
                        bow_insert.reset();
                }
        }

        guard.commit();

        // Reset buffer.
        buffer.clear();
}

void
engine::SQLiteDataSource::find_documents_by_terms(const std::vector<Term>& terms, std::set<Document>& docs)
{
        docs.clear();

        try {
                cppdb::statement stat = sql.prepare("SELECT url, title, tf, pos, lw "
                                                    "FROM document D, "
                                                    "           (SELECT BOW.did, BOW.tf FROM bag_of_words BOW, term T "
                                                    "           WHERE (T.hash_id = ? AND T.str = ?) AND T.tid = BOW.tid) AS BOWINFO,"
                                                    "           (SELECT PL.did, PL.pos, PL.lw FROM posting_list PL, term T "
                                                    "           WHERE (T.hash_id = ? AND T.str = ?) AND T.tid = PL.tid) AS PLINFO "
                                                    "WHERE D.did = PLINFO.did AND D.did = BOWINFO.did;");

                for (Term term : terms) {
                        stat.bind(term.get_hash_id());
                        stat.bind(term.get_content());

                        stat.bind(term.get_hash_id());
                        stat.bind(term.get_content());
                        cppdb::result res = stat.query();

                        while (res.next()) {
                                Document doc(res.get<std::string>("url"),
                                             res.get<std::string>("title"),
                                             0);
                                Term curr_term(term.get_content(),
                                               term.get_idf());

                                auto found = docs.find(doc);
                                if (found != docs.end()) {
                                        Document& doc = const_cast<Document&>(*found);
                                        doc.add_term(curr_term, TermPosition(res.get<unsigned>("pos"),
                                                                             res.get<float>("lw")),
                                                     res.get<unsigned>("tf"));
                                } else {
                                        doc.add_term(curr_term, TermPosition(res.get<unsigned>("pos"),
                                                                             res.get<float>("lw")),
                                                     res.get<unsigned>("tf"));
                                        docs.insert(doc);
                                }
                        }
                        stat.reset();
                }
        } catch (std::exception const &e) {
                std::cerr << e.what() << std::endl;
        }
}

bool
engine::SQLiteDataSource::find_term_by_content(const std::string& content, Term& term)
{
        try {
                auto res = term_set.find(Term(content));
                if (res != term_set.end()) {
                        term = *res;
                        return true;
                }
        } catch (std::exception const &e) {
                std::cerr << e.what() << std::endl;
        }
        return false;
}

bool
engine::SQLiteDataSource::find_term_by_fuzzy_content(const std::string& content, Term& term)
{
        unsigned min = std::numeric_limits<unsigned>::max();
        Term const* min_term = nullptr;

        for (const Term& term : this->term_set) {
                unsigned ed = util::ed(content, term.get_content());
                if (ed < min) {
                        min_term = &term;
                        min = ed;
                }
        }

        if (min_term != nullptr && min <= 2) {
                term = *min_term;
                return true;
        } else {
                return false;
        }
}

void
engine::SQLiteDataSource::fill_bag_of_words(IBagOfWords* bow)
{
}

unsigned
engine::SQLiteDataSource::document_count()
{
        return num_docs;
}
