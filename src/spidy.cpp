#include "spidy.h"
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace boost::filesystem;


// Token Iterator
engine::support::SpidyTokenIterator::SpidyTokenIterator()
{
    this->current_position = 0;
}

bool engine::support::SpidyTokenIterator::has_next() const
{
    if (this->current_position == this->tokens.size()) {
        return false;
    }
    return true;
}

engine::Term engine::support::SpidyTokenIterator::next()
{
    engine::Term term(this->tokens[this->current_position], 1);
    this->current_position++;
    return term;
}

engine::support::SpidyTokenIterator::~SpidyTokenIterator()
{
}

// Document Iterator
engine::support::SpidyDocIterator::SpidyDocIterator()
{
    this->current_position = 0;
}

bool engine::support::SpidyDocIterator::has_next() const
{
    if (this->current_position == this->file_names.size()) {
        return false;
    }
    return true;
}

void engine::support::SpidyDocIterator::add(std::string file_name)
{
    this->file_names.push_back(file_name);
}

engine::support::SpidyDocIterator::ITokenIterator* engine::support::SpidyDocIterator::parse()
{
    std::fstream file(this->file_names[this->current_position]);
    SpidyTokenIterator* spidyTokenIterator = new SpidyTokenIterator();
    while (file.good()) {
        string content;
        file >> content; // stop when space
        spidyTokenIterator->add(content);
    }
    return spidyTokenIterator;
}

engine::support::~SpidyDocIterator()
{
}

// Spidy crawl
engine::support::IDocumentIterator* engine::support::Spidy::crawl(const std::string &directory)
{
    path p = ".";

    if(is_directory(p)) {
    std::cout << p << " is a directory containing:\n";

    SpidyDocIterator* spidyDocIterator;
    for(auto& entry : boost::make_iterator_range(directory_iterator(p), {})) {
        std::cout << entry << "\n";
        std::stringstream sstream;
        sstream << entry;
        std::string entry_str;
        sstream >> entry_str;
        spidyDocIterator->add(entry_str);
    }
    return spidyDocIterator;
}


engine::support::Spidy::~Spidy()
{
}
