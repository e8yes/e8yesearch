#ifndef SQLITEDATASOURCE_H
#define SQLITEDATASOURCE_H

#include <set>
#include "idatasource.h"
#include <cppdb/frontend.h>

namespace engine
{

class SQLiteDataSource : public IDataSource
{
public:
        SQLiteDataSource();
        ~SQLiteDataSource();

        void 		destroy() override;
        void 		add_documents(const std::vector<Document>& docs) override;
        unsigned 	document_count() override;
        void 		find_documents_by_terms(const std::vector<Term>& terms, std::vector<Document>& docs) override;
        void 		force_transaction() override;
        Term* 		find_term_by_content(const std::string& content) override;
        Term* 		find_term_by_fuzzy_content(const std::string& content) override;

private:
        void load_terms();
        void load_document_count();

        const static int	MAX_BUFFER_SIZE = 1000;
        cppdb::session 		sql;
        std::vector<Document>	buffer;
        std::set<Term>		term_set;
        unsigned		num_docs = 0;
};

}

#endif // SQLITEDATASOURCE_H
