#include "Settings.h"

#include "Constants.h"

// Qt
#include <QDebug>

namespace
{
static const char *GROUP_MAIN = "main";
static const char *FETCH_MORE = "fetchMore";
static const char *PRICE = "price";
static const char *LAST_CHOOSEN_DB = "lastChoosenDb";
static const char *FIRM_NAME = "firmName";
static const char *MILK_INSPECTOR = "milkInspector";
static const char *MILK_INSPECTOR_2 = "milkInspector2";

static const char *COL_ARRAY = "columns";
static const char *COL_DISPLAY = "display";
static const char *COL_PREC = "prec";
static const char *COL_IS_SHOW = "isShow";
static const char *COL_TYPE = "type";

static const char *GROUP_PRINT = "print";
static const char *P_TEXT_FONT = "textFont";
static const char *P_CAPTION_FONT = "captionFont";
static const char *P_CAPTION_COLOR = "captionColor";
static const char *PT_WIDTH = "tableWidth";
static const char *PT_BORDER_WIDTH = "tableBorderWidth";
static const char *PT_BORDER_STYLE = "tableBorderStyle";
static const char *PT_CELL_SPACING = "cellSpacing";
static const char *PT_CELL_PADDING = "cellPadding";
static const char *PT_BORDER_COLOR = "tableBorderColor";
static const char *PT_HEADER_FONT = "tableHeaderFont";
static const char *PT_HEADER_COLOR = "tableHeaderColor";
static const char *PT_TEXT_FONT = "tableTextFont";
static const char *PT_TEXT_COLOR = "tableTextColor";
static const char *PT_RESULT_FONT = "tableResultFont";
static const char *PT_RESULT_COLOR = "tableResultColor";

static const char *GROUP_CALC = "calc";
static const char *C_DATE_FORMAT = "dateFormat";
static const char *C_TEXT_FONT = "textFont";
static const char *C_TEXT_COLOR = "textColor";
static const char *C_DELIV_RES_FONT = "delivResFont";
static const char *C_DELIV_RES_COLOR = "delivResColor";
static const char *C_ALL_RES_FONT = "allResFont";
static const char *C_ALL_RES_COLOR = "allResColor";

static const char *TEXT_FONT_VALUE = "Noto Sans,9,-1,5,50,0,0,0,0,0";
static const char *CAPTION_FONT_VALUE = "Noto Sans,12,-1,5,75,0,0,0,0,0";
static const char *HEAD_FONT_VALUE = "Noto Sans,10,-1,5,75,0,0,0,0,0";
static const char *TAB_RES_FONT_VALUE = "Noto Sans,9,-1,5,75,1,0,0,0,0";
static const char *TAB_FONT_VALUE = "Noto Sans,10,-1,5,50,0,0,0,0,0";

using COLTYPE = Constants::ColumnType;

static inline QString qtr(const char *value)
{
    return QObject::tr(value);
}

static inline int toInt(const COLTYPE column)
{
    return static_cast<int>(column);
}
}


Settings::Settings():
    m_settings(new QSettings(Constants::organization(), Constants::appName()))
{
}

Settings::~Settings()
{
}

void Settings::writeMainSettings()
{
    m_settings->beginGroup(GROUP_MAIN);

    setValue(LAST_CHOOSEN_DB, m_main.lastChoosenDb);
    setValue(PRICE, m_main.priceLiter);
    setValue(FIRM_NAME, m_main.firmName);
    setValue(MILK_INSPECTOR, m_main.milkInspector);
    setValue(MILK_INSPECTOR_2, m_main.milkInspector_2);
    setValue(FETCH_MORE, m_main.isFetchTablesOnRefresh);

    m_settings->endGroup();
}

void Settings::writeCalcSettings()
{
    m_settings->beginGroup(GROUP_CALC);

    setValue(C_DATE_FORMAT, m_calc.dateFormat);
    setValue(C_TEXT_FONT, m_calc.textFont.toString());
    setValue(C_TEXT_COLOR, m_calc.textBackColor.name());
    setValue(C_DELIV_RES_FONT, m_calc.delivResultFont.toString());
    setValue(C_DELIV_RES_COLOR, m_calc.delivResultColor.name());
    setValue(C_ALL_RES_FONT, m_calc.allResultFont.toString());
    setValue(C_ALL_RES_COLOR, m_calc.allResultColor.name());

    m_settings->beginWriteArray(COL_ARRAY);
    for (int i = 0; i < m_calc.columns.size(); ++i) {
        m_settings->setArrayIndex(i);
        writeColumnToSettings(m_calc.columns[i]);
    }
    m_settings->endArray();

    m_settings->endGroup();
}

void Settings::writePrintSettings()
{
    m_settings->beginGroup(GROUP_PRINT);

    setValue(P_TEXT_FONT, m_print.textFont.toString());
    setValue(P_CAPTION_FONT, m_print.captionTextFont.toString());
    setValue(P_CAPTION_COLOR, m_print.captionColor.name());
    setValue(PT_WIDTH, m_print.tableWidth);
    setValue(PT_BORDER_WIDTH, m_print.tableBorderWidth);
    setValue(PT_BORDER_STYLE, m_print.tableBorderStyle);
    setValue(PT_CELL_SPACING, m_print.cellSpacing);
    setValue(PT_CELL_PADDING, m_print.cellPadding);
    setValue(PT_BORDER_COLOR, m_print.tableBorderColor.name());
    setValue(PT_HEADER_FONT, m_print.tableHeaderFont.toString());
    setValue(PT_HEADER_COLOR, m_print.tableHeaderColor.name());
    setValue(PT_TEXT_FONT, m_print.tableTextFont.toString());
    setValue(PT_TEXT_COLOR, m_print.tableTextColor.name());
    setValue(PT_RESULT_FONT, m_print.tableResultFont.toString());
    setValue(PT_RESULT_COLOR, m_print.tableResultColor.name());

    m_settings->beginWriteArray(COL_ARRAY);
    for (int i = 0; i < m_print.columns.size(); ++i) {
        m_settings->setArrayIndex(i);
        writeColumnToSettings(m_print.columns[i]);
    }
    m_settings->endArray();

    m_settings->endGroup();
}

void Settings::writeSettings()
{
    writeMainSettings();
    writeCalcSettings();
    writePrintSettings();
}

void Settings::readMainSettings()
{
    m_settings->beginGroup(GROUP_MAIN);

    m_main = {
        value(LAST_CHOOSEN_DB, QString()).toString(),
        value(PRICE, .0f).toFloat(),
        value(FIRM_NAME, QString()).toString(),
        value(MILK_INSPECTOR, QString()).toString(),
        value(MILK_INSPECTOR_2, QString()).toString(),
        value(FETCH_MORE, false).toBool() };

    m_settings->endGroup();
}

void Settings::readCalcSettings()
{
    m_settings->beginGroup(GROUP_CALC);

    m_calc.dateFormat = value(C_DATE_FORMAT, Constants::defaultDateFormat()).toString();
    m_calc.textFont.fromString(value(C_TEXT_FONT, QFont().toString()).toString());
    m_calc.textBackColor.setNamedColor(value(C_TEXT_COLOR, QColor(Qt::white).name()).toString());
    m_calc.delivResultFont.fromString(value(C_DELIV_RES_FONT, QFont().toString()).toString());
    m_calc.delivResultColor.setNamedColor(value(C_DELIV_RES_COLOR, QColor(Qt::lightGray).name()).toString());
    m_calc.allResultFont.fromString(value(C_ALL_RES_FONT, QFont().toString()).toString());
    m_calc.allResultColor.setNamedColor(value(C_ALL_RES_COLOR, QColor(Qt::GlobalColor::darkGray).name()).toString());

    const auto size = m_settings->beginReadArray(COL_ARRAY);
    if (size == 0)
        setDefaultCalcColumns();
    else {
        m_calc.columns.clear();

        for (int i = 0; i < size; ++i) {
            m_settings->setArrayIndex(i);
            m_calc.columns.append(getColumnFromSettings());
        }
    }
    m_settings->endArray();

    m_settings->endGroup();
}

void Settings::readPrintSettings()
{
    m_settings->beginGroup(GROUP_PRINT);

    const auto blackColorName = QColor(Qt::black).name();

    m_print.textFont.fromString(value(P_TEXT_FONT, TEXT_FONT_VALUE).toString());
    m_print.captionTextFont.fromString(value(P_CAPTION_FONT, CAPTION_FONT_VALUE).toString());
    m_print.captionColor.setNamedColor(value(P_CAPTION_COLOR, blackColorName).toString());
    m_print.tableWidth = value(PT_WIDTH, 100).toInt();
    m_print.tableBorderWidth = value(PT_BORDER_WIDTH, 2).toInt();
    m_print.tableBorderStyle = value(PT_BORDER_STYLE, 3).toInt();
    m_print.cellSpacing = value(PT_CELL_SPACING, 0).toInt();
    m_print.cellPadding = value(PT_CELL_PADDING, 2).toInt();
    m_print.tableBorderColor.setNamedColor(value(PT_BORDER_COLOR, blackColorName).toString());
    m_print.tableHeaderFont.fromString(value(PT_HEADER_FONT, HEAD_FONT_VALUE).toString());
    m_print.tableHeaderColor.setNamedColor(value(PT_HEADER_COLOR, blackColorName).toString());
    m_print.tableTextFont.fromString(value(PT_TEXT_FONT, TAB_FONT_VALUE).toString());
    m_print.tableTextColor.setNamedColor(value(PT_TEXT_COLOR, blackColorName).toString());
    m_print.tableResultFont.fromString(value(PT_RESULT_FONT, TAB_RES_FONT_VALUE).toString());
    m_print.tableResultColor.setNamedColor(value(PT_RESULT_COLOR, blackColorName).toString());

    const auto size = m_settings->beginReadArray(COL_ARRAY);
    if (size == 0)
        setDefaultPrintColumns();
    else {
        m_print.columns.clear();

        for (int i = 0; i < size; ++i) {
            m_settings->setArrayIndex(i);
            m_print.columns.append(getColumnFromSettings());
        }
    }
    m_settings->endArray();

    m_settings->endGroup();
}

void Settings::readSettings()
{
    readMainSettings();
    readCalcSettings();
    readPrintSettings();
}

void Settings::setDefaultMainSettings()
{
    m_main = {};
}

void Settings::setDefaultPrintSettings()
{
    QFont textFont, tabCaptionFont, tabHeadFont, tabResFont, tabTextFont;

    textFont.fromString(TEXT_FONT_VALUE);
    tabCaptionFont.fromString(CAPTION_FONT_VALUE);
    tabHeadFont.fromString(HEAD_FONT_VALUE);
    tabResFont.fromString(TAB_RES_FONT_VALUE);
    tabTextFont.fromString(TAB_FONT_VALUE);

    m_print = { textFont, tabCaptionFont, {Qt::black}, 100, 2, 3, 0, 2, {Qt::black},
                tabHeadFont, {Qt::black}, tabTextFont, {Qt::black}, tabResFont, {Qt::black}};

    setDefaultPrintColumns();
}

void Settings::setDefaultSettings()
{
    setDefaultMainSettings();
    setDefaultCalcSettings();
    setDefaultPrintSettings();
}

void Settings::setDefaultCalcSettings()
{
    m_calc = { Constants::defaultDateFormat(),
               QFont(), QColor(Qt::GlobalColor::white),
               QFont(), QColor(Qt::GlobalColor::lightGray),
               QFont(), QColor(Qt::GlobalColor::darkGray)
             };

    setDefaultCalcColumns();
}

void Settings::setDefaultCalcColumns()
{
    m_calc.columns = {
        {qtr("Ф. И. О."), toInt(COLTYPE::String)},
        {qtr("Молокопункты"), toInt(COLTYPE::String)},
        {qtr("Дата сдачи"), toInt(COLTYPE::Date)},
        {qtr("Цена за литр"), toInt(COLTYPE::Double)},
        {qtr("Литры"), toInt(COLTYPE::Double)},
        {qtr("Жиры"), toInt(COLTYPE::Double)},
        {qtr("Белок"), toInt(COLTYPE::Double)},
        {qtr("Жироед."), toInt(COLTYPE::Double)},
        {qtr("Зачет. вес"), toInt(COLTYPE::Double)},
        {qtr("Оплата(без премии)"), toInt(COLTYPE::Double)},
        {qtr("Премия"), toInt(COLTYPE::Double)},
        {qtr("Сумма"), toInt(COLTYPE::Double)}
    };
}

void Settings::setDefaultPrintColumns()
{
    m_print.columns = {
        {qtr("№ п/п"), toInt(COLTYPE::SerialNumber)},
        {qtr("Ф. И. О."), toInt(COLTYPE::String)},
        {qtr("Физ. вес"), toInt(COLTYPE::Double)},
        {qtr("% жир"), toInt(COLTYPE::Double)},
        {qtr("Белок"), toInt(COLTYPE::Double)},
        {qtr("Жироед."), toInt(COLTYPE::Double), false},
        {qtr("Зачет. вес"), toInt(COLTYPE::Double)},
        {qtr("Оплата(без премии)"), toInt(COLTYPE::Double), false},
        {qtr("Премия"), toInt(COLTYPE::Double), false},
        {qtr("Сумма"), toInt(COLTYPE::Double)},
        {qtr("Подпись"), toInt(COLTYPE::String)}
    };
}

Settings::Column Settings::getColumnFromSettings() const
{
    return {
        value(COL_DISPLAY).toString(),
                value(COL_TYPE).toInt(),
                value(COL_PREC).toInt(),
                value(COL_IS_SHOW).toBool()
    };
}

void Settings::writeColumnToSettings(const Settings::Column &column)
{
    setValue(COL_DISPLAY, column.display);
    setValue(COL_PREC, column.prec);
    setValue(COL_IS_SHOW, column.isShow);
    setValue(COL_TYPE, column.type);
}

void Settings::setValue(const QString &key, const QVariant &value)
{
    m_settings->setValue(key, value);
}

QVariant Settings::value(const QString &key, const QVariant &defaultValue) const
{
    return m_settings->value(key, defaultValue);
}
