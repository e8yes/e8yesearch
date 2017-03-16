#ifndef TERM_H
#define TERM_H

#include <string>
#include <map>
#include <ostream>
#include "term.h"

namespace engine
{

typedef uint64_t term_id_t;

class Term
{
        friend std::ostream& operator<<(std::ostream& os, const Term& term);
public:
        enum Location {
                Any,
                Title,		// 0.7
                Heading1,	// 0.68
                Heading2,	// 0.66
                Heading3,	// 0.64
                Heading4,	// 0.62
                Heading5,	// 0.61
                Heading6,	// 0.60
                Section,	// 0.60

                Bold,		// 0.55
                Italic,		// 0.55
                Emphasized,	// 0.55
                Strong,		// 0.55
                List,		// 0.5
                Caption,	// 0.5
                Center,		// 0.5
                Cite,		// 0.5

                Division,	// 0.3
                Paragraph,	// 0.3

                TableRow,	// 0.1

                HyperLink,	// 0.0
        };

        static float positional_weight(Location location)
        {
                switch (location) {
                case Title:
                        return .7f;
                case Heading1:
                        return .68f;
                case Heading2:
                        return .66f;
                case Heading3:
                        return .64f;
                case Heading4:
                        return .62f;
                case Heading5:
                        return .61f;
                case Heading6:
                        return .60f;
                case Section:
                        return .60f;

                case Bold:
                        return .55f;
                case Italic:
                        return .55f;
                case Emphasized:
                        return .55f;
                case Strong:
                        return .55f;
                case List:
                        return .5f;
                case Caption:
                        return .5f;
                case Center:
                        return .5f;
                case Cite:
                        return .5f;

                case Any:
                case Division:
                        return 0.3f;
                case Paragraph:
                        return .3f;

                case TableRow:
                        return .1f;

                case HyperLink:
                        return .0f;
                }
        }

        Term();
        Term(const std::string& content, Location location, unsigned position);
        Term(const std::string& content, unsigned freq, unsigned idf, float locational_weight, unsigned position);


        void 			set_idf(unsigned idf);
        void 			set_tf(unsigned tf);
        void			set_pos(unsigned p);

        term_id_t		get_hash_id() const;
        const std::string& 	get_content() const;
        unsigned 		get_idf() const;
        unsigned 		get_frequency() const;
        float           	compute_tfidf(unsigned n_docs) const;
        unsigned		get_pos() const;
        bool			operator<(const Term& term) const;
private:
        term_id_t		m_hash_id;
        std::string		m_content;
        unsigned 		m_freq = 0;
        unsigned		m_idf = 0;
        float 			m_lweight;
        unsigned 		m_local_pos;
};

std::ostream& operator<<(std::ostream& os, const Term& term);


typedef std::map<Term, unsigned> idf_t;
typedef std::pair<Term, unsigned> idf_entry_t;

}

#endif // TERM_H
