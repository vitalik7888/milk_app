#include "Test_PrintSettings.h"

#include "PrintSettings.h"
#include "SettingsConstants.h"
// Qt
#include <QTest>
#include <QSignalSpy>
#include <QDebug>

using SC = SettingsConstants;


Test_PrintSettings::Test_PrintSettings(QObject *parent) : QObject(parent)
{

}

void Test_PrintSettings::testEmptyConstructor()
{
    PrintSettings ps;
    compareDefault(&ps);
}

void Test_PrintSettings::testMethods()
{
    PrintSettings ps;
    ps.setTextFont({"Times", 10, QFont::Bold});
    ps.setCaptionTextFont({"Times", 9, QFont::Bold});
    ps.setCaptionColor({Qt::black});
    ps.setTableWidth(2);
    ps.setTableBorderWidth(3);
    ps.setTableBorderStyle(4);
    ps.setCellSpacing(2);
    ps.setCellPadding(2);
    ps.setTableBorderColor({Qt::green});
    ps.setTableHeaderFont({"Times", 10, QFont::Bold});
    ps.setTableHeaderColor({Qt::red});
    ps.setTableTextFont({"Times", 11, QFont::Bold});
    ps.setTableTextColor({Qt::white});
    ps.setTableResultFont({"Times", 12, QFont::Bold});
    ps.setTableResultColor({Qt::gray});
    compare(&ps, {"Times", 10, QFont::Bold}, {"Times", 9, QFont::Bold}, {Qt::black}, 2, 3, 4, 2, 2, {Qt::green},
            {"Times", 10, QFont::Bold}, {Qt::red}, {"Times", 11, QFont::Bold}, {Qt::white}, {"Times", 12, QFont::Bold}, {Qt::gray});
}

void Test_PrintSettings::testReset()
{
    PrintSettings ps;
    ps.setTextFont({"Times", 10, QFont::Bold});
    ps.setCaptionTextFont({"Times", 9, QFont::Bold});
    ps.setCaptionColor({Qt::black});
    ps.setTableWidth(2);
    ps.setTableBorderWidth(3);
    ps.setTableBorderStyle(4);
    ps.setCellSpacing(2);
    ps.setCellPadding(2);
    ps.setTableBorderColor({Qt::green});
    ps.setTableHeaderFont({"Times", 10, QFont::Bold});
    ps.setTableHeaderColor({Qt::red});
    ps.setTableTextFont({"Times", 11, QFont::Bold});
    ps.setTableTextColor({Qt::white});
    ps.setTableResultFont({"Times", 12, QFont::Bold});
    ps.setTableResultColor({Qt::gray});
    ps.reset();
    compareDefault(&ps);
}

void Test_PrintSettings::testSignalTextFont()
{
    PrintSettings ps;
    const QFont data{"Times", 10, QFont::Bold};
    QSignalSpy signalSpy(&ps, &PrintSettings::textFontChanged);
    ps.setTextFont(data);
    ps.setTextFont(data);
    compareSignal(signalSpy, data, 1);
}

void Test_PrintSettings::testSignalCaptionTextFont()
{
    PrintSettings ps;
    const QFont data{"Times", 9, QFont::Bold};
    QSignalSpy signalSpy(&ps, &PrintSettings::captionTextFontChanged);
    ps.setCaptionTextFont(data);
    ps.setCaptionTextFont(data);
    compareSignal(signalSpy, data, 1);
}

void Test_PrintSettings::testSignalCaptionColor()
{
    PrintSettings ps;
    const QColor data{Qt::white};
    QSignalSpy signalSpy(&ps, &PrintSettings::captionColorChanged);
    ps.setCaptionColor(data);
    ps.setCaptionColor(data);
    compareSignal(signalSpy, data, 1);
}

void Test_PrintSettings::testSignalTableWidth()
{
    PrintSettings ps;
    const int data = 2;
    QSignalSpy signalSpy(&ps, &PrintSettings::tableWidthChanged);
    ps.setTableWidth(data);
    ps.setTableWidth(data);
    compareSignal(signalSpy, data, 1);
}

void Test_PrintSettings::testSignalTableBorderWidth()
{
    PrintSettings ps;
    const int data = SC::Print::DEF_TABLE_BORDER_WIDTH + 1;
    QSignalSpy signalSpy(&ps, &PrintSettings::tableBorderWidthChanged);
    ps.setTableBorderWidth(data);
    ps.setTableBorderWidth(data);
    compareSignal(signalSpy, data, 1);
}

void Test_PrintSettings::testSignalTableBorderStyle()
{
    PrintSettings ps;
    const int data = SC::Print::DEF_TABLE_BORDER_STYLE + 1;
    QSignalSpy signalSpy(&ps, &PrintSettings::tableBorderStyleChanged);
    ps.setTableBorderStyle(data);
    ps.setTableBorderStyle(data);
    compareSignal(signalSpy, data, 1);
}

void Test_PrintSettings::testSignalCellSpacing()
{
    PrintSettings ps;
    const int data = SC::Print::DEF_CELL_SPACING + 1;
    QSignalSpy signalSpy(&ps, &PrintSettings::cellSpacingChanged);
    ps.setCellSpacing(data);
    ps.setCellSpacing(data);
    compareSignal(signalSpy, data, 1);
}

void Test_PrintSettings::testSignalCellPadding()
{
    PrintSettings ps;
    const int data = SC::Print::DEF_CELL_PADDING + 1;
    QSignalSpy signalSpy(&ps, &PrintSettings::cellPaddingChanged);
    ps.setCellPadding(data);
    ps.setCellPadding(data);
    compareSignal(signalSpy, data, 1);
}

void Test_PrintSettings::testSignalTableBorderColor()
{
    PrintSettings ps;
    const QColor data{Qt::white};
    QSignalSpy signalSpy(&ps, &PrintSettings::tableBorderColorChanged);
    ps.setTableBorderColor(data);
    ps.setTableBorderColor(data);
    compareSignal(signalSpy, data, 1);
}

void Test_PrintSettings::testSignalTableHeaderFont()
{
    PrintSettings ps;
    const QFont data{"Times", 9, QFont::Bold};
    QSignalSpy signalSpy(&ps, &PrintSettings::tableHeaderFontChanged);
    ps.setTableHeaderFont(data);
    ps.setTableHeaderFont(data);
    compareSignal(signalSpy, data, 1);
}

void Test_PrintSettings::testSignalTableHeaderColor()
{
    PrintSettings ps;
    const QColor data{Qt::white};
    QSignalSpy signalSpy(&ps, &PrintSettings::tableHeaderColorChanged);
    ps.setTableHeaderColor(data);
    ps.setTableHeaderColor(data);
    compareSignal(signalSpy, data, 1);
}

void Test_PrintSettings::testSignalTableTextFont()
{
    PrintSettings ps;
    const QFont data{"Times", 9, QFont::Bold};
    QSignalSpy signalSpy(&ps, &PrintSettings::tableTextFontChanged);
    ps.setTableTextFont(data);
    ps.setTableTextFont(data);
    compareSignal(signalSpy, data, 1);
}

void Test_PrintSettings::testSignalTableTextColor()
{
    PrintSettings ps;
    const QColor data{Qt::gray};
    QSignalSpy signalSpy(&ps, &PrintSettings::tableTextColorChanged);
    ps.setTableTextColor(data);
    ps.setTableTextColor(data);
    compareSignal(signalSpy, data, 1);
}

void Test_PrintSettings::testSignalTableResultFont()
{
    PrintSettings ps;
    const QFont data{"Times", 9, QFont::Bold};
    QSignalSpy signalSpy(&ps, &PrintSettings::tableResultFontChanged);
    ps.setTableResultFont(data);
    ps.setTableResultFont(data);
    compareSignal(signalSpy, data, 1);
}

void Test_PrintSettings::testSignalTableResultColor()
{
    PrintSettings ps;
    const QColor data{Qt::green};
    QSignalSpy signalSpy(&ps, &PrintSettings::tableResultColorChanged);
    ps.setTableResultColor(data);
    ps.setTableResultColor(data);
    compareSignal(signalSpy, data, 1);
}

void Test_PrintSettings::compare(PrintSettings *ps, const QFont &textFont,
                                 const QFont &captionTextFont, const QColor &captionColor,
                                 const int tableWidth, const int tableBorderWidth,
                                 const int tableBorderStyle, const int cellSpacing,
                                 const int cellPadding, const QColor &tableBorderColor,
                                 const QFont &tableHeaderFont, const QColor &tableHeaderColor,
                                 const QFont &tableTextFont, const QColor &tableTextColor,
                                 const QFont &tableResultFont, const QColor &tableResultColor)
{
    QCOMPARE(ps->textFont(), textFont);
    QCOMPARE(ps->captionTextFont(), captionTextFont);
    QCOMPARE(ps->captionColor(), captionColor);
    QCOMPARE(ps->tableWidth(), tableWidth);
    QCOMPARE(ps->tableBorderWidth(), tableBorderWidth);
    QCOMPARE(ps->tableBorderStyle(), tableBorderStyle);
    QCOMPARE(ps->cellSpacing(), cellSpacing);
    QCOMPARE(ps->cellPadding(), cellPadding);
    QCOMPARE(ps->tableBorderColor(), tableBorderColor);
    QCOMPARE(ps->tableHeaderFont(), tableHeaderFont);
    QCOMPARE(ps->tableHeaderColor(), tableHeaderColor);
    QCOMPARE(ps->tableTextFont(), tableTextFont);
    QCOMPARE(ps->tableTextColor(), tableTextColor);
    QCOMPARE(ps->tableResultFont(), tableResultFont);
    QCOMPARE(ps->tableResultColor(), tableResultColor);
}

void Test_PrintSettings::compareDefault(PrintSettings *ps)
{
    compare(ps, SC::Print::DEF_TEXT_FONT, SC::Print::DEF_CAPTION_TEXT_FONT,
            SC::Print::DEF_CAPTION_COLOR, SC::Print::DEF_TABLE_WIDTH,
            SC::Print::DEF_TABLE_BORDER_WIDTH, SC::Print::DEF_TABLE_BORDER_STYLE,
            SC::Print::DEF_CELL_SPACING, SC::Print::DEF_CELL_PADDING,
            SC::Print::DEF_TABLE_BORDER_COLOR, SC::Print::DEF_TABLE_HEADER_FONT,
            SC::Print::DEF_TABLE_HEADER_COLOR, SC::Print::DEF_TABLE_TEXT_FONT,
            SC::Print::DEF_TABLE_TEXT_COLOR, SC::Print::DEF_TABLE_RESULT_FONT, SC::Print::DEF_TABLE_RESULT_COLOR);
}

void Test_PrintSettings::compareSignal(const QSignalSpy &spy, const QVariant &value, const int count)
{
    QCOMPARE(spy.count(), count);
    const QVariantList arguments = spy.first();
    QCOMPARE(arguments.at(0), value);
}
