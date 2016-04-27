#ifndef SETTINGS_H
#define SETTINGS_H

//#include <QString>
#include <QColor>
#include <QFont>
#include <QVector>

class QSettings;

class Settings
{
public:
    struct Column {
        Column(): display(""), type(-1), isShow(true), prec(2) {}
        Column(const QString &_display, const int _type, const bool _isShow = true,
               const int _prec = 2):
            display(_display), type(_type), isShow(_isShow), prec(_prec) {}

        QString display;
        int type;
        bool isShow;
        int prec;
    };

    struct Print {
        Print(): textFont(QFont()), captionTextFont(QFont()), captionColor(QColor(Qt::black)),
            tableWidth(2), tableBorderWidth(2), tableBorderStyle(3), cellSpacing(0), cellPadding(0),
            tableBorderColor(QColor(Qt::black)), tableHeaderFont(QFont()), tableHeaderColor(QColor(Qt::black)),
        tableTextFont(QFont()), tableTextColor(QColor(Qt::black)),
        tableResultFont(QFont()), tableResultColor(QColor(Qt::black)) {}

        QFont textFont;
        QFont captionTextFont;
        QColor captionColor;
        int tableWidth;
        int tableBorderWidth;
        int tableBorderStyle;
        int cellSpacing;
        int cellPadding;
        QColor tableBorderColor;
        QFont tableHeaderFont;
        QColor tableHeaderColor;
        QFont tableTextFont;
        QColor tableTextColor;
        QFont tableResultFont;
        QColor tableResultColor;

        QVector<Column> columns;
    };

    struct Calc {
        Calc(): dateFormat("MM-dd-yyyy"),
            textFont(QFont()), textBackColor(QColor()),
            delivResultFont(QFont()), delivResultColor(QColor()),
            allResultFont(QFont()), allResultColor(QColor()) {}

        QString dateFormat;
        QFont textFont;
        QColor textBackColor;
        QFont delivResultFont;
        QColor delivResultColor;
        QFont allResultFont;
        QColor allResultColor;

        QVector<Column> columns;
    };

    Settings();
    ~Settings();

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

    float priceLiter() const;
    void setPriceLiter(const float priceLiter);

    QString lastChoosenDb() const;
    void setLastChoosenDb(const QString &lastChoosenDb);

    Print getPrint() const;
    Print &setPrint();

    Calc getCalc() const;
    Calc &setCalc();

    QString getFirmName() const;
    void setFirmName(const QString &value);

    QString getMilkInspector() const;
    void setMilkInspector(const QString &value);

    QString getMilkInspector_2() const;
    void setMilkInspector_2(const QString &value);

    bool getIsFetchTablesOnRefresh() const;
    void setIsFetchTablesOnRefresh(bool value);

private:
    QSettings *m_settings;

    QString m_lastChoosenDb;
    float m_priceLiter;
    QString firmName;
    QString milkInspector;
    QString milkInspector_2;
    bool isFetchTablesOnRefresh;

    Print m_print;
    Calc m_calc;

    void setDefaultCalcColumns();
    void setDefaultPrintColumns();

    Settings::Column getColumnFromSettings() const;
    void writeColumnToSettings(const Settings::Column &column);
};

#endif // SETTINGS_H
