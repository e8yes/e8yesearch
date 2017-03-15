#ifndef RESULT_H
#define RESULT_H

#include <cppcms/view.h>
#include <string>

namespace result
{

struct result_documents: public cppcms::base_content
{
        std::string json_docs;
};

}

#endif // RESULT_H
