#include "document.h"

engine::Document::Document(const std::string& url, const std::string& heading, float importance):
        m_url(url), m_heading(heading), m_importance(importance)
{
}

const std::string& engine::Document::get_url() const
{
        return m_url;
}

const std::string& engine::Document::get_heading() const
{
        return m_heading;
}

float engine::Document::get_importance() const
{
        return m_importance;
}

bool engine::Document::operator<(const Document& rhs) const
{
        return m_importance < rhs.m_importance;
}
