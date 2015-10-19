#include "Settings.h"

#include "Constants.h"

// qt
#include <QSettings>
#include <QDebug>


static const char *GROUP_MAIN = "main";
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



Settings::Settings():
    m_settings(new QSettings(Constants::organization(), Constants::appName())),
    m_priceLiter(.0f)
{
}

Settings::~Settings()
{
    delete m_settings;
}

void Settings::writeMainSettings()
{
    m_settings->beginGroup(GROUP_MAIN);

    m_settings->setValue(LAST_CHOOSEN_DB, m_lastChoosenDb);
    m_settings->setValue(PRICE, m_priceLiter);
    m_settings->setValue(FIRM_NAME, firmName);
    m_settings->setValue(MILK_INSPECTOR, milkInspector);
    m_settings->setValue(MILK_INSPECTOR_2, milkInspector_2);

    m_settings->endGroup();
}

void Settings::writeCalcSettings()
{
    m_settings->beginGroup(GROUP_CALC);

    m_settings->setValue(C_DATE_FORMAT, m_calc.dateFormat);
    m_settings->setValue(C_TEXT_FONT, m_calc.textFont.toString());
    m_settings->setValue(C_TEXT_COLOR, m_calc.textBackColor.name());
    m_settings->setValue(C_DELIV_RES_FONT, m_calc.delivResultFont.toString());
    m_settings->setValue(C_DELIV_RES_COLOR, m_calc.delivResultColor.name());
    m_settings->setValue(C_ALL_RES_FONT, m_calc.allResultFont.toString());
    m_settings->setValue(C_ALL_RES_COLOR, m_calc.allResultColor.name());

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

    m_settings->setValue(P_TEXT_FONT, m_print.textFont.toString());
    m_settings->setValue(P_CAPTION_FONT, m_print.captionTextFont.toString());
    m_settings->setValue(P_CAPTION_COLOR, m_print.captionColor.name());
    m_settings->setValue(PT_WIDTH, m_print.tableWidth);
    m_settings->setValue(PT_BORDER_WIDTH, m_print.tableBorderWidth);
    m_settings->setValue(PT_BORDER_STYLE, m_print.tableBorderStyle);
    m_settings->setValue(PT_CELL_SPACING, m_print.cellSpacing);
    m_settings->setValue(PT_CELL_PADDING, m_print.cellPadding);
    m_settings->setValue(PT_BORDER_COLOR, m_print.tableBorderColor.name());
    m_settings->setValue(PT_HEADER_FONT, m_print.tableHeaderFont.toString());
    m_settings->setValue(PT_HEADER_COLOR, m_print.tableHeaderColor.name());
    m_settings->setValue(PT_TEXT_FONT, m_print.tableTextFont.toString());
    m_settings->setValue(PT_TEXT_COLOR, m_print.tableTextColor.name());
    m_settings->setValue(PT_RESULT_FONT, m_print.tableResultFont.toString());
    m_settings->setValue(PT_RESULT_COLOR, m_print.tableResultColor.name());

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

    m_priceLiter = m_settings->value(PRICE, .0f).toFloat();
    m_lastChoosenDb = m_settings->value(LAST_CHOOSEN_DB, QString()).toString();
    firmName = m_settings->value(FIRM_NAME, QString()).toString();
    milkInspector = m_settings->value(MILK_INSPECTOR, QString()).toString();
    milkInspector_2 = m_settings->value(MILK_INSPECTOR_2, QString()).toString();

    m_settings->endGroup();
}

void Settings::readCalcSettings()
{
    m_settings->beginGroup(GROUP_CALC);

    m_calc.dateFormat = m_settings->value(C_DATE_FORMAT, Constants::defaultDateFormat()).toString();
    m_calc.textFont.fromString(m_settings->value(C_TEXT_FONT, QFont().toString()).toString());
    m_calc.textBackColor.setNamedColor(m_settings->value(C_TEXT_COLOR, QColor(Qt::white).name()).toString());
    m_calc.delivResultFont.fromString(m_settings->value(C_DELIV_RES_FONT, QFont().toString()).toString());
    m_calc.delivResultColor.setNamedColor(m_settings->value(C_DELIV_RES_COLOR, QColor(Qt::lightGray).name()).toString());
    m_calc.allResultFont.fromString(m_settings->value(C_ALL_RES_FONT, QFont().toString()).toString());
    m_calc.allResultColor.setNamedColor(m_settings->value(C_ALL_RES_COLOR, QColor(Qt::GlobalColor::darkGray).name()).toString());

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

    m_print.textFont.fromString(m_settings->value(P_TEXT_FONT, "Noto Sans,9,-1,5,50,0,0,0,0,0").toString());
    m_print.captionTextFont.fromString(m_settings->value(P_CAPTION_FONT, "Noto Sans,12,-1,5,75,0,0,0,0,0").toString());
    m_print.captionColor.setNamedColor(m_settings->value(P_CAPTION_COLOR, blackColorName).toString());
    m_print.tableWidth = m_settings->value(PT_WIDTH, 100).toInt();
    m_print.tableBorderWidth = m_settings->value(PT_BORDER_WIDTH, 2).toInt();
    m_print.tableBorderStyle = m_settings->value(PT_BORDER_STYLE, 3).toInt();
    m_print.cellSpacing = m_settings->value(PT_CELL_SPACING, 0).toInt();
    m_print.cellPadding = m_settings->value(PT_CELL_PADDING, 2).toInt();
    m_print.tableBorderColor.setNamedColor(m_settings->value(PT_BORDER_COLOR, blackColorName).toString());
    m_print.tableHeaderFont.fromString(m_settings->value(PT_HEADER_FONT, "Noto Sans,10,-1,5,75,0,0,0,0,0").toString());
    m_print.tableHeaderColor.setNamedColor(m_settings->value(PT_HEADER_COLOR, blackColorName).toString());
    m_print.tableTextFont.fromString(m_settings->value(PT_TEXT_FONT, "Noto Sans,10,-1,5,50,0,0,0,0,0").toString());
    m_print.tableTextColor.setNamedColor(m_settings->value(PT_TEXT_COLOR, blackColorName).toString());
    m_print.tableResultFont.fromString(m_settings->value(PT_RESULT_FONT, "Noto Sans,9,-1,5,75,1,0,0,0,0").toString());
    m_print.tableResultColor.setNamedColor(m_settings->value(PT_RESULT_COLOR, blackColorName).toString());

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
    m_lastChoosenDb = QString();
    m_priceLiter = .0f;
    firmName = QString();
    milkInspector = QString();
    milkInspector_2 = QString();
}

float Settings::priceLiter() const
{
    return m_priceLiter;
}

void Settings::setPriceLiter(const float priceLiter)
{
    m_priceLiter = priceLiter;
}

QString Settings::lastChoosenDb() const
{
    return m_lastChoosenDb;
}

void Settings::setLastChoosenDb(const QString &lastChoosenDb)
{
    m_lastChoosenDb = lastChoosenDb;
}

Settings::Print Settings::getPrint() const
{
    return m_print;
}

Settings::Print &Settings::setPrint()
{
    return m_print;
}

Settings::Calc Settings::getCalc() const
{
    return m_calc;
}

Settings::Calc &Settings::setCalc()
{
    return m_calc;
}

QString Settings::getFirmName() const
{
    return firmName;
}

void Settings::setFirmName(const QString &value)
{
    firmName = value;
}

QString Settings::getMilkInspector() const
{
    return milkInspector;
}

void Settings::setMilkInspector(const QString &value)
{
    milkInspector = value;
}

QString Settings::getMilkInspector_2() const
{
    return milkInspector_2;
}

void Settings::setMilkInspector_2(const QString &value)
{
    milkInspector_2 = value;
}

void Settings::setDefaultPrintSettings()
{
    const auto blackColor = QColor(Qt::black);
    auto textFont = QFont(), tabCaptionFont = QFont(), tabHeadFont = QFont(),
            tabResFont = QFont(), tabTextFont = QFont();

    textFont.fromString("Noto Sans,9,-1,5,50,0,0,0,0,0");
    tabCaptionFont.fromString("Noto Sans,12,-1,5,75,0,0,0,0,0");
    tabHeadFont.fromString("Noto Sans,10,-1,5,75,0,0,0,0,0");
    tabResFont.fromString("Noto Sans,9,-1,5,75,1,0,0,0,0");
    tabTextFont.fromString("Noto Sans,10,-1,5,50,0,0,0,0,0");

    m_print.textFont = textFont;
    m_print.captionTextFont = tabCaptionFont;
    m_print.captionColor = blackColor;
    m_print.tableWidth = 100;
    m_print.tableBorderWidth = 2;
    m_print.tableBorderStyle = 3;
    m_print.cellSpacing = 0;
    m_print.cellPadding = 2;
    m_print.tableBorderColor = blackColor;
    m_print.tableHeaderFont = tabHeadFont;
    m_print.tableHeaderColor = blackColor;
    m_print.tableTextFont = tabTextFont;
    m_print.tableTextColor = blackColor;
    m_print.tableResultFont = tabResFont;
    m_print.tableResultColor = blackColor;

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
    const auto font = QFont();

    m_calc.dateFormat = Constants::defaultDateFormat();
    m_calc.textFont = font;
    m_calc.textBackColor = QColor(Qt::GlobalColor::white);
    m_calc.delivResultFont = font;
    m_calc.delivResultColor = QColor(Qt::GlobalColor::lightGray);
    m_calc.allResultFont = font;
    m_calc.allResultColor = QColor(Qt::GlobalColor::darkGray);

    setDefaultCalcColumns();
}

void Settings::setDefaultCalcColumns()
{
    m_calc.columns.clear();

    m_calc.columns.append(Column(QObject::tr("Ф. И. О."), (int)Constants::ColumnType::String));
    m_calc.columns.append(Column(QObject::tr("Молокопункты"), (int)Constants::ColumnType::String));
    m_calc.columns.append(Column(QObject::tr("Дата сдачи"), (int)Constants::ColumnType::Date));
    m_calc.columns.append(Column(QObject::tr("Цена за литр"), (int)Constants::ColumnType::Double));
    m_calc.columns.append(Column(QObject::tr("Литры"), (int)Constants::ColumnType::Double));
    m_calc.columns.append(Column(QObject::tr("Жиры"), (int)Constants::ColumnType::Double));
    m_calc.columns.append(Column(QObject::tr("Белок"), (int)Constants::ColumnType::Double));
    m_calc.columns.append(Column(QObject::tr("Жироед."), (int)Constants::ColumnType::Double));
    m_calc.columns.append(Column(QObject::tr("Зачет. вес"), (int)Constants::ColumnType::Double));
    m_calc.columns.append(Column(QObject::tr("Оплата(без премии)"), (int)Constants::ColumnType::Double));
    m_calc.columns.append(Column(QObject::tr("Премия"), (int)Constants::ColumnType::Double));
    m_calc.columns.append(Column(QObject::tr("Сумма"), (int)Constants::ColumnType::Double));
}

void Settings::setDefaultPrintColumns()
{
    m_print.columns.clear();

    m_print.columns.append(Column(QObject::tr("№ п/п"), (int)Constants::ColumnType::SerialNumber));
    m_print.columns.append(Column(QObject::tr("Ф. И. О."), (int)Constants::ColumnType::String));
    m_print.columns.append(Column(QObject::tr("Физ. вес"), (int)Constants::ColumnType::Double));
    m_print.columns.append(Column(QObject::tr("% жир"), (int)Constants::ColumnType::Double));
    m_print.columns.append(Column(QObject::tr("Белок"), (int)Constants::ColumnType::Double));
    m_print.columns.append(Column(QObject::tr("Жироед."), (int)Constants::ColumnType::Double, false));
    m_print.columns.append(Column(QObject::tr("Зачет. вес"), (int)Constants::ColumnType::Double));
    m_print.columns.append(Column(QObject::tr("Оплата(без премии)"), (int)Constants::ColumnType::Double, false));
    m_print.columns.append(Column(QObject::tr("Премия"), (int)Constants::ColumnType::Double, false));
    m_print.columns.append(Column(QObject::tr("Сумма"), (int)Constants::ColumnType::Double));
    m_print.columns.append(Column(QObject::tr("Подпись"), (int)Constants::ColumnType::String));
}

Settings::Column Settings::getColumnFromSettings() const
{
    Column column;
    column.display = m_settings->value(COL_DISPLAY).toString();
    column.prec = m_settings->value(COL_PREC).toInt();
    column.isShow = m_settings->value(COL_IS_SHOW).toBool();
    column.type = m_settings->value(COL_TYPE).toInt();

    return column;
}

void Settings::writeColumnToSettings(const Settings::Column &column)
{
    m_settings->setValue(COL_DISPLAY, column.display);
    m_settings->setValue(COL_PREC, column.prec);
    m_settings->setValue(COL_IS_SHOW, column.isShow);
    m_settings->setValue(COL_TYPE, column.type);
}
