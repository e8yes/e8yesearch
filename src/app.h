#ifndef APP_H
#define APP_H

#include "document.h"
#include "itextsearch.h"
#include "iqueryparser.h"
#include "idatasource.h"
#include "idatagatherer.h"
#include "ispider.h"


namespace web
{

class App
{
public:
        enum Task {
                Tunnel
        };

        App();
        ~App();

        std::string	search(const std::string& query, engine::sorted_results_t& result);
        void 		tunnel_local(const std::string& descriptor);
        float 		progress(Task task) const;
private:
        engine::ITextSearch*		m_searcher;
        engine::IDataSource* 		m_ds;
        engine::IDataGatherer* 		m_gatherer;
        engine::support::ISpider*	m_spider;
        engine::IQueryParser*		m_parser;
};

}

#endif // APP_H
