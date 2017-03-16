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

const engine::docterms_t&
engine::Document::get_term_info() const
{
        return m_doc_terms;
}

engine::terms_pos_t
engine::Document::get_terms_pos() const
{
        terms_pos_t tpos;
        for (const docterm_t& docterm: m_doc_terms) {
                const Term& term = docterm.first;
                for (const TermPosition& pos: docterm.second.pos) {
                        tpos.push_back(term_pos_t(term, pos));
                }
        }
        return tpos;
}

unsigned
engine::Document::get_tf(const Term& term) const
{
        auto iterm = m_doc_terms.find(term);
        return iterm != m_doc_terms.end() ? iterm->second.tf(): 0;
}

void
engine::Document::add_term(const Term& term, const TermPosition& pos)
{
        auto iterm = m_doc_terms.find(term);
        if (iterm != m_doc_terms.end()) {
                iterm->second.add_pos(pos);
                // This cast is safe since term must have the same key, as iterm as the execution reaches this branch.
                static_cast<engine::Term>(iterm->first) = term;
        } else {
                m_doc_terms.insert(docterm_t(term, DocTermInfo(pos)));
        }
}

void
engine::Document::add_term(const Term& term, const TermPosition& p, unsigned freq)
{
        add_term(term, p);
        m_doc_terms.at(term).freq = freq;
}

void
engine::Document::reset_terms()
{
        m_doc_terms.clear();
}

ciere::json::value
engine::Document::to_json() const
{
        ciere::json::value val;
        val["m_url"] = m_url;
        val["m_heading"] = m_heading;
        return val;
}
