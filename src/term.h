#ifndef TERM_H
#define TERM_H
#include <string>

namespace engine
{

class Term
{
public:
        Term(const std::string& content, float locational_weight, unsigned position);
        void 			inc_idf();
        void 			inc_tf();
        const std::string& 	content() const;
        unsigned 		frequency() const;
        float			tfidf(unsigned n_docs) const;
        unsigned		position() const;
        bool			operator<(const Term& term) const;
private:
        std::string 	m_content;
        unsigned 	m_freq = 0;
        unsigned	m_idf = 0;
        float 		m_lweight;
        unsigned 	m_local_pos;
};

}

#endif // TERM_H
