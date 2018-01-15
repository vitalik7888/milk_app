#include "Settings.h"

#include "SettingsConstants.h"
// Qt
#include <QSettings>
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
}

using SC = SettingsConstants;
using COLTYPE = SC::SettingsColumnType;


Settings::Settings(QObject *parent):
    Settings(QString(), parent)
{
}

Settings::Settings(const QString &fileName, QObject *parent):
    QObject(parent)
{
    fileName.isEmpty() ? m_settings = new QSettings(this) :
            m_settings = new QSettings(fileName, QSettings::NativeFormat, this);

    m_main = new MainSettings(this);

    m_print = new PrintSettings(this);
    m_calc = new CalcSettings(this);
}

Settings::~Settings()
{
}

void Settings::writeLastChoosenDb()
{
    m_settings->beginGroup(GROUP_MAIN);
    m_settings->setValue(LAST_CHOOSEN_DB, main()->lastChoosenDb());
    m_settings->endGroup();
}

void Settings::writeMainSettings()
{
    m_settings->beginGroup(GROUP_MAIN);

    m_settings->setValue(LAST_CHOOSEN_DB, main()->lastChoosenDb());
    m_settings->setValue(PRICE, main()->priceLiter());
    m_settings->setValue(FIRM_NAME, main()->firmName());
    m_settings->setValue(MILK_INSPECTOR, main()->milkInspector());
    m_settings->setValue(MILK_INSPECTOR_2, main()->milkInspector2());
    m_settings->setValue(FETCH_MORE, main()->isFetchTablesOnRefresh());

    m_settings->endGroup();
}

void Settings::writeCalcSettings()
{
    m_settings->beginGroup(GROUP_CALC);

    m_settings->setValue(C_DATE_FORMAT, calc()->dateFormat());
    m_settings->setValue(C_TEXT_FONT, calc()->textFont().toString());
    m_settings->setValue(C_TEXT_COLOR, calc()->textBackColor());
    m_settings->setValue(C_DELIV_RES_FONT, calc()->delivResultFont().toString());
    m_settings->setValue(C_DELIV_RES_COLOR, calc()->delivResultColor());
    m_settings->setValue(C_ALL_RES_FONT, calc()->allResultFont().toString());
    m_settings->setValue(C_ALL_RES_COLOR, calc()->allResultColor());

    m_settings->beginWriteArray(COL_ARRAY);
    for (int i = 0; i < calc()->settingsColumnsCount(); ++i) {
        m_settings->setArrayIndex(i);
        writeColumnToSettings(calc()->settingColumn(i));
    }
    m_settings->endArray();

    m_settings->endGroup();
}

void Settings::writePrintSettings()
{
    m_settings->beginGroup(GROUP_PRINT);

    m_settings->setValue(P_TEXT_FONT, print()->textFont());
    m_settings->setValue(P_CAPTION_FONT, print()->captionTextFont());
    m_settings->setValue(P_CAPTION_COLOR, print()->captionColor());
    m_settings->setValue(PT_WIDTH, print()->tableWidth());
    m_settings->setValue(PT_BORDER_WIDTH, print()->tableBorderWidth());
    m_settings->setValue(PT_BORDER_STYLE, print()->tableBorderStyle());
    m_settings->setValue(PT_CELL_SPACING, print()->cellSpacing());
    m_settings->setValue(PT_CELL_PADDING, print()->cellPadding());
    m_settings->setValue(PT_BORDER_COLOR, print()->tableBorderColor());
    m_settings->setValue(PT_HEADER_FONT, print()->tableHeaderFont());
    m_settings->setValue(PT_HEADER_COLOR, print()->tableHeaderColor());
    m_settings->setValue(PT_TEXT_FONT, print()->tableTextFont());
    m_settings->setValue(PT_TEXT_COLOR, print()->tableTextColor());
    m_settings->setValue(PT_RESULT_FONT, print()->tableResultFont());
    m_settings->setValue(PT_RESULT_COLOR, print()->tableResultColor());

    m_settings->beginWriteArray(COL_ARRAY);
    for (int i = 0; i < print()->settingsColumnsCount(); ++i) {
        m_settings->setArrayIndex(i);
        writeColumnToSettings(print()->settingColumn(i));
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

    main()->setLastChoosenDb(getString(LAST_CHOOSEN_DB, SC::M_DEF_LAST_CHOOSEN_DB));
    main()->setPriceLiter(getFloat(PRICE, SC::M_DEF_PRICE_LITER));
    main()->setFirmName(getString(FIRM_NAME, SC::M_DEF_FIRM_NAME));
    main()->setMilkInspector(getString(MILK_INSPECTOR, SC::M_DEF_MILK_INSPECTOR));
    main()->setMilkInspector2(getString(MILK_INSPECTOR_2, SC::M_M_DEF_MILK_INSPECTOR2));
    main()->setIsFetchTablesOnRefresh(getBool(FETCH_MORE, SC::M_DEF_IS_FETCH_TABLE_ON_REFRESH));

    m_settings->endGroup();
}

void Settings::readCalcSettings()
{
    m_settings->beginGroup(GROUP_CALC);

    calc()->setDateFormat(getString(C_DATE_FORMAT, SC::defaultDateFormat()));
    calc()->setTextFont(getFont(C_TEXT_FONT, SC::C_DEF_TEXT_FONT));
    calc()->setTextBackColor(getColor(C_TEXT_COLOR, SC::C_DEF_TEXT_BACK_COLOR));
    calc()->setDelivResultFont(getFont(C_DELIV_RES_FONT, SC::C_DEF_DELIV_RESULT_FONT.toString()));
    calc()->setDelivResultColor(getColor(C_DELIV_RES_COLOR, SC::C_DEF_DELIV_RESULT_COLOR));
    calc()->setAllResultFont(getFont(C_ALL_RES_FONT, SC::C_DEF_ALL_RESULT_FONT.toString()));
    calc()->setAllResultColor(getColor(C_ALL_RES_COLOR, SC::C_DEF_ALL_RESULT_COLOR));

    const int arraySize = m_settings->beginReadArray(COL_ARRAY);
    for (int i = 0; i < arraySize; ++i) {
        m_settings->setArrayIndex(i);
        auto column = calc()->getColumns()[i];
        column->setDisplay(getString(COL_DISPLAY, SC::COL_DEF_DISPLAY));
        column->setType(getInt(COL_TYPE, SC::COL_DEF_TYPE));
        column->setPrec(getInt(COL_PREC, SC::COL_DEF_PREC));
        column->setIsShow(getBool(COL_IS_SHOW, SC::COL_DEF_IS_SHOW));
    }
    m_settings->endArray();

    m_settings->endGroup();
}

void Settings::readPrintSettings()
{
    m_settings->beginGroup(GROUP_PRINT);

    print()->setTextFont(getFont(P_TEXT_FONT, SC::P_DEF_TEXT_FONT));
    print()->setCaptionTextFont(getFont(P_CAPTION_FONT, SC::P_DEF_CAPTION_TEXT_FONT));
    print()->setCaptionColor(getColor(P_CAPTION_COLOR, SC::P_DEF_CAPTION_COLOR));
    print()->setTableWidth(getInt(PT_WIDTH, SC::P_DEF_TABLE_WIDTH));
    print()->setTableBorderWidth(getInt(PT_BORDER_WIDTH, SC::P_DEF_TABLE_BORDER_WIDTH));
    print()->setTableBorderStyle(getInt(PT_BORDER_STYLE, SC::P_DEF_TABLE_BORDER_STYLE));
    print()->setCellSpacing(getInt(PT_CELL_SPACING, SC::P_DEF_CELL_SPACING));
    print()->setCellPadding(getInt(PT_CELL_PADDING, SC::P_DEF_CELL_PADDING));
    print()->setTableBorderColor(getColor(PT_BORDER_COLOR, SC::P_DEF_TABLE_BORDER_COLOR));
    print()->setTableHeaderFont(getFont(PT_HEADER_FONT, SC::P_DEF_TABLE_HEADER_FONT));
    print()->setTableHeaderColor(getColor(PT_HEADER_COLOR, SC::P_DEF_TABLE_HEADER_COLOR));
    print()->setTableTextFont(getFont(PT_TEXT_FONT, SC::P_DEF_TABLE_TEXT_FONT));
    print()->setTableTextColor(getColor(PT_TEXT_COLOR, SC::P_DEF_TABLE_TEXT_COLOR));
    print()->setTableResultFont(getFont(PT_RESULT_FONT, SC::P_DEF_TABLE_RESULT_FONT));
    print()->setTableResultColor(getColor(PT_RESULT_COLOR, SC::P_DEF_TABLE_RESULT_COLOR));

    const int arraySize = m_settings->beginReadArray(COL_ARRAY);
    for (int i = 0; i < arraySize; ++i) {
        m_settings->setArrayIndex(i);
        auto column = print()->getColumns()[i];
        column->setDisplay(getString(COL_DISPLAY, SC::COL_DEF_DISPLAY));
        column->setType(getInt(COL_TYPE, SC::COL_DEF_TYPE));
        column->setPrec(getInt(COL_PREC, SC::COL_DEF_PREC));
        column->setIsShow(getBool(COL_IS_SHOW, SC::COL_DEF_IS_SHOW));
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

void Settings::reset()
{
    resetMain();
    resetCalc();
    resetPrint();
}

void Settings::resetMain()
{
    main()->reset();
}

void Settings::resetCalc()
{
    calc()->reset();
}

void Settings::resetPrint()
{
    print()->reset();
}

void Settings::writeColumnToSettings(SettingsColumn *column)
{
    m_settings->setValue(COL_DISPLAY, column->display());
    m_settings->setValue(COL_PREC, column->prec());
    m_settings->setValue(COL_IS_SHOW, column->isShow());
    m_settings->setValue(COL_TYPE, column->type());
}

QString Settings::getString(const QString &key, const QString &defaultValue) const
{
    return m_settings->value(key, defaultValue).toString();
}

bool Settings::getBool(const QString &key, const bool defaultValue) const
{
    return m_settings->value(key, defaultValue).toBool();
}

int Settings::getInt(const QString &key, const int defaultValue) const
{
    return m_settings->value(key, defaultValue).toInt();
}

float Settings::getFloat(const QString &key, const float defaultValue) const
{
    return m_settings->value(key, defaultValue).toFloat();
}

QFont Settings::getFont(const QString &key, const QFont &defaultFont) const
{
    return m_settings->value(key, defaultFont).value<QFont>();
}

QColor Settings::getColor(const QString &key, const QColor &defaultColor) const
{
    return m_settings->value(key, defaultColor.name()).value<QColor>();
}
