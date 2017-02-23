#include <QString>
#include <QtTest>
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
    spidy.crawl("TestDir");
}

QTEST_APPLESS_MAIN(UnitTest)

#include "tst_unittest.moc"
