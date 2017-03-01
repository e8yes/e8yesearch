#include "spidy.h"
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

typedef boost::iterator_range<boost::filesystem::directory_iterator> 	dir_range_iter_t;
typedef boost::filesystem::directory_iterator				dir_iter_t;


// Token Iterator
engine::support::SpidyTokenIterator::SpidyTokenIterator()
{
}

bool
engine::support::SpidyTokenIterator::has_next() const
{
        if (this->current_position == this->tokens.size()) {
                return false;
        }
        return true;
}

engine::Term
engine::support::SpidyTokenIterator::next()
{
        engine::Term term(this->tokens[this->current_position], 1, this->current_position);
        this->current_position++;
        return term;
}

void
engine::support::SpidyTokenIterator::add(const std::string& token)
{
        tokens.push_back(token);
}

engine::support::SpidyTokenIterator::~SpidyTokenIterator()
{
}

// Document Iterator
engine::support::SpidyDocIterator::SpidyDocIterator()
{
}

std::string
engine::support::SpidyDocIterator::get_descriptor() const
{
        return file_names[current_position];
}

bool
engine::support::SpidyDocIterator::has_next() const
{
        return static_cast<size_t>(this->current_position) < this->file_names.size();
}

void
engine::support::SpidyDocIterator::add(std::string file_name)
{
        this->file_names.push_back(file_name);
}

engine::support::ITokenIterator*
engine::support::SpidyDocIterator::parse()
{
        std::fstream file(this->file_names[this->current_position]);
        SpidyTokenIterator* spidyTokenIterator = new SpidyTokenIterator();
        while (file.good()) {
                std::string content;
                file >> content; // stop when space
                spidyTokenIterator->add(content);
        }
        this->current_position ++;
        return spidyTokenIterator;
}

engine::support::SpidyDocIterator::~SpidyDocIterator()
{
}

// Spidy crawl
static void
crawl(const boost::filesystem::path& dir, engine::support::SpidyDocIterator* doc_it)
{
        if (boost::filesystem::is_directory(dir)) {
                dir_range_iter_t range = boost::make_iterator_range(boost::filesystem::directory_iterator(dir), {});
                for(dir_iter_t it = range.begin(); it != range.end(); ++ it) {
                        ::crawl(it->path(), doc_it);
                }
        } else {
                doc_it->add(dir.string());
        }
}

engine::support::IDocumentIterator*
engine::support::Spidy::crawl(const std::string &directory)
{
        SpidyDocIterator* it= new SpidyDocIterator();
        ::crawl(boost::filesystem::path(directory), it);
        return it;
}


engine::support::Spidy::~Spidy()
{
}
