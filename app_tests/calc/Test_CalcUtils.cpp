#include "Test_CalcUtils.h"

#include "CalcUtils.h"
// Qt
#include <QTest>

static const int PREC = 5;


Test_CalcUtils::Test_CalcUtils(QObject *parent) : QObject(parent)
{

}

void Test_CalcUtils::protein_data()
{
    QTest::addColumn<double>("fat");
    QTest::addColumn<double>("result");

    QTest::newRow("below zero")        << -32.200 << 0.0000;
    QTest::newRow("zero")              << 0.0000  << 0.0000;
    QTest::newRow("after zero case 1") << 5.1000  << 4.5000;
}

void Test_CalcUtils::protein()
{
    QFETCH(double, fat);
    QFETCH(double, result);
    QCOMPARE(CalcUtils::protein(fat), result);
}

void Test_CalcUtils::fat_data()
{
    QTest::addColumn<double>("fatUnits");
    QTest::addColumn<double>("liters");
    QTest::addColumn<double>("result");

    QTest::newRow("fatUnits below zero") << -2.000  << 1.6400 << 0.0000;
    QTest::newRow("liters below zero")   << 16.000  << -3.6400 << 0.0000;
    QTest::newRow("zero")                << 0.0000  << 0.0000  << 0.0000;
    QTest::newRow("after zero case 1")   << 62.4000 << 13.0000 << 4.8000;
    QTest::newRow("after zero case 2")   << 52.8000 << 12.0000 << 4.4000;
    QTest::newRow("after zero case 3")   << 52.8000 << 12.0000 << 4.4000;
}

void Test_CalcUtils::fat()
{
    QFETCH(double, fatUnits);
    QFETCH(double, liters);
    QFETCH(double, result);
    QCOMPARE(CalcUtils::fat(fatUnits, liters), result);
}

void Test_CalcUtils::liters_data()
{
    QTest::addColumn<double>("fatUnits");
    QTest::addColumn<double>("fat");
    QTest::addColumn<double>("result");

    QTest::newRow("fatUnits below zero") << -9.1500 << 4.2000 << 0.0000;
    QTest::newRow("fat below zero")      << 50.000 << -4.3200 << 0.0000;
    QTest::newRow("zero")                << 0.0000  << 0.0000 << 0.0000;
    QTest::newRow("after zero case 1")   << 38.2500 << 5.1000 << 7.5000;
    QTest::newRow("after zero case 2")   << 46.7500 << 5.5000 << 8.5000;
    QTest::newRow("after zero case 3")   << 35.0000 << 5.0000 << 7.0000;
}

void Test_CalcUtils::liters()
{
    QFETCH(double, fatUnits);
    QFETCH(double, fat);
    QFETCH(double, result);
    QCOMPARE(CalcUtils::liters(fatUnits, fat), result);
}

void Test_CalcUtils::fatUnits_data()
{
    QTest::addColumn<double>("liters");
    QTest::addColumn<double>("fat");
    QTest::addColumn<double>("result");

    QTest::newRow("liter below zero")   << -20.000 << 4.2000 << 0.0000;
    QTest::newRow("fat zero")           << 0.0000  << -1.9600 << 0.0000;
    QTest::newRow("zero")               << 0.0000  << 0.0000 << 0.0000;
    QTest::newRow("after zero case 1")  << 20.0000 << 4.2000 << 84.0000;
    QTest::newRow("after zero case 2")  << 7.5000  << 4.0000 << 30.0000;
    QTest::newRow("after zero case 3")  << 6.0000  << 4.5000 << 27.0000;
}

void Test_CalcUtils::fatUnits()
{
    QFETCH(double, liters);
    QFETCH(double, fat);
    QFETCH(double, result);
    QCOMPARE(CalcUtils::fatUnits(liters, fat), result);
}

void Test_CalcUtils::rankWeight_data()
{
    QTest::addColumn<double>("fatUnits");
    QTest::addColumn<double>("result");

    QTest::newRow("below zero")             << -43.000 << 0.00000;
    QTest::newRow("zero")                   << 0.0000  << 0.0000;
    QTest::newRow("after zero case 1")      << 45.9000 << 13.5000;
    QTest::newRow("after zero case 2")      << 45.0500 << 13.2500;
}

void Test_CalcUtils::rankWeight()
{
    QFETCH(double, fatUnits);
    QFETCH(double, result);
    QCOMPARE(CalcUtils::rankWeight(fatUnits), result);
}

void Test_CalcUtils::premiumForFat_data()
{
    QTest::addColumn<double>("fat");
    QTest::addColumn<double>("paymentWithOutPremium");
    QTest::addColumn<double>("result");

    QTest::newRow("fat below zero")    << -2.000 << 4.2000   << 0.0000;
    QTest::newRow("payment below zero")<< 3.6450 << 0.0000   << 0.0000;
    QTest::newRow("zero")              << 0.0000 << 0.0000   << 0.0000;
    QTest::newRow("after zero case 1") << 4.1000 << 127.5000 << 26.2500;
    QTest::newRow("after zero case 2") << 5.7000 << 182.7500 << 123.6250;
}

void Test_CalcUtils::premiumForFat()
{
    QFETCH(double, fat);
    QFETCH(double, paymentWithOutPremium);
    QFETCH(double, result);
    QCOMPARE(CalcUtils::premiumForFat(fat, paymentWithOutPremium), result);
}

void Test_CalcUtils::paymentWithOutPremium_data()
{
    QTest::addColumn<double>("liters");
    QTest::addColumn<double>("price");
    QTest::addColumn<double>("result");

    QTest::newRow("liters below zero") << -20.000 << 4.2000 << 0.0000;
    QTest::newRow("price below zero")  << 10.000  << -3.600 << 0.0000;
    QTest::newRow("zero")              << 0.0000  << 0.0000 << 0.0000;
    QTest::newRow("after zero case 1") << 8.5000  << 21.5000 << 182.7500;
    QTest::newRow("after zero case 2") << 21.5000 << 9.5000 << 204.2500;
}

void Test_CalcUtils::paymentWithOutPremium()
{
    QFETCH(double, liters);
    QFETCH(double, price);
    QFETCH(double, result);
    QCOMPARE(CalcUtils::paymentWithOutPremium(liters, price), result);
}

void Test_CalcUtils::sum_data()
{
    QTest::addColumn<double>("rankWeight");
    QTest::addColumn<double>("price");
    QTest::addColumn<double>("result");

    QTest::newRow("rankWeight below zero") << -17.000 << 4.2000 << 0.0000;
    QTest::newRow("price below zero")      << 16.000 << -3.5000 << 0.0000;
    QTest::newRow("zero")                  << 0.0000  << 0.0000 << 0.0000;
    QTest::newRow("after zero case 1")     << 10.2500 << 15.000 << 153.7500;
    QTest::newRow("after zero case 2")     << 14.2500 << 21.5000 << 306.3750;
}

void Test_CalcUtils::sum()
{
    QFETCH(double, rankWeight);
    QFETCH(double, price);
    QFETCH(double, result);
    QCOMPARE(CalcUtils::sum(rankWeight, price), result);
}

