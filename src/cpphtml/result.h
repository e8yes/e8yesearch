#ifndef RESULT_H
#define RESULT_H


#include <string>
#include <cppcms/view.h>

#include "../itextsearch.h"
#include "../document.h"


namespace result
{

struct result_documents: public cppcms::base_content
{
        engine::sorted_results_t docs;
        std::string query;
};

}

#endif // RESULT_H
