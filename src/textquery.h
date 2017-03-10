#ifndef TEXTQUERY_H
#define TEXTQUERY_H
#include <vector>
#include "term.h"

namespace engine{
class TextQuery
{
public:
        TextQuery();

        const std::vector<Term>& get_query() const;
        void add_query(const Term& term);

private:
        std::vector<Term> query;
};

}
#endif // TEXTQUERY_H
