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
        void                    	add_term(const Term& term);
        void				reset_terms();
        const std::vector<Term>& 	get_terms() const;

        bool operator<(const Document& rhs) const;
private:
        const uint64_t		m_hash_id;
        const std::string 	m_url;
        const std::string 	m_heading;
        const float 		m_importance;
        std::vector<Term> 	m_terms;
};

};

#endif // DOCUMENT_H
