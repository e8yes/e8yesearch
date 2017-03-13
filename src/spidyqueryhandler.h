#ifndef SPIDYPARSER_H
#define SPIDYPARSER_H
#include "iqueryparser.h"

namespace engine {
class spidyQueryHandler:public IQueryParser
{
public:
    spidyQueryHandler();
    ~spidyQueryHandler();
    TextQuery parse(const std::string& squery);
};
}
#endif // SPIDYPARSER_H
