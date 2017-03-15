#include <algorithm>
#include "textquery.h"


engine::TextQuery::TextQuery()
{

}

const std::vector<engine::Term>&
engine::TextQuery::query_terms() const
{
        return terms;
}


void
engine::TextQuery::add_term(const engine::Term& term)
{
        terms.push_back(term);
}


std::string
engine::TextQuery::to_query_string() const
{
        std::vector<Term> ts = terms;
        std::sort(ts.begin(), ts.end(), [](const Term& a, const Term& b) {
                return a.get_pos() < b.get_pos();
        });
        std::string s;
        for (const Term& term: ts) {
                s += term.get_content() + " ";
        }
        return s;
}
