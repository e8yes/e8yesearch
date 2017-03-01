#include "sqlitedatasource.h"
#include <vector>

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
}

void engine::SQLiteDataSource::add_documents(const std::vector<Document>& docs)
{
}

void engine::SQLiteDataSource::find_documents_by_terms(const std::vector<Term>& terms, std::vector<Document>& docs)
{

}
