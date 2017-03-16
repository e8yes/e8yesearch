#include <string>
#include <cmath>
#include "utils.h"
#include "term.h"


engine::Term::Term():
        m_hash_id(0), m_content("")
{
}

engine::Term::Term(const std::string& content):
    m_hash_id(util::hash(util::toupper(content).c_str())), m_content(util::toupper(content))
{
}

engine::Term::Term(const std::string& content, unsigned idf):
    m_hash_id(util::hash(util::toupper(content).c_str())), m_content(content), m_idf(idf)
{
}

engine::term_id_t
engine::Term::get_hash_id() const
{
        return m_hash_id;
}

void
engine::Term::set_idf(unsigned idf)
{
        m_idf = idf;
}

const std::string&
engine::Term::get_content() const
{
        return m_content;
}

unsigned
engine::Term::get_idf() const
{
        return  m_idf;
}

bool
engine::Term::operator<(const Term& term) const
{
        return m_hash_id != term.m_hash_id ? m_hash_id < term.m_hash_id : m_content < term.m_content;
}

std::ostream&
engine::operator<<(std::ostream& os, const Term& term)
{
        os << "Term=[" << term.m_content << "," << term.m_idf << "]";
        return os;
}
