#ifndef ITEXTSEARCH_H
#define ITEXTSEARCH_H

#include "idatasource.h"
#include "textquery.h"
#include "searchresult.h"

namespace engine
{

class ITextSearch
{
public:
        ITextSearch(const IDataSource& data_source);
        virtual ~ITextSearch() = 0;

        virtual void find(const TextQuery& text, sorted_results_t& result) = 0;
private:
        const IDataSource& m_data_source;
};

};

#endif // ITEXTSEARCH_H
