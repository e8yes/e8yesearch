#include <iostream>
#include "e8yesearch.h"


web::E8yeSearch::E8yeSearch(cppcms::service &srv) :
        cppcms::application(srv)
{
        dispatcher().assign("/e8yes*", &E8yeSearch::get, this);
        dispatcher().assign(".*", &E8yeSearch::redirect, this);
}

void
web::E8yeSearch::redirect()
{
        response().set_redirect_header("/pages/e8yes.html");
}

void
web::E8yeSearch::get()
{
        std::cout << "get..." << std::endl;
}

void
web::E8yeSearch::post()
{
        std::cout << "post..." << std::endl;
}
