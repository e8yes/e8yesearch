#include <set>

#include "localdatagatherer.h"


engine::LocalDataGatherer::LocalDataGatherer(support::ISpider* spider, IDataSource* ds):
        m_spider(spider), m_ds(ds)
{
}

engine::LocalDataGatherer::~LocalDataGatherer()
{
}

void
engine::LocalDataGatherer::compute_idf(const std::string& directory, idf_t& idf)
{
        m_num_docs = 0;

        support::IDocumentIterator* doc_iter = m_spider->crawl(directory);
        while (doc_iter->has_next()) {
                // Collect terms.
                std::set<Term> terms;
                support::ITokenIterator* tok_iter = doc_iter->parse();
                while (tok_iter->has_next())
                        terms.insert(tok_iter->next().first);

                delete tok_iter;

                // Update idf stats.
                for (Term term: terms) {
                        idf_t::iterator it = idf.find(term);
                        if (it != idf.end())	it->second ++;
                        else			idf.insert(idf_entry_t(term, 1));
                }

                m_num_docs ++;
        }
        delete doc_iter;
}

void
engine::LocalDataGatherer::add_documents(const std::string& directory, const idf_t& idf)
{
        float curr_pro = m_progress;
        unsigned i_doc = 0;

        // Gather terms and put into data source.
        support::IDocumentIterator* doc_iter = m_spider->crawl(directory);
        while (doc_iter->has_next()) {
                std::string descriptor = doc_iter->get_descriptor();
                Document curr_doc(descriptor, "Unknown", 0.0f);

                // Put terms into document collect term frequency
                support::ITokenIterator* tok_iter = doc_iter->parse();
                while (tok_iter->has_next()) {
                        term_pos_t termpos = tok_iter->next();
                        termpos.first.set_idf(idf.at(termpos.first));
                        curr_doc.add_term(termpos.first, termpos.second);
                }
                delete tok_iter;

                m_ds->add_document(curr_doc);
                m_progress = curr_pro + (1 - curr_pro)*static_cast<float>(++ i_doc)/m_num_docs;
        }
        m_ds->force_transaction();
        delete doc_iter;
}

void
engine::LocalDataGatherer::run(const std::string& directory)
{
        m_progress = .1f;
        idf_t idf;
        compute_idf(directory, idf);

        m_progress = .5f;
        add_documents(directory, idf);
}

float
engine::LocalDataGatherer::progress()
{
        return m_progress;
}
