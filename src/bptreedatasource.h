#ifndef BPTREEDATASOURCE_H
#define BPTREEDATASOURCE_H

#include <set>
#include "term.h"
#include "document.h"

#include "idatasource.h"

namespace engine
{

class BPTreeDataSource : public IDataSource
{
public:
        BPTreeDataSource();
        ~BPTreeDataSource() override;

        void 		destroy() override;
        void 		add_document(const Document& doc) override;
        void 		find_documents_by_terms(const std::vector<Term>& terms, std::set<Document>& docs) override;
        unsigned 	document_count() override;
        void 		force_transaction() override;
        bool 		find_term_by_content(const std::string& content, Term& term) override;
        bool 		find_term_by_fuzzy_content(const std::string& content, Term& term) override;
        void		fill_bag_of_words(IBagOfWords* bow) override;
private:
        struct InternalData;
        InternalData*   m_dataimpl;
};

}

#endif // BPTREEDATASOURCE_H
