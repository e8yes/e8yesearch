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
        virtual void find_documents_by_terms(const std::vector<Term>& terms, std::vector<Document>& docs) = 0;
};

}

#endif // IDATASOURCE_H
