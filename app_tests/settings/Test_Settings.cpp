#include "Test_Settings.h"

#include <Settings.h>
#include "Test_MainSettings.h"
#include "Test_CalcSettings.h"
#include "Test_PrintSettings.h"
#include "SettingsConstants.h"
// Qt
#include <QSignalSpy>
#include <QTest>

using SC = SettingsConstants;


Test_Settings::Test_Settings(QObject *parent) : QObject(parent)
{
    const QString fileName = "test_settings";
    QFile::remove(fileName);
    m_settings = new Settings(fileName, this);
}

void Test_Settings::testEmptyConstructor()
{
    QCOMPARE((bool)m_settings->main(), true);
    QCOMPARE((bool)m_settings->print(), true);
    QCOMPARE((bool)m_settings->calc(), true);
}

void Test_Settings::testReadWriteDefaultSettings()
{
    m_settings->writeSettings();
    m_settings->readSettings();

    Test_MainSettings::compareDefault(m_settings->main());
    Test_PrintSettings::compareDefault(m_settings->print());
    Test_CalcSettings::compareDefault(m_settings->calc());
}

void Test_Settings::testReadWriteSettings()
{
    auto main = m_settings->main();
    main->setLastChoosenDb("db_Name");
    main->setPriceLiter(9.6f);
    main->setFirmName("f_name");
    main->setMilkInspector("ins1");
    main->setMilkInspector2("ins2");
    main->setIsFetchTablesOnRefresh(true);

    auto print = m_settings->print();
    print->setTextFont({"Times", 10, QFont::Bold});
    print->setCaptionTextFont({"Times", 9, QFont::Bold});
    print->setCaptionColor({Qt::black});
    print->setTableWidth(2);
    print->setTableBorderWidth(3);
    print->setTableBorderStyle(4);
    print->setCellSpacing(2);
    print->setCellPadding(2);
    print->setTableBorderColor({Qt::green});
    print->setTableHeaderFont({"Times", 10, QFont::Bold});
    print->setTableHeaderColor({Qt::red});
    print->setTableTextFont({"Times", 11, QFont::Bold});
    print->setTableTextColor({Qt::white});
    print->setTableResultFont({"Times", 12, QFont::Bold});
    print->setTableResultColor({Qt::gray});

    auto calc = m_settings->calc();
    calc->setTextFont({"Times", 10, QFont::Bold});
    calc->setTextBackColor({Qt::black});
    calc->setDelivResultFont({"Times", 11, QFont::Bold});
    calc->setDelivResultColor({Qt::white});
    calc->setAllResultFont({"Times", 12, QFont::Bold});
    calc->setAllResultColor({Qt::green});
    calc->setDateFormat("MMMM");

    m_settings->writeSettings();
    m_settings->readSettings();

    Test_MainSettings::compare(main, "db_Name", 9.6f, "f_name", "ins1", "ins2", true);
    Test_PrintSettings::compare(print, {"Times", 10, QFont::Bold}, {"Times", 9, QFont::Bold}, {Qt::black}, 2, 3, 4, 2, 2, {Qt::green},
    {"Times", 10, QFont::Bold}, {Qt::red}, {"Times", 11, QFont::Bold}, {Qt::white}, {"Times", 12, QFont::Bold}, {Qt::gray});
    Test_CalcSettings::compare(calc, {"Times", 10, QFont::Bold}, {Qt::black},
    {"Times", 11, QFont::Bold}, {Qt::white}, {"Times", 12, QFont::Bold}, {Qt::green}, "MMMM");
}

void Test_Settings::testReadWriteSettingsAfterReset()
{
    m_settings->reset();
    m_settings->writeSettings();
    m_settings->readSettings();

    Test_MainSettings::compareDefault(m_settings->main());
    Test_PrintSettings::compareDefault(m_settings->print());
    Test_CalcSettings::compareDefault(m_settings->calc());
}

