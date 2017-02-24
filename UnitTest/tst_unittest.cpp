#include <QString>
#include <QtTest>
#include <iostream>
#include "../src/term.h"
#include "../src/spidy.h"

class UnitTest : public QObject
{
        Q_OBJECT

public:
        UnitTest();

private Q_SLOTS:
        void testSpidy();
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

QTEST_APPLESS_MAIN(UnitTest)

#include "tst_unittest.moc"
