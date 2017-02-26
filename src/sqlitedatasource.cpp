#include "sqlitedatasource.h"
#include <vector>

engine::SQLiteDataSource::SQLiteDataSource():
    sql("sqlite3:db=e8yesDB;")
{


}

void engine::SQLiteDataSource::find_documents_by_terms(const std::vector<Term>& terms, std::vector<Document>& docs)
{

}

engine::SQLiteDataSource::~SQLiteDataSource()
{
}
