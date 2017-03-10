#ifndef SPIDYTEXTSEARCH_H
#define SPIDYTEXTSEARCH_H

#include "idatasource.h"
#include "itextsearch.h"

namespace engine {
class spidyTextSearch:public ITextSearch
{
public:
    spidyTextSearch(IDataSource* ds);
    void find(const TextQuery& text, sorted_results_t& result);
};
}

#endif // SPIDYTEXTSEARCH_H
