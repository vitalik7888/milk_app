#include "Test_MainSettings.h"

#include "MainSettings.h"
#include "SettingsConstants.h"
// Qt
#include <QtTest/QtTest>

using SC = SettingsConstants;


Test_MainSettings::Test_MainSettings(QObject *parent) : QObject(parent)
{

}

void Test_MainSettings::testEmptyConstructor()
{
    MainSettings ms;

    compareDefault(&ms);
}

void Test_MainSettings::testConstructor()
{
    MainSettings ms("dbName", 10.4f, "firm", "inspector1", "inspector2", false);

    compare(&ms, "dbName", 10.4f, "firm", "inspector1", "inspector2", false);
}

void Test_MainSettings::testMethods()
{
    MainSettings ms;
    ms.setLastChoosenDb("db_Name");
    ms.setPriceLiter(9.6f);
    ms.setFirmName("f_name");
    ms.setMilkInspector("ins1");
    ms.setMilkInspector2("ins2");
    ms.setIsFetchTablesOnRefresh(true);

    compare(&ms, "db_Name", 9.6f, "f_name", "ins1", "ins2", true);
}

void Test_MainSettings::testReset()
{
    MainSettings ms("dbName", 10.4f, "firm", "inspector1", "inspector2", false);
    ms.reset();

    compareDefault(&ms);
}

void Test_MainSettings::testSignalLastChoosenDbChanged()
{
    MainSettings ms;
    QSignalSpy signalSpy(&ms, &MainSettings::lastChoosenDbChanged);
    ms.setLastChoosenDb("_db");
    ms.setLastChoosenDb("_db");
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toString(), QString("_db"));
}

void Test_MainSettings::testSignalPriceLiterChanged()
{
    MainSettings ms;
    QSignalSpy signalSpy(&ms, &MainSettings::priceLiterChanged);
    ms.setPriceLiter(11.3f);
    ms.setPriceLiter(11.3f);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toFloat(), 11.3f);
}

void Test_MainSettings::testSignalFirmNameChanged()
{
    MainSettings ms;
    QSignalSpy signalSpy(&ms, &MainSettings::firmNameChanged);
    ms.setFirmName("fn");
    ms.setFirmName("fn");
    ms.setFirmName("fn2");
    QCOMPARE(signalSpy.count(), 2);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toString(), QString("fn"));
    const QVariantList arguments2 = signalSpy.at(1);
    QCOMPARE(arguments2.at(0).toString(), QString("fn2"));
}

void Test_MainSettings::testSignalMilkInspectorChanged()
{
    MainSettings ms;
    QSignalSpy signalSpy(&ms, &MainSettings::milkInspectorChanged);
    ms.setMilkInspector("insp");
    ms.setMilkInspector("insp");
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toString(), QString("insp"));
}

void Test_MainSettings::testSignalMilkInspector2Changed()
{
    MainSettings ms;
    QSignalSpy signalSpy(&ms, &MainSettings::milkInspector2Changed);
    ms.setMilkInspector2("insp2");
    ms.setMilkInspector2("insp2");
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toString(), QString("insp2"));
}

void Test_MainSettings::testSignalIsFetchTablesOnRefreshChanged()
{
    MainSettings ms;
    QSignalSpy signalSpy(&ms, &MainSettings::isFetchTablesOnRefreshChanged);
    ms.setIsFetchTablesOnRefresh(true);
    ms.setIsFetchTablesOnRefresh(true);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toBool(), true);
}

void Test_MainSettings::compare(MainSettings *ms, const QString &lastChoosenDb, const float priceLiter, const QString &firmName, const QString &milkInspector, const QString &milkInspector_2, const bool isFetchTablesOnRefresh)
{
    QCOMPARE(ms->lastChoosenDb(), lastChoosenDb);
    QCOMPARE(ms->priceLiter(), priceLiter);
    QCOMPARE(ms->firmName(), firmName);
    QCOMPARE(ms->milkInspector(), milkInspector);
    QCOMPARE(ms->milkInspector2(), milkInspector_2);
    QCOMPARE(ms->isFetchTablesOnRefresh(), isFetchTablesOnRefresh);
}

void Test_MainSettings::compareDefault(MainSettings *ms)
{
    compare(ms, SC::DEF_LAST_CHOOSEN_DB, SC::DEF_PRICE_LITER, SC::DEF_FIRM_NAME,
            SC::DEF_MILK_INSPECTOR, SC::DEF_MILK_INSPECTOR2, SC::DEF_IS_FETCH_TABLE_ON_REFRESH);
}
