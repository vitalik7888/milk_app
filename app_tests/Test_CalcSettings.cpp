#include "Test_CalcSettings.h"

#include <CalcSettings.h>
#include "SettingsConstants.h"
// Qt
#include <QSignalSpy>
#include <QTest>

using SC = SettingsConstants;
using SCC = SC::Calc;


Test_CalcSettings::Test_CalcSettings(QObject *parent) : QObject(parent)
{

}

void Test_CalcSettings::testEmptyConstructor()
{
    CalcSettings cs;
    compareDefault(cs);
}

void Test_CalcSettings::testMethods()
{
    CalcSettings cs;
    cs.setTextFont({"Times", 10, QFont::Bold});
    cs.setTextBackColor({Qt::black});
    cs.setDelivResultFont({"Times", 11, QFont::Bold});
    cs.setDelivResultColor({Qt::white});
    cs.setAllResultFont({"Times", 12, QFont::Bold});
    cs.setAllResultColor({Qt::green});
    cs.setDateFormat("MMMM");

    compare(cs, {"Times", 10, QFont::Bold}, {Qt::black},
        {"Times", 11, QFont::Bold}, {Qt::white}, {"Times", 12, QFont::Bold}, {Qt::green}, "MMMM");
}

void Test_CalcSettings::testReset()
{
    CalcSettings cs;
    cs.setTextFont({"Times", 10, QFont::Bold});
    cs.setTextBackColor({Qt::black});
    cs.setDelivResultFont({"Times", 11, QFont::Bold});
    cs.setDelivResultColor({Qt::white});
    cs.setAllResultFont({"Times", 12, QFont::Bold});
    cs.setAllResultColor({Qt::green});
    cs.setDateFormat("MMMM");
    cs.reset();

    compareDefault(cs);
}

void Test_CalcSettings::testSignalTextFontChanged()
{
    CalcSettings cs;
    const QFont font{"Times", 10, QFont::Bold};
    QSignalSpy signalSpy(&cs, &CalcSettings::textFontChanged);

    cs.setTextFont(font);
    cs.setTextFont(font);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toString(), font.toString());
}

void Test_CalcSettings::testSignalTextBackColorChanged()
{
    CalcSettings cs;
    const QColor color{Qt::black};
    QSignalSpy signalSpy(&cs, &CalcSettings::textBackColorChanged);

    cs.setTextBackColor(color);
    cs.setTextBackColor(color);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toString(), color.name());
}

void Test_CalcSettings::testSignalDelivResultFontChanged()
{
    CalcSettings cs;
    const QFont font{"Times", 11, QFont::Bold};
    QSignalSpy signalSpy(&cs, &CalcSettings::delivResultFontChanged);

    cs.setDelivResultFont(font);
    cs.setDelivResultFont(font);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toString(), font.toString());
}

void Test_CalcSettings::testSignalDelivResultColorChanged()
{
    CalcSettings cs;
    const QColor color{Qt::red};
    QSignalSpy signalSpy(&cs, &CalcSettings::delivResultColorChanged);

    cs.setDelivResultColor(color);
    cs.setDelivResultColor(color);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toString(), color.name());
}

void Test_CalcSettings::testSignalAllResultFontChanged()
{
    CalcSettings cs;
    const QFont font{"Times", 9, QFont::Bold};
    QSignalSpy signalSpy(&cs, &CalcSettings::allResultFontChanged);

    cs.setAllResultFont(font);
    cs.setAllResultFont(font);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toString(), font.toString());
}

void Test_CalcSettings::testSignalAllResultColorChanged()
{
    CalcSettings cs;
    const QColor color{Qt::gray};
    QSignalSpy signalSpy(&cs, &CalcSettings::allResultColorChanged);

    cs.setAllResultColor(color);
    cs.setAllResultColor(color);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toString(), color.name());
}

void Test_CalcSettings::testSignalDateFormatChanged()
{
    CalcSettings cs;
    const QString dateFormat = "yyyy";
    QSignalSpy signalSpy(&cs, &CalcSettings::dateFormatChanged);

    cs.setDateFormat(dateFormat);
    cs.setDateFormat(dateFormat);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toString(), dateFormat);
}

void Test_CalcSettings::compare(const CalcSettings &cs, const QFont &textFont,
                                const QColor &textBackColor, const QFont &delivResultFont,
                                const QColor &delivResultColor, const QFont &allResultFont,
                                const QColor &allResultColor, const QString &dateFormat)
{
    QCOMPARE(cs.textFont(), textFont);
    QCOMPARE(cs.textBackColor(), textBackColor);
    QCOMPARE(cs.delivResultFont(), delivResultFont);
    QCOMPARE(cs.delivResultColor(), delivResultColor);
    QCOMPARE(cs.allResultFont(), allResultFont);
    QCOMPARE(cs.allResultColor(), allResultColor);
    QCOMPARE(cs.dateFormat(), dateFormat);
}

void Test_CalcSettings::compareDefault(const CalcSettings &cs)
{
    QCOMPARE(cs.textFont(), SCC::DEF_TEXT_FONT);
    QCOMPARE(cs.textBackColor(), SCC::DEF_TEXT_BACK_COLOR);
    QCOMPARE(cs.delivResultFont(), SCC::DEF_DELIV_RESULT_FONT);
    QCOMPARE(cs.delivResultColor(), SCC::DEF_DELIV_RESULT_COLOR);
    QCOMPARE(cs.allResultFont(), SCC::DEF_ALL_RESULT_FONT);
    QCOMPARE(cs.allResultColor(), SCC::DEF_ALL_RESULT_COLOR);
    QCOMPARE(cs.dateFormat(), SC::defaultDateFormat());
}

