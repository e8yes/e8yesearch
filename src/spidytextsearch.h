#ifndef SPIDYTEXTSEARCH_H
#define SPIDYTEXTSEARCH_H

#include "idatasource.h"
#include "itextsearch.h"

namespace engine
{

class SpidyTextSearch:public ITextSearch
{
public:
        SpidyTextSearch(IDataSource* ds);
        void	find(const TextQuery& text, sorted_results_t& result);
};

}

#endif // SPIDYTEXTSEARCH_H
