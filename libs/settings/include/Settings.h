#ifndef SETTINGS_H
#define SETTINGS_H

#include "MainSettings.h"
#include "PrintSettings.h"
#include "CalcSettings.h"
#include "SettingsColumn.h"
// Qt
#include <QSettings>


class SETTINGSLIBRARYSHARED_EXPORT Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(MainSettings *main READ main CONSTANT RESET resetMain)
    Q_PROPERTY(PrintSettings *print READ print CONSTANT RESET resetPrint)
    Q_PROPERTY(CalcSettings *calc READ calc CONSTANT RESET resetCalc)

public:
    Settings(QObject *parent = Q_NULLPTR);
    Settings(const QString &fileName, QObject *parent = Q_NULLPTR);
    virtual ~Settings();

    MainSettings *main() { return m_main; }
    PrintSettings *print() const { return m_print; }
    CalcSettings *calc() const { return m_calc; }

public slots:
    void writeLastChoosenDb();
    void writeMainSettings();
    void writeCalcSettings();
    void writePrintSettings();
    void writeSettings();

    void readMainSettings();
    void readCalcSettings();
    void readPrintSettings();
    void readSettings();

    void reset();
    void resetMain();
    void resetCalc();
    void resetPrint();

private:
    QSettings *m_settings;

    MainSettings *m_main;
    PrintSettings *m_print;
    CalcSettings *m_calc;

    void setDefaultPrintColumns();

    void writeColumnToSettings(SettingsColumn *column);

    QString getString(const QString &key, const QString &defaultValue) const;
    bool getBool(const QString &key, const bool defaultValue) const;
    int getInt(const QString &key, const int defaultValue) const;
    float getFloat(const QString &key, const float defaultValue) const;
    QFont getFont(const QString &key, const QFont &defaultFont) const;
    QColor getColor(const QString &key, const QColor &defaultColor) const;
};

#endif // SETTINGS_H
