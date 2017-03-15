#ifndef ITEXTSEARCH_H
#define ITEXTSEARCH_H

#include <vector>
#include "idatasource.h"
#include "textquery.h"
#include "document.h"

namespace engine
{

typedef std::vector<Document> sorted_results_t;

class ITextSearch
{
public:
        ITextSearch(IDataSource& data_source);
        virtual ~ITextSearch();
        virtual void find(const TextQuery& text, sorted_results_t& result) = 0;
protected:
        IDataSource& m_data_source;
};

};

#endif // ITEXTSEARCH_H
