#include "searchresult.h"

engine::SearchResult::SearchResult(const std::string& url, const std::string& heading, float importance):
        m_url(url), m_heading(heading), m_importance(importance)
{
}

const std::string& engine::SearchResult::get_url() const
{
        return m_url;
}

const std::string& engine::SearchResult::get_heading() const
{
        return m_heading;
}

float engine::SearchResult::get_importance() const
{
        return m_importance;
}

bool engine::SearchResult::operator<(const SearchResult& rhs) const
{
        return m_importance < rhs.m_importance;
}
