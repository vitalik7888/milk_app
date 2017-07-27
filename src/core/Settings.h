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
        QString display = "";
        int type = -1;
        bool isShow = true;
        int prec = 2;
    };

    struct Print {
        QFont textFont;
        QFont captionTextFont;
        QColor captionColor = QColor(Qt::black);
        int tableWidth = 2;
        int tableBorderWidth = 2;
        int tableBorderStyle = 3;
        int cellSpacing = 0;
        int cellPadding = 0;
        QColor tableBorderColor = QColor(Qt::black);
        QFont tableHeaderFont;
        QColor tableHeaderColor = QColor(Qt::black);
        QFont tableTextFont;
        QColor tableTextColor = QColor(Qt::black);
        QFont tableResultFont;
        QColor tableResultColor = QColor(Qt::black);

        QVector<Column> columns = {};
    };

    struct Main {
        QString lastChoosenDb;
        float priceLiter = .0f;
        QString firmName;
        QString milkInspector;
        QString milkInspector_2;
        bool isFetchTablesOnRefresh = false;
    };

    struct Calc {
        QString dateFormat = "MM-dd-yyyy";
        QFont textFont;
        QColor textBackColor;
        QFont delivResultFont;
        QColor delivResultColor;
        QFont allResultFont;
        QColor allResultColor;

        QVector<Column> columns = {};
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

    Main getMain() const { return m_main; }
    Main &setMain() { return m_main; }
    Print getPrint() const { return m_print; }
    Print &setPrint() { return m_print; }
    Calc getCalc() const { return m_calc; }
    Calc &setCalc() { return m_calc; }

private:
    QScopedPointer<QSettings> m_settings;

    Main m_main;
    Print m_print;
    Calc m_calc;

    void setDefaultCalcColumns();
    void setDefaultPrintColumns();

    Settings::Column getColumnFromSettings() const;
    void writeColumnToSettings(const Settings::Column &column);
};

#endif // SETTINGS_H
