#include "spidytextsearch.h"
#include "sqlitedatasource.h"
#include <cmath>
#include <set>
#include <algorithm>

engine::SpidyTextSearch::SpidyTextSearch(IDataSource* ds):
        ITextSearch(*ds)
{

}

engine::TextQuery
engine::SpidyTextSearch::find(const TextQuery& text, sorted_results_t& result)
{
        const std::vector<Term>& original = text.query_terms();
        std::set<Term> query_terms;
        for (const Term& query_term : original) {
                Term* term = this->m_data_source.find_term_by_content(query_term.get_content());

                if (term == nullptr)
                        term = this->m_data_source.find_term_by_fuzzy_content(query_term.get_content());

                if (term != nullptr) {
                        term->set_pos(query_term.get_pos());
                        query_terms.insert(*term);
                }

                delete term;
        }
        std::vector<Term> query_fixed(query_terms.begin(), query_terms.end());
        m_data_source.find_documents_by_terms(query_fixed, result);

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

        // Reconstruct query.
        TextQuery query;
        for (const Term& term: query_terms) {
                query.add_term(term);
        }
        return query;
}
