#include "calc/Test_CalculatedItemData.h"

#include <CalculatedItemData.h>
// Qt
#include <QTest>


Test_CalculatedItemData::Test_CalculatedItemData(QObject *parent) : QObject(parent)
{

}

void Test_CalculatedItemData::compare(const CalculatedItemData &item, const double liters,
                                      const double fat, const double priceForLiter,
                                      const double protein, const double fatUnits,
                                      const double rankWeight, const double paymentWithOutPremium,
                                      const double premiumForFat, const double sum)
{
    QCOMPARE(item.liters(), liters);
    QCOMPARE(item.fat(), fat);
    QCOMPARE(item.priceForLiter(), priceForLiter);
    QCOMPARE(item.protein(), protein);
    QCOMPARE(item.fatUnits(), fatUnits);
    QCOMPARE(item.rankWeight(), rankWeight);
    QCOMPARE(item.paymentWithOutPremium(), paymentWithOutPremium);
    QCOMPARE(item.premiumForFat(), premiumForFat);
    QCOMPARE(item.sum(), sum);
}

void Test_CalculatedItemData::emptyConstructor()
{
    compare(CalculatedItemData(), .0, .0, .0, .0, .0, .0, .0, .0, .0);
}

void Test_CalculatedItemData::calculatedResult_data()
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
    QTest::newRow("case all zero")              << 0.0 << 0.0 << 0.0 << 0.0
                                                << 0.0 << 0.0 << 0.0 << 0.0
                                                << 0.0;
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

void Test_CalculatedItemData::calculatedResult()
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

    CalculatedItemData ci(liters, fat, priceForLiter);
    compare(ci, liters, fat, priceForLiter, protein, fatUnits, rankWeight, paymentWithOutPremium, premiumForFat, sum);
}

void Test_CalculatedItemData::add()
{
    const QList<CalculatedItemData> calcItems {
        {12.0, 5.1, 15.00},
    };
    CalculatedItemData result;
    for (const auto &item : calcItems)
        result += item;
    compare(result, 12.0, 5.1, .0, 4.5, 61.2, 18.0, 180.0, 90.0, 270.0);
}

