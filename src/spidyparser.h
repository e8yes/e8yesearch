#ifndef SPIDYPARSER_H
#define SPIDYPARSER_H
#include "iqueryparser.h"

namespace engine {
class spidyParser:public IQueryParser
{
public:
    spidyParser();
    ~spidyParser();
    TextQuery parse(const std::string& squery);
};
}
#endif // SPIDYPARSER_H
