#ifndef LOCALDATAGATHERER_H
#define LOCALDATAGATHERER_H

#include "term.h"
#include "ispider.h"
#include "idatagatherer.h"
#include "idatasource.h"

namespace engine
{

class LocalDataGatherer: public IDataGatherer
{
public:
        LocalDataGatherer(support::ISpider* spider, IDataSource* ds);
        ~LocalDataGatherer() override;

        void 	run(const std::string& directory) override;
        float 	progress() override;
private:
        void 	compute_idf(const std::string& directory, idf_t& idf);
        void 	add_documents(const std::string& directory, const idf_t& idf);

        float 				m_progress = .0f;
        unsigned			m_num_docs = 0;

        support::ISpider* const 	m_spider;
        IDataSource* const 		m_ds;
};

}

#endif // LOCALDATAGATHERER_H
