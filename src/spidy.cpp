#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>


#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>


#include <boost/locale.hpp>
#include <locale>         // std::wstring_convert
#include <codecvt>        // std::codecvt_utf8

#include "spidy.h"

typedef boost::iterator_range<boost::filesystem::directory_iterator> 	dir_range_iter_t;
typedef boost::filesystem::directory_iterator				dir_iter_t;

// Token Iterator
engine::support::SpidyTokenIterator::SpidyTokenIterator()
{
}

engine::support::SpidyTokenIterator::~SpidyTokenIterator()
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
        Term term(this->tokens[this->current_position], Term::Paragraph, this->current_position);
        this->current_position++;
        return term;
}

void
engine::support::SpidyTokenIterator::add(const std::string& token)
{
        tokens.push_back(token);
}

// Document Iterator
engine::support::SpidyDocIterator::SpidyDocIterator()
{
        xercesc::XMLPlatformUtils::Initialize();

        static const XMLCh gLS[] = {xercesc::chLatin_L,
                                    xercesc::chLatin_S,
                                    xercesc::chNull};
        xercesc::DOMImplementation *impl = xercesc::DOMImplementationRegistry::getDOMImplementation(gLS);
        xercesc::DOMLSParser       *parser = ((xercesc::DOMImplementationLS*)impl)->createLSParser(xercesc::DOMImplementationLS::MODE_SYNCHRONOUS, 0);
        xercesc::DOMConfiguration  *config = parser->getDomConfig();

        config->setParameter(xercesc::XMLUni::fgDOMNamespaces, false);
        config->setParameter(xercesc::XMLUni::fgXercesSchema, false);
        config->setParameter(xercesc::XMLUni::fgXercesHandleMultipleImports, true);
        config->setParameter(xercesc::XMLUni::fgXercesSchemaFullChecking, false);

        this->parser = parser;
}

engine::support::SpidyDocIterator::~SpidyDocIterator()
{
        xercesc::XMLPlatformUtils::Terminate();
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


//    visit(node):
//        switch(node):
//            case "div":
//                get content from node
//                add tokenized content to iterator
//                break;
//            case "p":
//                get content from node
//                add tokenized content to iterator
//                break;
//            ....
//        end
//    end

//    loop(node):
//        visit(node)
//        for child in node.children():
//            loop(child)
//        end
//    end



static inline std::string tostring(const XMLCh* xmlchstr)
{
        return xercesc::XMLString::transcode(xmlchstr);
}


void visit(xercesc::DOMElement* node, engine::support::SpidyTokenIterator& spidyTokenIterator)
{

        const XMLCh* tag = node->getTagName();
        if (xercesc::XMLString::compareIString(tag, xercesc::XMLString::transcode("div")) == 0) {
                spidyTokenIterator.add(tostring(node->getTextContent()));
        } else if ((xercesc::XMLString::compareIString(tag, xercesc::XMLString::transcode("p")) == 0)) {
                spidyTokenIterator.add(tostring(node->getTextContent()));
        } else if ((xercesc::XMLString::compareIString(tag, xercesc::XMLString::transcode("h1")) == 0)) {
                spidyTokenIterator.add(tostring(node->getTextContent()));
        } else if ((xercesc::XMLString::compareIString(tag, xercesc::XMLString::transcode("h2")) == 0)) {
                spidyTokenIterator.add(tostring(node->getTextContent()));
        } else if ((xercesc::XMLString::compareIString(tag, xercesc::XMLString::transcode("h3")) == 0)) {
                spidyTokenIterator.add(tostring(node->getTextContent()));
        } else if ((xercesc::XMLString::compareIString(tag, xercesc::XMLString::transcode("title")) == 0)) {
                spidyTokenIterator.add(tostring(node->getTextContent()));
        }
}


void loop(xercesc::DOMElement* node, engine::support::SpidyTokenIterator& spidyTokenIterator)
{
        if (node == nullptr)
                return;
        visit(node, spidyTokenIterator);
        for (unsigned i = 0; i < node->getChildElementCount(); i++) {
                loop(dynamic_cast<xercesc::DOMElement*>(node->getChildNodes()->item(i)), spidyTokenIterator);
        }
}

void
parse_as_text(const std::string& file_name, engine::support::SpidyTokenIterator* it)
{
        std::fstream file(file_name);

        std::string buffer;
        int state = 0;
        while (file.good()) {
                int ch = file.get();
                if (ch == file.eof())
                        continue;
                switch (state) {
                case 0:
                        if (std::isalnum(ch)) {
                                buffer += static_cast<char>(ch);
                                state = 1;
                        } else
                                state = 0;
                        break;
                case 1:
                        if (!std::isalnum(ch) && ch != '-') {
                                it->add(buffer);
                                buffer.clear();
                                state = 1;
                        } else {
                                buffer += static_cast<char>(ch);
                                state = 1;
                        }
                        break;
                }
        }
}

engine::support::ITokenIterator*
engine::support::SpidyDocIterator::parse()
{
        SpidyTokenIterator* spidyTokenIterator = new SpidyTokenIterator();

        std::string curr_file = this->file_names[this->current_position ++];

        xercesc::DOMDocument* domDoc;
        xercesc::DOMElement* root;
        try {
                this->parser->resetDocumentPool();
                domDoc = this->parser->parseURI(curr_file.c_str());
        } catch (...) {
                ::parse_as_text(curr_file, spidyTokenIterator);
                return spidyTokenIterator;
        }
        if (domDoc != nullptr && nullptr != (root = domDoc->getDocumentElement())) {
                ::loop(root, *spidyTokenIterator);
                return spidyTokenIterator;
        }

        // Fallback to plain text search.
        ::parse_as_text(curr_file, spidyTokenIterator);
        return spidyTokenIterator;
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
