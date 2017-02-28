#include "sqlitedatasource.h"
#include <vector>

engine::SQLiteDataSource::SQLiteDataSource():
        sql("sqlite3:db=e8yesDB;")
{
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
