#include <algorithm>
#include "textquery.h"


engine::TextQuery::TextQuery():
        Document("", "", .0f)
{

}

std::vector<engine::Term>
engine::TextQuery::query_terms() const
{
        std::vector<engine::Term> terms;
        for (const docterm_t& docterm: get_term_info()) {
                terms.push_back(docterm.first);
        }
        return terms;
}

std::string
engine::TextQuery::to_query_string() const
{
        terms_pos_t termspos = get_terms_pos();
        std::sort(termspos.begin(), termspos.end(), [](const term_pos_t& a, const term_pos_t& b) {
                return a.second.get_pos() < b.second.get_pos();
        });
        std::string s;
        for (const term_pos_t& termpos: termspos) {
                s += termpos.first.get_content() + " ";
        }
        return s;
}
