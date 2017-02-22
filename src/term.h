#ifndef TERM_H
#define TERM_H

namespace engine
{

class Term
{
public:
        Term();
private:
        unsigned m_freq;
        float m_weight;
        unsigned m_local_pos;
};

}

#endif // TERM_H
