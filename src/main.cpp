#include <cppcms/applications_pool.h>
#include <iostream>
#include "e8yesearch.h"


int main(int argc, char *argv[])
{
        try {
                std::cout << "Starting service..." << std::endl;
                cppcms::service srv(argc, argv);
                srv.applications_pool().mount(cppcms::applications_factory<web::E8yeSearch>());
                std::cout << "Mounted to application pool." << std::endl;
                std::cout << "Running." << std::endl;
                srv.run();
                return 0;
        } catch(std::exception const &e) {
                std::cerr << e.what() << std::endl;
                return -1;
        }
}
