#include <QString>
#include <QtTest>
#include <iostream>
#include <string>
#include "../src/term.h"
#include "../src/spidy.h"
#include "../src/sqlitedatasource.h"
#include "../src/localdatagatherer.h"
#include "../src/spidyparser.h"
#include "../src/spidytextsearch.h"

class UnitTest : public QObject
{
        Q_OBJECT

public:
        UnitTest();

        void testSpidy();
        void testDB();
        void testLocalDataGatherer();
private Q_SLOTS:

        void testQueryParser();
};

UnitTest::UnitTest()
{
}

void UnitTest::testSpidy()
{
        engine::support::Spidy spidy;
        engine::support::IDocumentIterator* doc_iter = spidy.crawl("TestDir");

        while (doc_iter->has_next()) {
                std::cout << "Processing new document:" << std::endl;

                engine::support::ITokenIterator* tok_iter = doc_iter->parse();
                while (tok_iter->has_next()) {
                        std::cout << "Token: " << tok_iter->next() << std::endl;
                }
        }

        delete doc_iter;
}

void UnitTest::testDB()
{
        engine::SQLiteDataSource sqliteDataSource;
        sqliteDataSource.destroy();

        std::vector<engine::Document> test_docs;
        for (int i = 0; i < 10; i++) {
                engine::Document doc("url_" + std::to_string(i), "title_"+ std::to_string(i), 0);
                for (int j = 0; j < 3; j++) {
                        engine::Term term("content_" + std::to_string(j), 0.0, 0);
                        doc.add_term(term);
                }
                test_docs.push_back(doc);
        }
        sqliteDataSource.add_documents(test_docs);
}

void UnitTest::testLocalDataGatherer()
{
        engine::support::Spidy spidy;
        engine::SQLiteDataSource sqliteDataSource;
        sqliteDataSource.destroy();

        engine::LocalDataGatherer gatherer(&spidy, &sqliteDataSource);
        gatherer.run("TestDir");
}

void UnitTest::testQueryParser()
{
    std::string query = "Machine Learning";
    //std::getline(std::cin, query);
    std::cout << "Input your query: " << query << std::endl;

    engine::spidyParser spidyParser;
    engine::TextQuery textQuery = spidyParser.parse(query);

    engine::IDataSource* iDataSource = new engine::SQLiteDataSource();
    //iDataSource->destroy();
    //engine::support::Spidy spidy;
    //engine::LocalDataGatherer gatherer(&spidy, iDataSource);
    //gatherer.run("WEBPAGES_SIMPLE");

    engine::spidyTextSearch spidyTextSearch(iDataSource);
    engine::sorted_results_t documents;
    spidyTextSearch.find(textQuery, documents);

    if (documents.empty()) {
            std::cout << "No matched document found" << std::endl;
    } else {
        for (engine::Document doc : documents) {
            std::cout << doc.get_url() << std::endl;
        }
    }

}

QTEST_APPLESS_MAIN(UnitTest)

#include "tst_unittest.moc"
