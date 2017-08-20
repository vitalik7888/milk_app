#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QColor>
#include <QFont>
#include <QVector>

class QSettings;

//----------------------------
class MainSettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString lastChoosenDb READ lastChoosenDb WRITE setLastChoosenDb)
    Q_PROPERTY(float priceLiter READ priceLiter WRITE setPriceLiter)
    Q_PROPERTY(QString firmName READ firmName WRITE setFirmName)
    Q_PROPERTY(QString milkInspector READ milkInspector WRITE setMilkInspector)
    Q_PROPERTY(QString milkInspector_2 READ milkInspector_2 WRITE setMilkInspector_2)
    Q_PROPERTY(bool isFetchTablesOnRefresh READ isFetchTablesOnRefresh WRITE setIsFetchTablesOnRefresh)

public:
    struct Data {
        QString lastChoosenDb;
        float priceLiter = .0f;
        QString firmName;
        QString milkInspector;
        QString milkInspector_2;
        bool isFetchTablesOnRefresh = false;
    };

    explicit MainSettings(const QString &lastChoosenDb, const float priceLiter, const QString &firmName,
                          const QString &milkInspector, const QString &milkInspector_2,
                          const bool isFetchTablesOnRefresh = false, QObject *parent = Q_NULLPTR);
    explicit MainSettings(QObject *parent = Q_NULLPTR);
    virtual ~MainSettings();

    QString lastChoosenDb() const { return m_data.lastChoosenDb; }
    float priceLiter() const { return m_data.priceLiter; }
    QString firmName() const { return m_data.firmName; }
    QString milkInspector() const { return m_data.milkInspector; }
    QString milkInspector_2() const { return m_data.milkInspector_2; }
    bool isFetchTablesOnRefresh() const { return m_data.isFetchTablesOnRefresh; }

public slots:
    void setLastChoosenDb(const QString &lastChoosenDb);
    void setPriceLiter(float priceLiter);
    void setFirmName(const QString &firmName);
    void setMilkInspector(const QString &milkInspector);
    void setMilkInspector_2(const QString &milkInspector_2);
    void setIsFetchTablesOnRefresh(const bool isFetchTablesOnRefresh);
    void reset();

private:
    Data m_data;
};

//------------------------------------
struct SettingsColumnData {
    QString display = "";
    int type = -1;
    int prec = 2;
    bool isShow = true;
};

//------------------------------------
class SettingsColumn : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString display READ display WRITE setDisplay)
    Q_PROPERTY(int type READ type WRITE setType)
    Q_PROPERTY(int prec READ prec WRITE setPrec)
    Q_PROPERTY(bool isShow READ isShow WRITE setIsShow)

public:
    explicit SettingsColumn(const QString display = "",const int type = -1,
                            const int prec = 2, bool isShow = true, QObject *parent = Q_NULLPTR):
        QObject(parent), m_data({display, type, prec, isShow}) {}
    virtual ~SettingsColumn() {}

    QString display() const { return m_data.display; }
    int type() const { return m_data.type; }
    int prec() const { return m_data.prec; }
    bool isShow() const { return m_data.isShow; }

public slots:
    void setDisplay(const QString &display);
    void setType(const int type);
    void setPrec(const int prec);
    void setIsShow(const bool isShow);

private:
    SettingsColumnData m_data;
};

//------------------------------------
class PrintSettings : public QObject {
    Q_OBJECT
    Q_PROPERTY(QFont textFont READ textFont WRITE setTextFont)
    Q_PROPERTY(QFont captionTextFont READ captionTextFont WRITE setCaptionTextFont)
    Q_PROPERTY(QColor captionColor READ captionColor WRITE setCaptionColor)
    Q_PROPERTY(int tableWidth READ tableWidth WRITE setTableWidth)
    Q_PROPERTY(int tableBorderWidth READ tableBorderWidth WRITE setTableBorderWidth)
    Q_PROPERTY(int tableBorderStyle READ tableBorderStyle WRITE setTableBorderStyle)
    Q_PROPERTY(int cellSpacing READ cellSpacing WRITE setCellSpacing)
    Q_PROPERTY(int cellPadding READ cellPadding WRITE setCellPadding)
    Q_PROPERTY(QColor tableBorderColor READ tableBorderColor WRITE setTableBorderColor)
    Q_PROPERTY(QFont tableHeaderFont READ tableHeaderFont WRITE setTableHeaderFont)
    Q_PROPERTY(QColor tableHeaderColor READ tableHeaderColor WRITE setTableHeaderColor)
    Q_PROPERTY(QFont tableTextFont READ tableTextFont WRITE setTableTextFont)
    Q_PROPERTY(QColor tableTextColor READ tableTextColor WRITE setTableTextColor)
    Q_PROPERTY(QFont tableResultFont READ tableResultFont WRITE setTableResultFont)
    Q_PROPERTY(QColor tableResultColor READ tableResultColor WRITE setTableResultColor)
    Q_PROPERTY(QVector<SettingsColumnData> columns READ columns WRITE setColumns)

public:
    struct Data {
        QFont textFont;
        QFont captionTextFont;
        QColor captionColor = {Qt::black};
        int tableWidth = 2;
        int tableBorderWidth = 2;
        int tableBorderStyle = 3;
        int cellSpacing = 0;
        int cellPadding = 0;
        QColor tableBorderColor = {Qt::black};
        QFont tableHeaderFont;
        QColor tableHeaderColor = {Qt::black};
        QFont tableTextFont;
        QColor tableTextColor = {Qt::black};
        QFont tableResultFont;
        QColor tableResultColor = {Qt::black};

        QVector<SettingsColumnData> columns = {};
    };

    explicit PrintSettings(
            const QFont &textFont, const QFont &captionTextFont,
            const QColor &captionColor = QColor(Qt::black), const int tableWidth = 2,
            const int tableBorderWidth = 2, const int tableBorderStyle = 3,
            const int cellSpacing = 0, const int cellPadding = 0,
            const QColor &tableBorderColor = QColor(Qt::black), const QFont &tableHeaderFont = QFont(),
            const QColor &tableHeaderColor = QColor(Qt::black), const QFont &tableTextFont = QFont(),
            const QColor &tableTextColor = QColor(Qt::black), const QFont &tableResultFont = QFont(),
            const QColor &tableResultColor = QColor(Qt::black), const QVector<SettingsColumnData> &columns = {},
            QObject *parent = Q_NULLPTR) :
        QObject(parent),
        m_data({textFont, captionTextFont, captionColor, tableWidth, tableBorderWidth,
               tableBorderStyle, cellSpacing, cellPadding, tableBorderColor, tableHeaderFont,
               tableHeaderColor, tableTextFont, tableTextColor, tableResultFont, tableResultColor, columns})
    {}

    virtual ~PrintSettings() {}

    QFont textFont() const { return m_data.textFont; }
    QFont captionTextFont() const { return m_data.captionTextFont; }
    QColor captionColor() const { return m_data.captionColor; }
    int tableWidth() const { return m_data.tableWidth; }
    int tableBorderWidth() const { return m_data.tableBorderWidth; }
    int tableBorderStyle() const { return m_data.tableBorderStyle; }
    int cellSpacing() const { return m_data.cellSpacing; }
    int cellPadding() const { return m_data.cellPadding; }
    QColor tableBorderColor() const { return m_data.tableBorderColor; }
    QFont tableHeaderFont() const { return m_data.tableHeaderFont; }
    QColor tableHeaderColor() const { return m_data.tableHeaderColor; }
    QFont tableTextFont() const { return m_data.tableTextFont; }
    QColor tableTextColor() const { return m_data.tableTextColor; }
    QFont tableResultFont() const { return m_data.tableResultFont; }
    QColor tableResultColor() const { return m_data.tableResultColor; }
    QVector<SettingsColumnData> columns() const { return m_data.columns; }

    Q_INVOKABLE void addColumn(const SettingsColumnData &column) {
        m_data.columns.append(column);
    }

    Q_INVOKABLE void clearColumns() {
        m_data.columns.clear();
    }

    Q_INVOKABLE void reset()
    {

    }

public slots:
    void setTextFont(const QFont &textFont);
    void setCaptionTextFont(const QFont &captionTextFont);
    void setCaptionColor(const QColor &captionColor);
    void setTableWidth(const int tableWidth);
    void setTableBorderWidth(const int tableBorderWidth);
    void setTableBorderStyle(const int tableBorderStyle);
    void setCellSpacing(const int cellSpacing);
    void setCellPadding(const int cellPadding);
    void setTableBorderColor(const QColor &tableBorderColor);
    void setTableHeaderFont(const QFont &tableHeaderFont);
    void setTableHeaderColor(const QColor &tableHeaderColor);
    void setTableTextFont(const QFont &tableTextFont);
    void setTableTextColor(const QColor &tableTextColor);
    void setTableResultFont(const QFont &tableResultFont);
    void setTableResultColor(const QColor &tableResultColor);
    void setColumns(const QVector<SettingsColumnData> &columns);

private:
    Data m_data;
};

//------------------------------------
class CalcSettings : public QObject {
    Q_OBJECT
    Q_PROPERTY(QFont textFont READ textFont WRITE setTextFont)
    Q_PROPERTY(QColor textBackColor READ textBackColor WRITE setTextBackColor)
    Q_PROPERTY(QFont delivResultFont READ delivResultFont WRITE setDelivResultFont)
    Q_PROPERTY(QColor delivResultColor READ delivResultColor WRITE setDelivResultColor)
    Q_PROPERTY(QFont allResultFont READ allResultFont WRITE setAllResultFont)
    Q_PROPERTY(QColor allResultColor READ allResultColor WRITE setAllResultColor)
    Q_PROPERTY(QString dateFormat READ dateFormat WRITE setDateFormat)
    Q_PROPERTY(QVector<SettingsColumnData> columns READ columns WRITE setColumns)

public:
    struct Data {
        QString dateFormat = "MM-dd-yyyy";
        QFont textFont;
        QColor textBackColor;
        QFont delivResultFont;
        QColor delivResultColor;
        QFont allResultFont;
        QColor allResultColor;

        QVector<SettingsColumnData> columns = {};
    };

    explicit CalcSettings(
            const QFont &textFont, const QColor &textBackColor,
            const QFont &delivResultFont, const QColor &delivResultColor,
            const QFont &allResultFont, const QColor &allResultColor,
            const QString &dateFormat = "MM-dd-yyyy",
            const QVector<SettingsColumnData> &columns = {},
            QObject *parent = Q_NULLPTR) :
        QObject(parent),
        m_data({dateFormat, textFont, textBackColor, delivResultFont, delivResultColor, allResultFont,
               allResultColor, columns}) {}
    virtual ~CalcSettings() {}

    QFont textFont() const { return m_data.textFont; }
    QColor textBackColor() const { return m_data.textBackColor; }
    QFont delivResultFont() const { return m_data.delivResultFont; }
    QColor delivResultColor() const { return m_data.delivResultColor; }
    QFont allResultFont() const { return m_data.allResultFont; }
    QColor allResultColor() const { return m_data.allResultColor; }
    QString dateFormat() const { return m_data.dateFormat; }
    QVector<SettingsColumnData> columns() const { return m_data.columns; }

    Q_INVOKABLE void addColumn(const SettingsColumnData &column) {
        m_data.columns.append(column);
    }

    Q_INVOKABLE void clearColumns() {
        m_data.columns.clear();
    }

public slots:
    void setTextFont(const QFont &textFont);
    void setDelivResultFont(const QFont &delivResultFont);
    void setDelivResultColor(const QColor &delivResultColor);
    void setAllResultFont(const QFont &allResultFont);
    void setAllResultColor(const QColor &allResultColor);
    void setDateFormat(const QString &dateFormat);
    void setColumns(const QVector<SettingsColumnData> &columns);
    void setTextBackColor(const QColor &textBackColor);

private:
    Data m_data;
};
//----------------------------
class Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(MainSettings *main READ main)
    Q_PROPERTY(PrintSettings *print READ print)
    Q_PROPERTY(CalcSettings *calc READ calc)

public:
    Settings(QObject *parent = Q_NULLPTR);
    virtual ~Settings();

    void writeMainSettings();
    void writeCalcSettings();
    void writePrintSettings();
    void writeSettings();

    void readMainSettings();
    void readCalcSettings();
    void readPrintSettings();
    void readSettings();

    void setDefaultMainSettings();
    void setDefaultCalcSettings();
    void setDefaultPrintSettings();
    void setDefaultSettings();

    MainSettings *main() { return m_main; }
    PrintSettings *print() const { return m_print; }
    CalcSettings *calc() const { return m_calc; }

private:
    QSettings *m_settings;

    MainSettings *m_main;
    PrintSettings *m_print;
    CalcSettings *m_calc;

    void setDefaultCalcColumns();
    void setDefaultPrintColumns();

    void writeColumnToSettings(const SettingsColumnData &column);

    void setValue(const QString &key, const QVariant &value);
    QVariant value(const QString &key, const QVariant &defaultValue = {}) const;
};

#endif // SETTINGS_H
