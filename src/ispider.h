#ifndef ISPIDER_H
#define ISPIDER_H


#include <string>
#include "term.h"
#include "document.h"

namespace engine
{

namespace support
{

class ITokenIterator
{
public:
        virtual ~ITokenIterator();
        virtual bool 		has_next() const = 0;
        virtual term_pos_t	next() = 0;
};

class IDocumentIterator
{
public:
        virtual ~IDocumentIterator();
        virtual std::string     get_descriptor() const = 0;
        virtual bool 		has_next() const = 0;
        virtual ITokenIterator* parse() = 0;
};

class ISpider
{
public:
        ISpider();
        virtual ~ISpider();
        virtual IDocumentIterator* crawl(const std::string& directory) = 0;
};

}

}

#endif // ISPIDER_H
