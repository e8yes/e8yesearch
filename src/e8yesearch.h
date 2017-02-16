#ifndef E8YESEARCH_H
#define E8YESEARCH_H

#include <cppcms/service.h>
#include <cppcms/application.h>
#include <cppcms/http_response.h>

namespace web
{

class E8yeSearch : public cppcms::application
{
public:
        E8yeSearch(cppcms::service &srv) :
                cppcms::application(srv)
        {
        }
        virtual void main(std::string url) override;
};

}

#endif // E8YESEARCH_H
