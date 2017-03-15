#ifndef TEXTQUERY_H
#define TEXTQUERY_H
#include <vector>
#include "term.h"

namespace engine{
class TextQuery
{
public:
        TextQuery();

        const std::vector<Term>& 	query_terms() const;
        void 				add_term(const Term& term);
        std::string			to_query_string() const;
private:
        std::vector<Term> 		terms;
};

}
#endif // TEXTQUERY_H
