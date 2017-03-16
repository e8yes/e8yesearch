#ifndef TEXTQUERY_H
#define TEXTQUERY_H

#include <set>
#include <vector>
#include "term.h"
#include "document.h"


namespace engine
{

class TextQuery: public Document
{
public:
        TextQuery();
        std::vector<Term>		query_terms() const;
        std::string			to_query_string() const;
};

}

#endif // TEXTQUERY_H
