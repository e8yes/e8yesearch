#include "spidytextsearch.h"
#include "sqlitedatasource.h"
#include <cmath>
#include <set>
#include <algorithm>

engine::spidyTextSearch::spidyTextSearch(IDataSource* ds):
    ITextSearch(*ds)
{

}

void engine::spidyTextSearch::find(const TextQuery& text, sorted_results_t& result)
{
    m_data_source.find_documents_by_terms(text.get_query(), result);
    std::set<Term> query_terms;
    for (Term query_term : text.get_query()) {
        Term* term = this->m_data_source.findTermByContent(query_term.get_content());
        if (term != nullptr)
            query_terms.insert(*term);
    }

    for (Document& doc : result) {
        for (Term term_in_doc : doc.get_terms()) {
            auto found = query_terms.find(term_in_doc);
            if (found != query_terms.end()) {
                float tf_idf = std::log(term_in_doc.get_frequency()) * std::log(found->get_idf());
                doc.set_importance(tf_idf);
            }
        }
    }

    std::sort(result.begin(), result.end(), [] (const Document& a, const Document& b) -> bool {
        return a.get_importance() > b.get_importance();
    });
}
