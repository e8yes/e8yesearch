#include <string>
#include <cmath>
#include "utils.h"
#include "term.h"

engine::Term::Term(const std::string& content, float locational_weight, unsigned position):
    m_id(util::hash(content.c_str())), m_content(content), m_lweight(locational_weight), m_local_pos(position)
{
}

engine::Term::Term(uint64_t id, const std::string& content, unsigned freq, unsigned idf, float locational_weight, unsigned position):
    m_id(id), m_content(content), m_freq(freq), m_idf(idf), m_lweight(locational_weight), m_local_pos(position)
{
}

engine::term_id_t
engine::Term::get_id() const
{
        return m_id;
}

void
engine::Term::set_tf(unsigned tf)
{
        m_freq = tf;
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
engine::Term::get_frequency() const
{
        return m_freq;
}

float
engine::Term::compute_tfidf(unsigned n_docs) const
{
        return static_cast<float>(m_freq)*std::log2(static_cast<float>(n_docs)/m_idf);
}

unsigned
engine::Term::get_position() const
{
        return m_local_pos;
}

bool
engine::Term::operator<(const Term& term) const
{
        return m_content < term.m_content;
}

std::ostream&
engine::operator<<(std::ostream& os, const Term& term)
{
        os << "Term=[" << term.m_content << "," << term.m_freq << "," << term.m_idf << "," << term.m_local_pos << "," << term.m_lweight << "]";
        return os;
}
