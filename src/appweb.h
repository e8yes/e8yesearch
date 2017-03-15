#ifndef APPWEB_H
#define APPWEB_H

#include <set>

#include <cppcms/service.h>
#include <cppcms/application.h>
#include <cppcms/applications_pool.h>

#include <cppcms/url_dispatcher.h>

#include <cppcms/http_response.h>
#include <cppcms/http_request.h>
#include <cppcms/http_context.h>

#include "app.h"


namespace web
{

typedef std::set<booster::shared_ptr<cppcms::http::context>> waiters_type;

class E8yeSearch : public cppcms::application
{
public:
        E8yeSearch(cppcms::service &srv);
private:
        void search();
        void tunnel();

        waiters_type 	waiters;
        App		app;
};

}

#endif // APPWEB_H
