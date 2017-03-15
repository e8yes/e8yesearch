#include <map>
#include <regex>
#include <iostream>
#include "e8yesearch.h"


std::map<std::string, std::string>
parse_query_string(const std::string& query)
{
        std::map<std::string, std::string> data;
        std::regex pattern("([\\w+%]+)=([^&]*)");
        auto words_begin = std::sregex_iterator(query.begin(), query.end(), pattern);
        auto words_end = std::sregex_iterator();

        for (std::sregex_iterator i = words_begin; i != words_end; i++) {
                std::string key = (*i)[1].str();
                std::string value = (*i)[2].str();
                data[key] = value;
        }

        return data;
}

web::E8yeSearch::E8yeSearch(cppcms::service &srv) :
        cppcms::application(srv)
{
        dispatcher().assign("", &E8yeSearch::search, this);
        dispatcher().assign("Tunnel", &E8yeSearch::tunnel, this);
}

void
web::E8yeSearch::search()
{
        const std::string& query_string = request().query_string();
        std::map<std::string, std::string> query = ::parse_query_string(query_string);
        auto qit = query.find("query");

        if (!query.empty() && qit != query.end() && !qit->second.empty()) {
                response().out() << "GET Request...";
        } else {
                // Home.
                response().set_redirect_header("/pages/e8yes.html");
        }
}

void
web::E8yeSearch::tunnel()
{
}
