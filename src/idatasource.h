#ifndef IDATASOURCE_H
#define IDATASOURCE_H

#include <vector>
#include "term.h"
#include "document.h"

namespace engine
{

class IDataSource
{
public:
        IDataSource();
        virtual ~IDataSource();

        virtual void 		destroy() = 0;
        virtual void 		add_documents(const std::vector<Document>& docs) = 0;
        virtual unsigned 	document_count() = 0;
        virtual void 		find_documents_by_terms(const std::vector<Term>& terms, std::vector<Document>& docs) = 0;
        virtual void 		force_transaction();
        virtual Term* 		find_term_by_content(const std::string& content) = 0;
        virtual Term* 		find_term_by_fuzzy_content(const std::string& content) = 0;
};

}

#endif // IDATASOURCE_H
