#include "spidyparser.h"
#include <sstream>

engine::spidyParser::spidyParser()
{

}

engine::TextQuery engine::spidyParser::parse(const std::string& query)
{
        TextQuery textQuery;
        std::stringstream sstream;
        sstream << query;

        while (sstream.good()) {
            std::string temp_str;
            sstream >> temp_str;
            textQuery.add_query(Term(temp_str, Term::Heading1, 0));
        }
        return textQuery;
}


engine::spidyParser::~spidyParser()
{
}
