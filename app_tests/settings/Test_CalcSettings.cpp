#include "Test_CalcSettings.h"

#include "Test_SettingsColumn.h"
#include <CalcSettings.h>
// Qt
#include <QSignalSpy>
#include <QTest>
#include <SettingsColumn.h>

using SC = SettingsConstants;


Test_CalcSettings::Test_CalcSettings(QObject *parent) : QObject(parent)
{

}

void Test_CalcSettings::testEmptyConstructor()
{
    CalcSettings cs;
    compareDefault(&cs);
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
    const SC::SettingsColumns columns = {
        new SettingsColumn("a", 1, 2, true, &cs),
        new SettingsColumn("b", 2, 1, false, &cs)
    };
    cs.setSettingsColumns(columns);

    compare(&cs, {"Times", 10, QFont::Bold}, {Qt::black},
    {"Times", 11, QFont::Bold}, {Qt::white}, {"Times", 12, QFont::Bold}, {Qt::green}, "MMMM", columns);
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
    cs.setSettingsColumns({
                              new SettingsColumn("a", 1, 2, true, &cs),
                              new SettingsColumn("b", 2, 1, false, &cs)
                          });
    cs.reset();

    compareDefault(&cs);
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

void Test_CalcSettings::compare(CalcSettings *cs, const QFont &textFont,
                                const QColor &textBackColor, const QFont &delivResultFont,
                                const QColor &delivResultColor, const QFont &allResultFont,
                                const QColor &allResultColor, const QString &dateFormat,
                                const SC::SettingsColumns &columns)
{
    QCOMPARE(cs->textFont(), textFont);
    QCOMPARE(cs->textBackColor(), textBackColor);
    QCOMPARE(cs->delivResultFont(), delivResultFont);
    QCOMPARE(cs->delivResultColor(), delivResultColor);
    QCOMPARE(cs->allResultFont(), allResultFont);
    QCOMPARE(cs->allResultColor(), allResultColor);
    QCOMPARE(cs->dateFormat(), dateFormat);
    const auto csColumns = cs->getColumns();
    QCOMPARE(csColumns.size(), columns.size());
    for (int i = 0; i < csColumns.size(); ++i) {
        SettingsColumn *column = columns[i];
        Test_SettingsColumn::compare(csColumns[i], column->display(), column->type(),
                                     column->prec(), column->isShow());
    }
}

void Test_CalcSettings::compareDefault(CalcSettings *cs)
{
    compare(cs, SC::C_DEF_TEXT_FONT, SC::C_DEF_TEXT_BACK_COLOR,
            SC::C_DEF_DELIV_RESULT_FONT, SC::C_DEF_DELIV_RESULT_COLOR,
            SC::C_DEF_ALL_RESULT_FONT, SC::C_DEF_ALL_RESULT_COLOR, SC::defaultDateFormat(), {});
}

