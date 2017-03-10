#include "spidytextsearch.h"
#include "sqlitedatasource.h"

engine::spidyTextSearch::spidyTextSearch(IDataSource* ds):
    ITextSearch(*ds)
{

}

void engine::spidyTextSearch::find(const TextQuery& text, sorted_results_t& result)
{
    m_data_source.find_documents_by_terms(text.get_query(), result);
}
