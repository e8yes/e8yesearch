#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <set>
#include <vector>
#include "ijsonserializable.h"
#include "term.h"

namespace engine
{

struct TermPosition
{
       TermPosition(unsigned p, float lweight):
               p(p), lweight(lweight)
       {
       }

       unsigned get_pos() const
       {
               return p;
       }

       float get_weight() const
       {
               return lweight;
       }

       bool operator<(const TermPosition& rhs) const
       {
               return p < rhs.p;
       }

       unsigned p;
       float	lweight;
};

struct DocTermInfo
{
        DocTermInfo(const TermPosition& p)
        {
                add_pos(p);
        }

        void add_pos(const TermPosition& p)
        {
                pos.insert(p);
        }

        unsigned tf() const
        {
                return freq == 0 ? static_cast<unsigned>(pos.size()) : freq;
        }

        std::set<TermPosition>	pos;
        unsigned		freq = 0;
};

typedef uint64_t 			doc_id_t;
typedef std::map<Term, DocTermInfo>	docterms_t;
typedef std::pair<Term, DocTermInfo>	docterm_t;

typedef std::pair<Term, TermPosition>	term_pos_t;
typedef std::vector<term_pos_t>		terms_pos_t;

class Document: public util::IJsonSerializable
{
public:
        Document(const std::string& url, const std::string& heading, float importance);
        ~Document() override;

        doc_id_t			get_hash_id() const;
        const std::string&		get_url() const;
        const std::string& 		get_heading() const;
        float 				get_importance() const;
        void				set_importance(float importance);
        void                    	add_term(const Term& term, const TermPosition& p);
        void                    	add_term(const Term& term, const TermPosition& p, unsigned freq);
        void				reset_terms();

        const docterms_t& 		get_term_info() const;
        terms_pos_t                     get_terms_pos() const;

        unsigned			get_tf(const Term& term) const;

        ciere::json::value		to_json() const override;

        bool operator<(const Document& rhs) const;

protected:
        uint64_t		m_hash_id;
        std::string 		m_url;
        std::string 		m_heading;
        float 			m_importance;

        docterms_t		m_doc_terms;
};

};

#endif // DOCUMENT_H
