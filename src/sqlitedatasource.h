#ifndef SQLITEDATASOURCE_H
#define SQLITEDATASOURCE_H
#include "idatasource.h"
#include <cppdb/frontend.h>

namespace engine {

class SQLiteDataSource : public IDataSource
{
private:
    cppdb::session 		sql;
public:
    SQLiteDataSource();
    void find_documents_by_terms(const std::vector<Term>& terms, std::vector<Document>& docs);
    ~SQLiteDataSource();
};
}

#endif // SQLITEDATASOURCE_H
