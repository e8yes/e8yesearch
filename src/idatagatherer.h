#ifndef IDATAGATHERER_H
#define IDATAGATHERER_H

#include <string>

namespace engine
{

class IDataGatherer
{
public:
        IDataGatherer();
        virtual ~IDataGatherer();

        virtual void run(const std::string& directory) = 0;
};

}

#endif // IDATAGATHERER_H
