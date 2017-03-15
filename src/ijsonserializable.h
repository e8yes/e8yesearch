#ifndef IJSONSERIALIZABLE_H
#define IJSONSERIALIZABLE_H

#include <json/value.hpp>

namespace engine
{

namespace util
{

class IJsonSerializable
{
public:
        IJsonSerializable();
        virtual ~IJsonSerializable();
        virtual ciere::json::value to_json() const = 0;
};

}

}


#endif // IJSONSERIALIZABLE_H
