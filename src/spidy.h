#ifndef SPIDY_H
#define SPIDY_H
#include "ispider.h"
#include <vector>
#include <string>

namespace engine {

namespace support {

class SpidyTokenIterator: public ITokenIterator
{
private:
        unsigned current_position;
        std::vector<std::string> tokens;
public:
        SpidyTokenIterator();
        ~SpidyTokenIterator() override;

        void add(std::string token);

        bool has_next() const override;
        Term next() override;

};

class SpidyDocIterator: public IDocumentIterator
{
private:
        unsigned current_position;
        std::vector<std::string> file_names;
public:
        SpidyDocIterator();
        ~SpidyDocIterator() override;

        void 			add(std::string file_name);
        bool 			has_next() const override;
        ITokenIterator* 	parse() override;
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
