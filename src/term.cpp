#include <string>
#include <cmath>
#include "utils.h"
#include "term.h"


static const std::locale loc;

static std::string toupper(const std::string& content)
{
        std::string upper;
        upper.resize(content.size());
        for (unsigned i = 0; i < content.size();i ++) {
                upper[i] = std::toupper(content[i], loc);
        }
        return upper;
}

engine::Term::Term(const std::string& content, Location location, unsigned position):
    m_hash_id(util::hash(toupper(content).c_str())), m_content(toupper(content)), m_lweight(positional_weight(location)), m_local_pos(position)
{
}

engine::Term::Term(const std::string& content, unsigned freq, unsigned idf, float locational_weight, unsigned position):
    m_hash_id(util::hash(toupper(content).c_str())), m_content(content), m_freq(freq), m_idf(idf), m_lweight(locational_weight), m_local_pos(position)
{
}

engine::term_id_t
engine::Term::get_hash_id() const
{
        return m_hash_id;
}

void
engine::Term::set_tf(unsigned tf)
{
        m_freq = tf;
}

void
engine::Term::set_pos(unsigned p)
{
        m_local_pos = p;
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
engine::Term::get_pos() const
{
        return m_local_pos;
}

bool
engine::Term::operator<(const Term& term) const
{
        return m_hash_id != term.m_hash_id ? m_hash_id < term.m_hash_id : m_content < term.m_content;
}

std::ostream&
engine::operator<<(std::ostream& os, const Term& term)
{
        os << "Term=[" << term.m_content << "," << term.m_freq << "," << term.m_idf << "," << term.m_local_pos << "," << term.m_lweight << "]";
        return os;
}
