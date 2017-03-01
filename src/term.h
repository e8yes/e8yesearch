#ifndef TERM_H
#define TERM_H

#include <string>
#include <map>
#include <ostream>

namespace engine
{

typedef uint64_t term_id_t;
typedef std::map<term_id_t, unsigned> idf_t;
typedef std::pair<term_id_t, unsigned> idf_entry_t;

class Term
{
        friend std::ostream& operator<<(std::ostream& os, const Term& term);
public:
        Term(const std::string& content, float locational_weight, unsigned position);
        Term(term_id_t id, const std::string& content, unsigned freq, unsigned idf, float locational_weight, unsigned position);

        term_id_t		get_id() const;
        void 			set_idf(unsigned idf);
        void 			set_tf(unsigned tf);
        const std::string& 	get_content() const;
        unsigned 		get_frequency() const;
        float           	compute_tfidf(unsigned n_docs) const;
        unsigned		get_position() const;
        bool			operator<(const Term& term) const;
private:
        const term_id_t		m_id;
        const std::string	m_content;
        unsigned 		m_freq = 0;
        unsigned		m_idf = 0;
        const float 		m_lweight;
        const unsigned 		m_local_pos;
};

std::ostream& operator<<(std::ostream& os, const Term& term);

}

#endif // TERM_H
