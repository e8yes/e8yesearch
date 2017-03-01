#ifndef TERM_H
#define TERM_H

#include <string>
#include <ostream>

namespace engine
{

class Term
{
        friend std::ostream& operator<<(std::ostream& os, const Term& term);
public:
        Term(const std::string& content, float locational_weight, unsigned position);
        Term(uint64_t id, const std::string& content, unsigned freq, unsigned idf, float locational_weight, unsigned position);

        uint64_t		get_id() const;
        void 			inc_idf();
        void 			inc_tf();
        const std::string& 	get_content() const;
        unsigned 		get_frequency() const;
        float           	compute_tfidf(unsigned n_docs) const;
        unsigned		get_position() const;
        bool			operator<(const Term& term) const;
private:
        const uint64_t		m_id;
        const std::string	m_content;
        unsigned 		m_freq = 0;
        unsigned		m_idf = 0;
        const float 		m_lweight;
        const unsigned 		m_local_pos;
};

std::ostream& operator<<(std::ostream& os, const Term& term);

}

#endif // TERM_H
