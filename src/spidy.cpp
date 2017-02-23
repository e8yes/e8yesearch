#include "spidy.h"
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>


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
        engine::Term term(this->tokens[this->current_position], 1, this->current_position);
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
        return static_cast<size_t>(this->current_position) < this->file_names.size();
}

void engine::support::SpidyDocIterator::add(std::string file_name)
{
        this->file_names.push_back(file_name);
}

engine::support::ITokenIterator* engine::support::SpidyDocIterator::parse()
{
        std::fstream file(this->file_names[this->current_position]);
        SpidyTokenIterator* spidyTokenIterator = new SpidyTokenIterator();
        while (file.good()) {
                std::string content;
                file >> content; // stop when space
                spidyTokenIterator->add(content);
        }
        return spidyTokenIterator;
}

engine::support::SpidyDocIterator::~SpidyDocIterator()
{
}

// Spidy crawl
engine::support::IDocumentIterator* engine::support::Spidy::crawl(const std::string &directory)
{
        boost::filesystem::path p = directory;

        SpidyDocIterator* spidyDocIterator = new SpidyDocIterator();
        for(auto& entry : boost::make_iterator_range(boost::filesystem::directory_iterator(p), {})) {
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
