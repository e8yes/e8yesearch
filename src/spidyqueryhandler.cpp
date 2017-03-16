#include <sstream>
#include "utils.h"
#include "spidyqueryhandler.h"

engine::SpidyQueryHandler::SpidyQueryHandler(IDataSource* ds):
        m_ds(ds)
{
}

engine::TextQuery engine::SpidyQueryHandler::parse(const std::string& query)
{
        std::stringstream sstream;
        sstream << query;
        std::vector<std::string> contents;

        while (sstream.good()) {
                std::string temp_str;
                sstream >> temp_str;
                contents.push_back(temp_str);
        }

        TextQuery tquery;
        for (unsigned i = 0; i < contents.size(); i ++) {
                const std::string& content = util::toupper(contents[i]);
                Term term;
                bool has_term = m_ds->find_term_by_content(content, term);
                if (!has_term)
                        has_term = m_ds->find_term_by_fuzzy_content(content, term);

                if (has_term) {
                        tquery.add_term(term, TermPosition(i, .0f));
                }
        }
        return tquery;
}


engine::SpidyQueryHandler::~SpidyQueryHandler()
{
}
