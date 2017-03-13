#ifndef SPIDY_H
#define SPIDY_H

#include <vector>
#include <string>
#include <xercesc/dom/DOM.hpp>
#include "ispider.h"

namespace engine {

namespace support {

class SpidyTokenIterator: public ITokenIterator
{
public:
        SpidyTokenIterator();
        ~SpidyTokenIterator() override;

        bool 	has_next() const override;
        Term 	next() override;

        void 	add(const std::string& token);

private:
        unsigned 			current_position = 0;
        std::vector<std::string> 	tokens;
};

class SpidyDocIterator: public IDocumentIterator
{
public:
        SpidyDocIterator();
        ~SpidyDocIterator() override;

        void 			add(std::string file_name);
        std::string             get_descriptor() const override;
        bool 			has_next() const override;
        ITokenIterator* 	parse() override;

private:
        xercesc::DOMLSParser*	parser;
        unsigned 			current_position = 0;
        std::vector<std::string> 	file_names;
};

class Spidy: public ISpider
{
public:
        IDocumentIterator* crawl(const std::string& directory) override;
        ~Spidy() override;
};

}

}

#endif // SPIDY_H
