#include "spidyqueryhandler.h"
#include <sstream>
#include <xercesc/parsers/XercesDOMParser.hpp>

engine::spidyQueryHandler::spidyQueryHandler()
{

}

engine::TextQuery engine::spidyQueryHandler::parse(const std::string& query)
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


engine::spidyQueryHandler::~spidyQueryHandler()
{
}
