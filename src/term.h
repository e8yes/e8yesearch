#ifndef TERM_H
#define TERM_H
#include <string>

namespace engine
{

class Term
{
public:
        Term(const std::string& content, float locational_weight);
private:
        std::string term;
        unsigned m_freq;
        float m_lweight;
        unsigned m_local_pos;
};

}

#endif // TERM_H
