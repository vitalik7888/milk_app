#include "Test_CalculatedItem.h"

#include "CalculatedItem.h"
// Qt
#include <QTest>


Test_CalculatedItem::Test_CalculatedItem(QObject *parent) : QObject(parent)
{

}

void Test_CalculatedItem::compare(CalculatedItem *ci, const double liters, const double fat,
                                  const double priceForLiter)
{
    QCOMPARE(ci->liters(), liters);
    QCOMPARE(ci->fat(), fat);
    QCOMPARE(ci->priceForLiter(), priceForLiter);
}

void Test_CalculatedItem::compareDefault(CalculatedItem *ci)
{
    compare(ci, .0, .0, .0);
}

void Test_CalculatedItem::testEmptyConstructor()
{
    CalculatedItem ci;
    compareDefault(&ci);
}

void Test_CalculatedItem::testConstructor()
{
    CalculatedItem ci(10.2, 3.4, 10.6);
    compare(&ci, 10.2, 3.4, 10.6);
}

void Test_CalculatedItem::calculatedResult_data()
{
    QTest::addColumn<double>("liters");
    QTest::addColumn<double>("fat");
    QTest::addColumn<double>("priceForLiter");
    QTest::addColumn<double>("protein");
    QTest::addColumn<double>("fatUnits");
    QTest::addColumn<double>("rankWeight");
    QTest::addColumn<double>("paymentWithOutPremium");
    QTest::addColumn<double>("premiumForFat");
    QTest::addColumn<double>("sum");

    QTest::newRow("case 1")                     << 12.0 << 5.1 << 15.0 << 4.5
                                                << 61.2 << 18.0 << 180.0
                                                << 90.0 << 270.0;
    QTest::newRow("case liters zero")           << 0.0 << 5.1 << 12.0 << 4.5
                                                << 0.0 << 0.0 << 0.0 << 0.0
                                                << 0.0;
    QTest::newRow("case fat zero")              << 12.0 << 0.0 << 13.7 << 0.0
                                                << 0.0 << 0.0 << 164.4 << 0.0
                                                << 0.0;
    QTest::newRow("case priceForLiter zero")    << 15.0 << 3.4 << 0.0 << 3.0
                                                << 51.0 << 15.0 << 0.0 << 0.0
                                                << 0.0;
}

void Test_CalculatedItem::calculatedResult()
{
    QFETCH(double, liters);
    QFETCH(double, fat);
    QFETCH(double, priceForLiter);
    QFETCH(double, protein);
    QFETCH(double, fatUnits);
    QFETCH(double, rankWeight);
    QFETCH(double, paymentWithOutPremium);
    QFETCH(double, premiumForFat);
    QFETCH(double, sum);

    CalculatedItem ci(liters, fat, priceForLiter);
    QCOMPARE(ci.protein(), protein);
    QCOMPARE(ci.fatUnits(), fatUnits);
    QCOMPARE(ci.rankWeight(), rankWeight);
    QCOMPARE(ci.paymentWithOutPremium(), paymentWithOutPremium);
    QCOMPARE(ci.premiumForFat(), premiumForFat);
    QCOMPARE(ci.sum(), sum);
}

void Test_CalculatedItem::add()
{

}

