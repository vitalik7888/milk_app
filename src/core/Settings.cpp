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
//--------------------------------
MainSettings::MainSettings(const QString &lastChoosenDb, const float priceLiter, const QString &firmName,
                           const QString &milkInspector, const QString &milkInspector_2,
                           const bool isFetchTablesOnRefresh, QObject *parent) :
    QObject(parent),
    m_data({lastChoosenDb, priceLiter, firmName, milkInspector, milkInspector_2,
    isFetchTablesOnRefresh})
{

}

MainSettings::MainSettings(QObject *parent):
    MainSettings(QString(), .0f, QString(), QString(), QString(), false, parent)
{

}

MainSettings::~MainSettings()
{
}

void MainSettings::setLastChoosenDb(const QString &lastChoosenDb)
{
    m_data.lastChoosenDb = lastChoosenDb;
}

void MainSettings::setPriceLiter(float priceLiter)
{
    m_data.priceLiter = priceLiter;
}

void MainSettings::setFirmName(const QString &firmName)
{
    m_data.firmName = firmName;
}

void MainSettings::setMilkInspector(const QString &milkInspector)
{
    m_data.milkInspector = milkInspector;
}

void MainSettings::setMilkInspector_2(const QString &milkInspector_2)
{
    m_data.milkInspector_2 = milkInspector_2;
}

void MainSettings::setIsFetchTablesOnRefresh(const bool isFetchTablesOnRefresh)
{
    m_data.isFetchTablesOnRefresh = isFetchTablesOnRefresh;
}

void MainSettings::reset()
{
    setLastChoosenDb(QString());
    setPriceLiter(.0f);
    setFirmName(QString());
    setMilkInspector(QString());
    setMilkInspector_2(QString());
    setIsFetchTablesOnRefresh(false);
}
//-------------------------------
void SettingsColumn::setDisplay(const QString &display)
{
    m_data.display = display;
}

void SettingsColumn::setType(const int type)
{
    m_data.type = type;
}

void SettingsColumn::setPrec(const int prec)
{
    m_data.prec = prec;
}

void SettingsColumn::setIsShow(const bool isShow)
{
    m_data.isShow = isShow;
}
//-------------------------------

void PrintSettings::setTextFont(const QFont &textFont)
{
    m_data.textFont = textFont;
}

void PrintSettings::setCaptionTextFont(const QFont &captionTextFont)
{
    m_data.captionTextFont = captionTextFont;
}

void PrintSettings::setCaptionColor(const QColor &captionColor)
{
    m_data.captionColor = captionColor;
}

void PrintSettings::setTableWidth(const int tableWidth)
{
    m_data.tableWidth = tableWidth;
}

void PrintSettings::setTableBorderWidth(const int tableBorderWidth)
{
    m_data.tableBorderWidth = tableBorderWidth;
}

void PrintSettings::setTableBorderStyle(const int tableBorderStyle)
{
    m_data.tableBorderStyle = tableBorderStyle;
}

void PrintSettings::setCellSpacing(const int cellSpacing)
{
    m_data.cellSpacing = cellSpacing;
}

void PrintSettings::setCellPadding(const int cellPadding)
{
    m_data.cellPadding = cellPadding;
}

void PrintSettings::setTableBorderColor(const QColor &tableBorderColor)
{
    m_data.tableBorderColor = tableBorderColor;
}

void PrintSettings::setTableHeaderFont(const QFont &tableHeaderFont)
{
    m_data.tableHeaderFont = tableHeaderFont;
}

void PrintSettings::setTableHeaderColor(const QColor &tableHeaderColor)
{
    m_data.tableHeaderColor = tableHeaderColor;
}

void PrintSettings::setTableTextFont(const QFont &tableTextFont)
{
    m_data.tableTextFont = tableTextFont;
}

void PrintSettings::setTableTextColor(const QColor &tableTextColor)
{
    m_data.tableTextColor = tableTextColor;
}

void PrintSettings::setTableResultFont(const QFont &tableResultFont)
{
    m_data.tableResultFont = tableResultFont;
}

void PrintSettings::setTableResultColor(const QColor &tableResultColor)
{
    m_data.tableResultColor = tableResultColor;
}

void PrintSettings::setColumns(const QVector<SettingsColumnData> &columns)
{
    m_data.columns = columns;
}
//-------------------------------
void CalcSettings::setTextFont(const QFont &textFont)
{
    m_data.textFont = textFont;
}

void CalcSettings::setDelivResultFont(const QFont &delivResultFont)
{
    m_data.delivResultFont = delivResultFont;
}

void CalcSettings::setDelivResultColor(const QColor &delivResultColor)
{
    m_data.delivResultColor = delivResultColor;
}

void CalcSettings::setAllResultFont(const QFont &allResultFont)
{
    m_data.allResultFont = allResultFont;
}

void CalcSettings::setAllResultColor(const QColor &allResultColor)
{
    m_data.allResultColor = allResultColor;
}

void CalcSettings::setDateFormat(const QString &dateFormat)
{
    m_data.dateFormat = dateFormat;
}

void CalcSettings::setColumns(const QVector<SettingsColumnData> &columns)
{
    m_data.columns = columns;
}

void CalcSettings::setTextBackColor(const QColor &textBackColor)
{
    m_data.textBackColor = textBackColor;
}
//------------------------------------
Settings::Settings(QObject *parent):
    QObject(parent)
{
    m_settings = new QSettings(Constants::organization(), Constants::appName(), this);
    m_main = new MainSettings(this);
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
    setValue(MILK_INSPECTOR_2, main()->milkInspector_2());
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
    for (int i = 0; i < calc()->columns().size(); ++i) {
        m_settings->setArrayIndex(i);
        writeColumnToSettings(calc()->columns()[i]);
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
    for (int i = 0; i < print()->columns().size(); ++i) {
        m_settings->setArrayIndex(i);
        writeColumnToSettings(print()->columns()[i]);
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

    main()->setLastChoosenDb(value(LAST_CHOOSEN_DB, QString()).toString());
    main()->setPriceLiter(value(PRICE, .0f).toFloat());
    main()->setFirmName(value(FIRM_NAME, QString()).toString());
    main()->setMilkInspector(value(MILK_INSPECTOR, QString()).toString());
    main()->setMilkInspector_2(value(MILK_INSPECTOR_2, QString()).toString());
    main()->setIsFetchTablesOnRefresh(value(FETCH_MORE, false).toBool());

    m_settings->endGroup();
}

void Settings::readCalcSettings()
{
    m_settings->beginGroup(GROUP_CALC);

    calc()->setDateFormat(value(C_DATE_FORMAT, Constants::defaultDateFormat()).toString());
    calc()->setTextFont(value(C_TEXT_FONT, QFont().toString()).toString());
    calc()->setTextBackColor(value(C_TEXT_COLOR, QColor(Qt::white).name()).toString());
    calc()->setDelivResultFont(value(C_DELIV_RES_FONT, QFont().toString()).toString());
    calc()->setDelivResultColor(value(C_DELIV_RES_COLOR, QColor(Qt::lightGray).name()).toString());
    calc()->setAllResultFont(value(C_ALL_RES_FONT, QFont().toString()).toString());
    calc()->setAllResultColor(value(C_ALL_RES_COLOR, QColor(Qt::GlobalColor::darkGray).name()).toString());

    const auto size = m_settings->beginReadArray(COL_ARRAY);
    if (size == 0)
        setDefaultCalcColumns();
    else {
        calc()->clearColumns();

        for (int i = 0; i < size; ++i) {
            m_settings->setArrayIndex(i);
            calc()->addColumn({value(COL_DISPLAY).toString(),
                               value(COL_TYPE).toInt(),
                               value(COL_PREC).toInt(),
                               value(COL_IS_SHOW).toBool()});
        }
    }
    m_settings->endArray();

    m_settings->endGroup();
}

void Settings::readPrintSettings()
{
    m_settings->beginGroup(GROUP_PRINT);

    const auto blackColorName = QColor(Qt::black).name();

    print()->setTextFont(value(P_TEXT_FONT, TEXT_FONT_VALUE).toString());
    print()->setCaptionTextFont(value(P_CAPTION_FONT, CAPTION_FONT_VALUE).toString());
    print()->setCaptionColor(value(P_CAPTION_COLOR, blackColorName).toString());
    print()->setTableWidth(value(PT_WIDTH, 100).toInt());
    print()->setTableBorderWidth(value(PT_BORDER_WIDTH, 2).toInt());
    print()->setTableBorderStyle(value(PT_BORDER_STYLE, 3).toInt());
    print()->setCellSpacing(value(PT_CELL_SPACING, 0).toInt());
    print()->setCellPadding(value(PT_CELL_PADDING, 2).toInt());
    print()->setTableBorderColor(value(PT_BORDER_COLOR, blackColorName).toString());
    print()->setTableHeaderFont(value(PT_HEADER_FONT, HEAD_FONT_VALUE).toString());
    print()->setTableHeaderColor(value(PT_HEADER_COLOR, blackColorName).toString());
    print()->setTableTextFont(value(PT_TEXT_FONT, TAB_FONT_VALUE).toString());
    print()->setTableTextColor(value(PT_TEXT_COLOR, blackColorName).toString());
    print()->setTableResultFont(value(PT_RESULT_FONT, TAB_RES_FONT_VALUE).toString());
    print()->setTableResultColor(value(PT_RESULT_COLOR, blackColorName).toString());

    const auto size = m_settings->beginReadArray(COL_ARRAY);
    if (size == 0)
        setDefaultPrintColumns();
    else {
        print()->clearColumns();

        for (int i = 0; i < size; ++i) {
            m_settings->setArrayIndex(i);
            print()->addColumn({value(COL_DISPLAY).toString(),
                                value(COL_TYPE).toInt(),
                                value(COL_PREC).toInt(),
                                value(COL_IS_SHOW).toBool()});
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
    main()->reset();
}

void Settings::setDefaultPrintSettings()
{
    print()->setTextFont({TEXT_FONT_VALUE});
    print()->setCaptionTextFont({CAPTION_FONT_VALUE});
    print()->setCaptionColor({Qt::black});
    print()->setTableWidth(100);
    print()->setTableBorderWidth(2);
    print()->setTableBorderStyle(3);
    print()->setCellSpacing(0);
    print()->setCellPadding(2);
    print()->setTableBorderColor({Qt::black});
    print()->setTableHeaderFont({HEAD_FONT_VALUE});
    print()->setTableHeaderColor({Qt::black});
    print()->setTableTextFont({TEXT_FONT_VALUE});
    print()->setTableTextColor({Qt::black});
    print()->setTableResultFont({TAB_RES_FONT_VALUE});
    print()->setTableResultColor({Qt::black});

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
    calc()->setDateFormat({Constants::defaultDateFormat()});
    calc()->setTextFont(QFont());
    calc()->setDelivResultFont(QFont());
    calc()->setAllResultFont(QFont());
    calc()->setTextBackColor(QColor(Qt::GlobalColor::white));
    calc()->setDelivResultColor(QColor(Qt::GlobalColor::darkGray));
    calc()->setAllResultColor(QColor(Qt::GlobalColor::lightGray));

    setDefaultCalcColumns();
}

void Settings::setDefaultCalcColumns()
{
    calc()->clearColumns();
    calc()->addColumn({qtr("Ф. И. О."), toInt(COLTYPE::String)});
    calc()->addColumn({qtr("Молокопункты"), toInt(COLTYPE::String)});
    calc()->addColumn({qtr("Дата сдачи"), toInt(COLTYPE::Date)});
    calc()->addColumn({qtr("Цена за литр"), toInt(COLTYPE::Double)});
    calc()->addColumn({qtr("Литры"), toInt(COLTYPE::Double)});
    calc()->addColumn({qtr("Жиры"), toInt(COLTYPE::Double)});
    calc()->addColumn({qtr("Белок"), toInt(COLTYPE::Double)});
    calc()->addColumn({qtr("Жироед."), toInt(COLTYPE::Double)});
    calc()->addColumn({qtr("Зачет. вес"), toInt(COLTYPE::Double)});
    calc()->addColumn({qtr("Оплата(без премии)"), toInt(COLTYPE::Double)});
    calc()->addColumn({qtr("Премия"), toInt(COLTYPE::Double)});
    calc()->addColumn({qtr("Сумма"), toInt(COLTYPE::Double)});
}

void Settings::setDefaultPrintColumns()
{
    calc()->clearColumns();
    calc()->addColumn({qtr("№ п/п"), toInt(COLTYPE::SerialNumber)});
    calc()->addColumn({qtr("Ф. И. О."), toInt(COLTYPE::String)});
    calc()->addColumn({qtr("Физ. вес"), toInt(COLTYPE::Double)});
    calc()->addColumn({qtr("% жир"), toInt(COLTYPE::Double)});
    calc()->addColumn({qtr("Белок"), toInt(COLTYPE::Double)});
    calc()->addColumn({qtr("Жироед."), toInt(COLTYPE::Double), false});
    calc()->addColumn({qtr("Зачет. вес"), toInt(COLTYPE::Double)});
    calc()->addColumn({qtr("Оплата(без премии)"), toInt(COLTYPE::Double), false});
    calc()->addColumn({qtr("Премия"), toInt(COLTYPE::Double), false});
    calc()->addColumn({qtr("Сумма"), toInt(COLTYPE::Double)});
    calc()->addColumn({qtr("Подпись"), toInt(COLTYPE::String)});
}

void Settings::writeColumnToSettings(const SettingsColumnData &column)
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
