#ifndef DATASOURCEPRIMITIVE_H
#define DATASOURCEPRIMITIVE_H

#include <string>
#include "idatasource.h"

namespace engine
{
namespace impl
{

class DataSourcePrimitive: public IDataSource
{
public:
        DataSourcePrimitive(const std::string& name);
private:
        const std::string m_name;
};

}
}

#endif // DATASOURCEPRIMITIVE_H
