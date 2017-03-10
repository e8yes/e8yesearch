#include <vector>
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

void engine::SQLiteDataSource::destroy()
{
        sql << "DELETE FROM document;" << cppdb::exec;
        sql << "DELETE FROM term;" << cppdb::exec;
        sql << "DELETE FROM posting_list;" << cppdb::exec;
}

void engine::SQLiteDataSource::add_documents(const std::vector<Document>& docs)
{
        cppdb::statement stat;

        for (Document doc : docs) {

                stat = sql << "INSERT INTO document(did, url, title) "
                              "VALUES(?, ?, ?);";

                stat.bind(doc.get_id());
                stat.bind(doc.get_url());
                stat.bind(doc.get_heading());

                stat.exec();

                std::vector<Term> terms = doc.get_terms();

                stat = sql << "INSERT INTO term(tid, str, idf) "
                              "VALUES(?, ?, ?);";

                for (Term term : terms) {
                        stat.bind(term.get_id());
                        stat.bind(term.get_content());
                        stat.bind(term.get_frequency());

                        try {
                                stat.exec();
                        } catch (std::exception const &e) {
                        }
                        stat.reset();
                }
        }

        for (Document doc : docs) {
                stat = sql << "INSERT INTO posting_list(tid, did, tf) "
                              "VALUES(?, ?, ?);";
                for (Term term : doc.get_terms()) {
                        stat.bind(term.get_id());
                        stat.bind(doc.get_id());
                        stat.bind(term.get_frequency());

                        try {
                                stat.exec();
                        } catch (std::exception const &e) {
                        }
                        stat.reset();
                }
        }
}

void engine::SQLiteDataSource::find_documents_by_terms(const std::vector<Term>& terms, std::vector<Document>& docs)
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
