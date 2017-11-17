#include "Settings.h"

#include "SettingsConstants.h"
#include <Constants.h>
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

using SC = SettingsConstants;
using SCC = SettingsConstants::Column;
using COLTYPE = SC::SettingsColumnType;

static inline QString qtr(const char *value)
{
    return QObject::tr(value);
}
}


Settings::Settings(QObject *parent):
    QObject(parent)
{
    m_settings = new QSettings(Constants::organization(), Constants::appName(), this);

    m_main = new MainSettings(this);

    m_print = new PrintSettings(this);
    print()->appendSettingsColumn(new SettingsColumn(qtr("№ п/п"), COLTYPE::SerialNumber, SCC::DEF_PREC, true, print()));
    print()->appendSettingsColumn(new SettingsColumn(qtr("Ф. И. О."), COLTYPE::String, SCC::DEF_PREC, true, print()));
    print()->appendSettingsColumn(new SettingsColumn(qtr("Физ. вес"), COLTYPE::Double, SCC::DEF_PREC, true, print()));
    print()->appendSettingsColumn(new SettingsColumn(qtr("% жир"), COLTYPE::Double, SCC::DEF_PREC, true, print()));
    print()->appendSettingsColumn(new SettingsColumn(qtr("Белок"), COLTYPE::Double, SCC::DEF_PREC, true, print()));
    print()->appendSettingsColumn(new SettingsColumn(qtr("Жироед."), COLTYPE::Double, SCC::DEF_PREC, false, print()));
    print()->appendSettingsColumn(new SettingsColumn(qtr("Зачет. вес"), COLTYPE::Double, SCC::DEF_PREC, true, print()));
    print()->appendSettingsColumn(new SettingsColumn(qtr("Оплата(без премии)"), COLTYPE::Double, SCC::DEF_PREC, false, print()));
    print()->appendSettingsColumn(new SettingsColumn(qtr("Премия"), COLTYPE::Double, SCC::DEF_PREC, false, print()));
    print()->appendSettingsColumn(new SettingsColumn(qtr("Сумма"), COLTYPE::Double, SCC::DEF_PREC, true, print()));
    print()->appendSettingsColumn(new SettingsColumn(qtr("Подпись"), COLTYPE::String, SCC::DEF_PREC, true, print()));


    m_calc = new CalcSettings(this);
    calc()->appendSettingsColumn(new SettingsColumn(qtr("Ф. И. О."), COLTYPE::String, SCC::DEF_PREC, true, calc()));
    calc()->appendSettingsColumn(new SettingsColumn(qtr("Молокопункты"), COLTYPE::String, SCC::DEF_PREC, true, calc()));
    calc()->appendSettingsColumn(new SettingsColumn(qtr("Дата сдачи"), COLTYPE::Date, SCC::DEF_PREC, true, calc()));
    calc()->appendSettingsColumn(new SettingsColumn(qtr("Цена за литр"), COLTYPE::Double, SCC::DEF_PREC, true, calc()));
    calc()->appendSettingsColumn(new SettingsColumn(qtr("Литры"), COLTYPE::Double, SCC::DEF_PREC, true, calc()));
    calc()->appendSettingsColumn(new SettingsColumn(qtr("Жиры"), COLTYPE::Double, SCC::DEF_PREC, true, calc()));
    calc()->appendSettingsColumn(new SettingsColumn(qtr("Белок"), COLTYPE::Double, SCC::DEF_PREC, true, calc()));
    calc()->appendSettingsColumn(new SettingsColumn(qtr("Жироед."), COLTYPE::Double, SCC::DEF_PREC, true, calc()));
    calc()->appendSettingsColumn(new SettingsColumn(qtr("Зачет. вес"), COLTYPE::Double, SCC::DEF_PREC, true, calc()));
    calc()->appendSettingsColumn(new SettingsColumn(qtr("Оплата(без премии)"), COLTYPE::Double, SCC::DEF_PREC, true, calc()));
    calc()->appendSettingsColumn(new SettingsColumn(qtr("Премия"), COLTYPE::Double, SCC::DEF_PREC, true, calc()));
    calc()->appendSettingsColumn(new SettingsColumn(qtr("Сумма"), COLTYPE::Double, SCC::DEF_PREC, true, calc()));
}

Settings::~Settings()
{
}

void Settings::writeMainSettings()
{
    m_settings->beginGroup(GROUP_MAIN);

    setValue(LAST_CHOOSEN_DB, main()->lastChoosenDb());
    setValue(PRICE, main()->priceLiter());
    setValue(FIRM_NAME, main()->firmName());
    setValue(MILK_INSPECTOR, main()->milkInspector());
    setValue(MILK_INSPECTOR_2, main()->milkInspector2());
    setValue(FETCH_MORE, main()->isFetchTablesOnRefresh());

    m_settings->endGroup();
}

void Settings::writeCalcSettings()
{
    m_settings->beginGroup(GROUP_CALC);

    setValue(C_DATE_FORMAT, calc()->dateFormat());
    setValue(C_TEXT_FONT, calc()->textFont().toString());
    setValue(C_TEXT_COLOR, calc()->textBackColor().name());
    setValue(C_DELIV_RES_FONT, calc()->delivResultFont().toString());
    setValue(C_DELIV_RES_COLOR, calc()->delivResultColor().name());
    setValue(C_ALL_RES_FONT, calc()->allResultFont().toString());
    setValue(C_ALL_RES_COLOR, calc()->allResultColor().name());

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

    setValue(P_TEXT_FONT, print()->textFont().toString());
    setValue(P_CAPTION_FONT, print()->captionTextFont().toString());
    setValue(P_CAPTION_COLOR, print()->captionColor().name());
    setValue(PT_WIDTH, print()->tableWidth());
    setValue(PT_BORDER_WIDTH, print()->tableBorderWidth());
    setValue(PT_BORDER_STYLE, print()->tableBorderStyle());
    setValue(PT_CELL_SPACING, print()->cellSpacing());
    setValue(PT_CELL_PADDING, print()->cellPadding());
    setValue(PT_BORDER_COLOR, print()->tableBorderColor().name());
    setValue(PT_HEADER_FONT, print()->tableHeaderFont().toString());
    setValue(PT_HEADER_COLOR, print()->tableHeaderColor().name());
    setValue(PT_TEXT_FONT, print()->tableTextFont().toString());
    setValue(PT_TEXT_COLOR, print()->tableTextColor().name());
    setValue(PT_RESULT_FONT, print()->tableResultFont().toString());
    setValue(PT_RESULT_COLOR, print()->tableResultColor().name());

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

    main()->setLastChoosenDb(value(LAST_CHOOSEN_DB, SC::DEF_LAST_CHOOSEN_DB).toString());
    main()->setPriceLiter(value(PRICE, SC::DEF_PRICE_LITER).toFloat());
    main()->setFirmName(value(FIRM_NAME, SC::DEF_FIRM_NAME).toString());
    main()->setMilkInspector(value(MILK_INSPECTOR, SC::DEF_MILK_INSPECTOR).toString());
    main()->setMilkInspector2(value(MILK_INSPECTOR_2, SC::DEF_MILK_INSPECTOR2).toString());
    main()->setIsFetchTablesOnRefresh(value(FETCH_MORE, SC::DEF_IS_FETCH_TABLE_ON_REFRESH).toBool());

    m_settings->endGroup();
}

void Settings::readCalcSettings()
{
    m_settings->beginGroup(GROUP_CALC);

    calc()->setDateFormat(value(C_DATE_FORMAT, SC::defaultDateFormat()).toString());
    calc()->setTextFont(value(C_TEXT_FONT, SC::Calc::DEF_TEXT_FONT).toString());
    calc()->setTextBackColor(value(C_TEXT_COLOR, SC::Calc::DEF_TEXT_BACK_COLOR.name()).toString());
    calc()->setDelivResultFont(value(C_DELIV_RES_FONT, SC::Calc::DEF_DELIV_RESULT_FONT.toString()).toString());
    calc()->setDelivResultColor(value(C_DELIV_RES_COLOR, SC::Calc::DEF_DELIV_RESULT_COLOR.name()).toString());
    calc()->setAllResultFont(value(C_ALL_RES_FONT, SC::Calc::DEF_ALL_RESULT_FONT.toString()).toString());
    calc()->setAllResultColor(value(C_ALL_RES_COLOR, SC::Calc::DEF_ALL_RESULT_COLOR.name()).toString());

    const auto size = m_settings->beginReadArray(COL_ARRAY);
    for (int i = 0; i < size; ++i) {
        m_settings->setArrayIndex(i);
        calc()->appendSettingsColumn(new SettingsColumn(value(COL_DISPLAY).toString(),
                                                        value(COL_TYPE).toInt(),
                                                        value(COL_PREC).toInt(),
                                                        value(COL_IS_SHOW).toBool(),
                                                        calc()));
    }
    m_settings->endArray();

    m_settings->endGroup();
}

void Settings::readPrintSettings()
{
    m_settings->beginGroup(GROUP_PRINT);

    print()->setTextFont(value(P_TEXT_FONT, SC::Print::DEF_TEXT_FONT).toString());
    print()->setCaptionTextFont(value(P_CAPTION_FONT, SC::Print::DEF_CAPTION_TEXT_FONT).toString());
    print()->setCaptionColor(value(P_CAPTION_COLOR, SC::Print::DEF_CAPTION_COLOR.name()).toString());
    print()->setTableWidth(value(PT_WIDTH, SC::Print::DEF_TABLE_WIDTH).toInt());
    print()->setTableBorderWidth(value(PT_BORDER_WIDTH, SC::Print::DEF_TABLE_BORDER_WIDTH).toInt());
    print()->setTableBorderStyle(value(PT_BORDER_STYLE, SC::Print::DEF_TABLE_BORDER_STYLE).toInt());
    print()->setCellSpacing(value(PT_CELL_SPACING, SC::Print::DEF_CELL_SPACING).toInt());
    print()->setCellPadding(value(PT_CELL_PADDING, SC::Print::DEF_CELL_PADDING).toInt());
    print()->setTableBorderColor(value(PT_BORDER_COLOR, SC::Print::DEF_TABLE_BORDER_COLOR.name()).toString());
    print()->setTableHeaderFont(value(PT_HEADER_FONT, SC::Print::DEF_TABLE_HEADER_FONT).toString());
    print()->setTableHeaderColor(value(PT_HEADER_COLOR, SC::Print::DEF_TABLE_HEADER_COLOR).toString());
    print()->setTableTextFont(value(PT_TEXT_FONT, SC::Print::DEF_TABLE_TEXT_FONT).toString());
    print()->setTableTextColor(value(PT_TEXT_COLOR, SC::Print::DEF_TABLE_TEXT_COLOR.name()).toString());
    print()->setTableResultFont(value(PT_RESULT_FONT, SC::Print::DEF_TABLE_RESULT_FONT).toString());
    print()->setTableResultColor(value(PT_RESULT_COLOR, SC::Print::DEF_TABLE_RESULT_COLOR.name()).toString());

    const auto size = m_settings->beginReadArray(COL_ARRAY);

    for (int i = 0; i < size; ++i) {
            m_settings->setArrayIndex(i);
            print()->appendSettingsColumn(
                        new SettingsColumn(
                            value(COL_DISPLAY).toString(),
                            value(COL_TYPE).toInt(),
                            value(COL_PREC).toInt(),
                            value(COL_IS_SHOW).toBool(),
                            print()));
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
    setValue(COL_DISPLAY, column->display());
    setValue(COL_PREC, column->prec());
    setValue(COL_IS_SHOW, column->isShow());
    setValue(COL_TYPE, column->type());
}

void Settings::setValue(const QString &key, const QVariant &value)
{
    m_settings->setValue(key, value);
}

QVariant Settings::value(const QString &key, const QVariant &defaultValue) const
{
    return m_settings->value(key, defaultValue);
}
