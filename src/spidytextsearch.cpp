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
engine::SpidyTextSearch::filter(const TextQuery& query, sorted_results_t& results)
{
}

void
engine::SpidyTextSearch::rank(const TextQuery& query, sorted_results_t& results)
{
        const docterms_t& qterms = query.get_term_info();

        for (Document& doc: results) {
                double importance = .0f;
                for (const docterm_t& term_in_doc: doc.get_term_info()) {
                        auto found = qterms.find(term_in_doc.first);
                        if (found != qterms.end()) {
                                double tf_idf = std::log(term_in_doc.second.tf()) *
                                                std::log(static_cast<float>(this->m_data_source.document_count())/found->first.get_idf());
                                importance += tf_idf;
                        }
                }
                doc.set_importance(static_cast<float>(importance));
        }
}

void
engine::SpidyTextSearch::find(const TextQuery& query, sorted_results_t& result)
{
        result.clear();

        std::set<Document> related_docs;
        m_data_source.find_documents_by_terms(query.query_terms(), related_docs);
        result.insert(result.end(), related_docs.begin(), related_docs.end());

        filter(query, result);
        rank(query, result);
        std::sort(result.begin(), result.end(), [] (const Document& a, const Document& b) -> bool {
                return a.get_importance() > b.get_importance();
        });
}
