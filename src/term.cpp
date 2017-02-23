#include "term.h"

engine::Term::Term(const std::string& content, float locational_weight):
    term(content), m_lweight(locational_weight)
{
}
