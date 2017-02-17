#ifndef IQUERYPARSER_H
#define IQUERYPARSER_H

#include <string>
#include "textquery.h"

namespace engine
{

class IQueryParser
{
public:
        IQueryParser();
        virtual ~IQueryParser() = 0;
        virtual TextQuery parse(const std::string& squery) = 0;
};

}

#endif // IQUERYPARSER_H
