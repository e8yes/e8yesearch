#include "spidytextsearch.h"
#include "sqlitedatasource.h"
#include <cmath>
#include <set>
#include <algorithm>


engine::SpidyTextSearch::SpidyTextSearch(IDataSource* ds):
        ITextSearch(*ds)
{

}

void
engine::SpidyTextSearch::find(const TextQuery& query, sorted_results_t& result)
{
        std::set<Term> query_terms;
        for (const Term& t: query.query_terms())
                query_terms.insert(t);

        m_data_source.find_documents_by_terms(query.query_terms(), result);

        for (Document& doc : result) {
                for (Term term_in_doc : doc.get_terms()) {
                        auto found = query_terms.find(term_in_doc);
                        if (found != query_terms.end()) {
                                double tf_idf = std::log(term_in_doc.get_frequency()) *
                                                std::log(static_cast<float>(this->m_data_source.document_count())/found->get_idf());
                                doc.set_importance(static_cast<float>(tf_idf));
                        }
                }
        }

        std::sort(result.begin(), result.end(), [] (const Document& a, const Document& b) -> bool {
                return a.get_importance() > b.get_importance();
        });
}
