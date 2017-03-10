#include "textquery.h"

engine::TextQuery::TextQuery()
{

}

const std::vector<engine::Term>& engine::TextQuery::get_query() const
{
        return this->query;
}


void engine::TextQuery::add_query(const engine::Term& term)
{
        this->query.push_back(term);
}
