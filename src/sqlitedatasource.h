#ifndef SQLITEDATASOURCE_H
#define SQLITEDATASOURCE_H

#include <map>
#include <set>
#include <cppdb/frontend.h>
#include "idatasource.h"

namespace engine
{

class SQLiteDataSource : public IDataSource
{
public:
        SQLiteDataSource();
        ~SQLiteDataSource();

        void 		destroy() override;
        void 		add_document(const Document& doc) override;
        unsigned 	document_count() override;
        void 		find_documents_by_terms(const std::vector<Term>& terms, std::set<Document>& docs) override;
        void 		force_transaction() override;
        bool 		find_term_by_content(const std::string& content, Term& term) override;
        bool 		find_term_by_fuzzy_content(const std::string& content, Term& term) override;
        void		fill_bag_of_words(IBagOfWords* bow) override;

private:
        void load_terms();
        void load_document_count();

        typedef std::set<Document> 		buffer_t;

        const static int			MAX_BUFFER_SIZE = 2000;
        cppdb::session 				sql;
        buffer_t				buffer;
        std::set<Term>				term_set;
        unsigned				num_docs = 0;
};

}

#endif // SQLITEDATASOURCE_H
