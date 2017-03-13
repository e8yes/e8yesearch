#include <vector>
#include <set>
#include <iostream>

#include "sqlitedatasource.h"

engine::SQLiteDataSource::SQLiteDataSource():
        sql("sqlite3:db=e8yesDB.db;")
{
        sql << "CREATE TABLE IF NOT EXISTS document(did INTEGER PRIMARY KEY, url VARCHAR(100) NOT NULL, title VARCHAR(100));"  << cppdb::exec;
        sql << "CREATE TABLE IF NOT EXISTS term(tid INTEGER PRIMARY KEY, str VARCHAR(100) UNIQUE NOT NULL, idf INTEGER NOT NULL);" << cppdb::exec;
        sql << "CREATE TABLE IF NOT EXISTS posting_list(tid INTEGER REFERENCES term(tid), "
               "did INTEGER REFERENCES document(did), tf INTEGER NOT NULL, PRIMARY KEY(tid, did));"  << cppdb::exec;
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
        cppdb::statement doc_insert = sql.prepare("INSERT INTO document(did, url, title) "
                                                  "VALUES (?, ?, ?);");
        cppdb::statement term_insert = sql.prepare("INSERT INTO term(tid, str, idf) "
                                                   "VALUES(?, ?, ?);");
        cppdb::statement pl_insert = sql.prepare("INSERT INTO posting_list(tid, did, tf) "
                                                 "VALUES(?, ?, ?);");

        std::set<Term> all_terms;

        // Save documents.
        for (const Document& doc : buffer) {
                doc_insert.bind(doc.get_id());
                doc_insert.bind(doc.get_url());
                doc_insert.bind(doc.get_heading());

                doc_insert.exec();
                doc_insert.reset();

                // Collect terms.
                for (const Term& term: doc.get_terms())
                        all_terms.insert(term);
        }

        // Handle terms.
        for (const Term& term: all_terms) {
                term_insert.bind(term.get_id());
                term_insert.bind(term.get_content());
                term_insert.bind(term.get_idf());

                try {
                        // May be repetition.
                        term_insert.exec();
                } catch (std::exception const &e) {
                }
                term_insert.reset();
        }

        // Handle sparse matrix.
        for (const Document& doc : buffer) {
                for (const Term& term : doc.get_terms()) {
                        pl_insert.bind(term.get_id());
                        pl_insert.bind(doc.get_id());
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
    cppdb::statement stat;
    try {
        for (Term term : terms) {
            stat = sql << "SELECT document.did, url, title FROM posting_list, document, term WHERE document.did = posting_list.did "
                          "AND term.tid = posting_list.tid AND upper(str) = upper(?);";
            stat.bind(term.get_content());
            cppdb::result res = stat.query();
            while (res.next()) {
                docs.push_back(Document(0, res.get<std::string>("url"), "", 0));
            }
            stat.reset();
        }
    } catch (std::exception const &e) {
            std::cout << e.what() << std::endl;
    }
}
