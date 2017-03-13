#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <vector>
#include "term.h"

namespace engine
{

typedef uint64_t doc_id_t;

class Document
{
public:
        Document(const std::string& url, const std::string& heading, float importance);

        doc_id_t			get_hash_id() const;
        const std::string&		get_url() const;
        const std::string& 		get_heading() const;
        float 				get_importance() const;
        void				set_importance(float importance);
        void                    	add_term(const Term& term);
        void				reset_terms();
        const std::vector<Term>& 	get_terms() const;

        bool operator<(const Document& rhs) const;
private:
        uint64_t		m_hash_id;
        std::string 		m_url;
        std::string 		m_heading;
        float 			m_importance;
        std::vector<Term> 	m_terms;
};

};

#endif // DOCUMENT_H
