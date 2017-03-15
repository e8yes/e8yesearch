#include <iostream>
#include <cppcms/applications_pool.h>
#include <booster/intrusive_ptr.h>
#include "appweb.h"


int main(int argc, char *argv[])
{
        try {
                std::cout << "Starting service..." << std::endl;
                cppcms::service srv(argc, argv);
                booster::intrusive_ptr<web::E8yeSearch> app = new web::E8yeSearch(srv);
                srv.applications_pool().mount(app);
                std::cout << "Mounted to application pool." << std::endl;
                std::cout << "Running." << std::endl;
                srv.run();
                return 0;
        } catch(std::exception const &e) {
                std::cerr << e.what() << std::endl;
                return -1;
        }
}
