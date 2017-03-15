#include "spidyqueryhandler.h"
#include <sstream>

engine::spidyQueryHandler::spidyQueryHandler()
{

}

engine::TextQuery engine::spidyQueryHandler::parse(const std::string& query)
{
        TextQuery textQuery;
        std::stringstream sstream;
        sstream << query;

        unsigned i = 0;
        while (sstream.good()) {
                std::string temp_str;
                sstream >> temp_str;
                textQuery.add_term(Term(temp_str, Term::Heading1, i ++));
        }
        return textQuery;
}


engine::spidyQueryHandler::~spidyQueryHandler()
{
}
