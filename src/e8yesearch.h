#ifndef E8YESEARCH_H
#define E8YESEARCH_H

#include <set>

#include <cppcms/service.h>
#include <cppcms/application.h>
#include <cppcms/applications_pool.h>

#include <cppcms/url_dispatcher.h>

#include <cppcms/http_response.h>
#include <cppcms/http_request.h>
#include <cppcms/http_context.h>


namespace web
{

class E8yeSearch : public cppcms::application
{
public:
        E8yeSearch(cppcms::service &srv);
private:
        void redirect();
        void get();
        void post();

        typedef std::set<booster::shared_ptr<cppcms::http::context>> waiters_type;
        waiters_type waiters;
};

}

#endif // E8YESEARCH_H
