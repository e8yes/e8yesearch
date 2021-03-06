#include <QString>
#include <QtTest>
#include <iostream>
#include <string>
#include "../src/term.h"
#include "../src/spidy.h"
#include "../src/sqlitedatasource.h"
#include "../src/localdatagatherer.h"
#include "../src/spidyqueryhandler.h"
#include "../src/spidytextsearch.h"

class UnitTest : public QObject
{
        Q_OBJECT

public:
        UnitTest();

        void testSpidy();
        void testSqliteDataSource();
        void testLocalDataGatherer();
        void testSpidyTextQuery();
private Q_SLOTS:
        void testMapBPTree();
 };

UnitTest::UnitTest()
{
}

void UnitTest::testSpidy()
{
        engine::support::Spidy spidy;
        engine::support::IDocumentIterator* doc_iter = spidy.crawl("WEBPAGES_SIMPLE");

        while (doc_iter->has_next()) {
                std::cout << "Processing new document:" << doc_iter->get_descriptor() << std::endl;

                engine::support::ITokenIterator* tok_iter = doc_iter->parse();
                while (tok_iter->has_next()) {
                        std::cout << "Token: " << tok_iter->next().first << std::endl;
                }
        }

        delete doc_iter;
}

void UnitTest::testSqliteDataSource()
{
        engine::SQLiteDataSource sqliteDataSource;
        sqliteDataSource.destroy();

        std::vector<engine::Document> test_docs;
        for (int i = 0; i < 10; i++) {
                engine::Document doc("url_" + std::to_string(i), "title_"+ std::to_string(i), 0);
                for (int j = 0; j < 3; j++) {
                        engine::Term term("content_" + std::to_string(j));
                        doc.add_term(term, engine::TermPosition(j, 0));
                }
                sqliteDataSource.add_document(doc);
        }
}

void UnitTest::testLocalDataGatherer()
{
        engine::support::Spidy spidy;
        engine::SQLiteDataSource sqliteDataSource;
        sqliteDataSource.destroy();

        engine::LocalDataGatherer gatherer(&spidy, &sqliteDataSource);
        gatherer.run("WEBPAGES_SIMPLE");

        std::cout << "#Documents: " << sqliteDataSource.document_count() << std::endl;
}

void UnitTest::testSpidyTextQuery()
{
        std::string query = "compter";
        //std::getline(std::cin, query);
        std::cout << "Input your query: " << query << std::endl;

        engine::IDataSource* iDataSource = new engine::SQLiteDataSource();
        engine::SpidyQueryHandler spidyParser(iDataSource);
        engine::TextQuery textQuery = spidyParser.parse(query);
        engine::SpidyTextSearch spidyTextSearch(iDataSource);
        engine::sorted_results_t documents;
        spidyTextSearch.find(textQuery, documents);

        if (documents.empty()) {
                std::cout << "No matched document found" << std::endl;
        } else {
                for (engine::Document doc : documents) {
                        std::cout << doc.get_url() << "---" << doc.get_importance() << std::endl;

                }
        }

}

void UnitTest::testMapBPTree()
{
}

QTEST_APPLESS_MAIN(UnitTest)

#include "tst_unittest.moc"
