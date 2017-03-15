#include "sqlitedatasource.h"
#include "localdatagatherer.h"
#include "spidy.h"
#include "spidytextsearch.h"
#include "spidyqueryhandler.h"
#include "textquery.h"
#include "app.h"

web::App::App()
{
        m_ds = new engine::SQLiteDataSource();
        m_spider = new engine::support::Spidy();
        m_gatherer = new engine::LocalDataGatherer(m_spider, m_ds);
        m_searcher = new engine::SpidyTextSearch(m_ds);
        m_parser = new engine::spidyQueryHandler();
}

web::App::~App()
{
        delete m_ds;
        delete m_spider;
        delete m_gatherer;
        delete m_searcher;
}

void
web::App::search(const std::string& query, engine::sorted_results_t& result)
{
        engine::TextQuery tquery = m_parser->parse(query);
        m_searcher->find(tquery, result);
}

void
web::App::tunnel_local(const std::string& descriptor)
{
        m_ds->destroy();
        m_gatherer->run(descriptor);
}

float
web::App::progress(Task task) const
{
        switch (task) {
        case Task::Tunnel:
                return m_gatherer->progress();
        }
        return -1;
}
