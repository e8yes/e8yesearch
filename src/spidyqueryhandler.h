#ifndef SPIDYPARSER_H
#define SPIDYPARSER_H

#include "idatasource.h"
#include "iqueryparser.h"


namespace engine
{

class SpidyQueryHandler: public IQueryParser
{
public:
        SpidyQueryHandler(IDataSource* ds);
        ~SpidyQueryHandler();
        TextQuery parse(const std::string& squery);
private:
        IDataSource*	m_ds;
};

}
#endif // SPIDYPARSER_H
