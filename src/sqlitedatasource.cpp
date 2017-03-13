#include <vector>
#include <set>
#include <map>
#include <iostream>

#include "sqlitedatasource.h"

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
