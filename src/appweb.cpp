#include <map>
#include <regex>
#include <iostream>
#include <sstream>
#include <json/value.hpp>
#include <json/io.hpp>
#include "cpphtml/result.h"
#include "appweb.h"


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

void
to_json(const engine::sorted_results_t& docs, ciere::json::value& json)
{
        json = ciere::json::array();
        for (unsigned i = 0; i < docs.size(); i ++) {
                json[static_cast<int>(i)] = docs[i].to_json();
        }
}


web::E8yeSearch::E8yeSearch(cppcms::service &srv) :
        cppcms::application(srv)
{
        dispatcher().assign("", &E8yeSearch::search, this);
        dispatcher().assign("/Tunnel", &E8yeSearch::tunnel, this);
}

void
web::E8yeSearch::search()
{
        if (request().request_method() == "POST") {
                // Search.
                const std::string& query = request().post("query");
                engine::sorted_results_t docs;
                app.search(query, docs);

                // Render.
                ciere::json::value json;
                ::to_json(docs, json);
                std::stringstream ss;
                ss << json;

                result::result_documents page;
                ss >> page.json_docs;

                render("result_documents", page);
        } else {
                // Home.
                response().set_redirect_header("/pages/e8yes.html");
        }
}

void
web::E8yeSearch::tunnel()
{
        if (request().request_method() == "POST") {
                // Tunnel.
                const std::string& descriptor = request().post("descriptor");
                app.tunnel_local(descriptor);
        } else {
                response().out() << app.progress(App::Task::Tunnel);
        }
}
