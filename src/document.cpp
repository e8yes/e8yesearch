#include "utils.h"
#include "document.h"


engine::Document::Document(const std::string& url, const std::string& heading, float importance):
        m_hash_id(util::hash(url.c_str())), m_url(url), m_heading(heading), m_importance(importance)
{
}

engine::Document::~Document()
{
}

engine::doc_id_t
engine::Document::get_hash_id() const
{
        return m_hash_id;
}

const std::string&
engine::Document::get_url() const
{
        return m_url;
}

const std::string&
engine::Document::get_heading() const
{
        return m_heading;
}

float
engine::Document::get_importance() const
{
        return m_importance;
}

void
engine::Document::set_importance(float importance)
{
    this->m_importance = importance;
}

bool
engine::Document::operator<(const Document& rhs) const
{
        return m_hash_id != rhs.m_hash_id ? m_hash_id < rhs.m_hash_id : m_url < rhs.m_url;
}

void
engine::Document::add_term(const Term& term)
{
        m_terms.push_back(term);
}

void
engine::Document::reset_terms()
{
        m_terms.clear();
}

const std::vector<engine::Term>&
engine::Document::get_terms() const
{
        return m_terms;
}

ciere::json::value
engine::Document::to_json() const
{
        ciere::json::value val;
        val["m_url"] = m_url;
        val["m_heading"] = m_heading;
        return val;
}
