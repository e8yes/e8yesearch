#ifndef IDATASOURCE_H
#define IDATASOURCE_H

#include <set>
#include <vector>
#include "term.h"
#include "document.h"
#include "ibagofwords.h"

namespace engine
{

class IDataSource
{
public:
        IDataSource();
        virtual ~IDataSource();

        virtual void 		destroy() = 0;
        virtual void 		add_document(const Document& doc) = 0;
        virtual unsigned 	document_count() = 0;
        virtual void 		find_documents_by_terms(const std::vector<Term>& terms, std::set<Document>& docs) = 0;
        virtual void 		force_transaction();
        virtual bool    	find_term_by_content(const std::string& content, Term& term) = 0;
        virtual bool 		find_term_by_fuzzy_content(const std::string& content, Term& term) = 0;
        virtual void		fill_bag_of_words(IBagOfWords* bow) = 0;
};

}

#endif // IDATASOURCE_H
