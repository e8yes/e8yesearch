#ifndef SQLITEDATASOURCE_H
#define SQLITEDATASOURCE_H


#include "idatasource.h"
#include <cppdb/frontend.h>

namespace engine
{

class SQLiteDataSource : public IDataSource
{
public:
        SQLiteDataSource();
        ~SQLiteDataSource();

        void destroy() override;
        void add_documents(const std::vector<Document>& docs) override;
        void find_documents_by_terms(const std::vector<Term>& terms, std::vector<Document>& docs) override;
        void force_transaction() override;

private:
        const static int	MAX_BUFFER_SIZE = 1000;
        cppdb::session 		sql;
        std::vector<Document>	buffer;
};

}

#endif // SQLITEDATASOURCE_H
