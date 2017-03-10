#ifndef BPTREEDATASOURCE_H
#define BPTREEDATASOURCE_H

#include "idatasource.h"


namespace engine
{


class BPTreeDataSource : public IDataSource
{
public:
        BPTreeDataSource();
        ~BPTreeDataSource() override;

        void destroy() override;
        void add_documents(const std::vector<Document>& docs) override;
        void find_documents_by_terms(const std::vector<Term>& terms, std::vector<Document>& docs) override;
        void force_transaction() override;
private:
};

}

#endif // BPTREEDATASOURCE_H
