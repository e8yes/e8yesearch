#include <string>
#include <cmath>
#include "term.h"

engine::Term::Term(const std::string& content, float locational_weight, unsigned position):
    m_content(content), m_lweight(locational_weight), m_local_pos(position)
{
}

void engine::Term::inc_tf()
{
        m_freq ++;
}

void engine::Term::inc_idf()
{
        m_idf ++;
}

const std::string& engine::Term::content() const
{
        return m_content;
}

unsigned engine::Term::frequency() const
{
        return m_freq;
}

float engine::Term::tfidf(unsigned n_docs) const
{
        return static_cast<float>(m_freq)*std::log2(static_cast<float>(n_docs)/m_idf);
}

unsigned engine::Term::position() const
{
        return m_local_pos;
}

bool engine::Term::operator<(const Term& term) const
{
        return m_content < term.m_content;
}
