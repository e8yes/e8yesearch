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
    int current_position;
    std::vector<string> tokens;
public:
    SpidyTokenIterator();
    bool has_next() const;
    void add(std::string token);
    Term next();
    ~SpidyTokenIterator();
};

class SpidyDocIterator: public IDocumentIterator
{
private:
    int current_position;
    std::vector<string> file_names;
public:
    SpidyDocIterator();
    bool has_next() const;
    void add(std::string file_name);
    ITokenIterator* parse();
    ~IDocumentIterator() override;
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
