#ifndef SETTINGS_H
#define SETTINGS_H

#include "MainSettings.h"
#include "PrintSettings.h"
#include "CalcSettings.h"
#include "SettingsColumn.h"
// Qt
#include <QSettings>


class Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(MainSettings *main READ main RESET resetMain)
    Q_PROPERTY(PrintSettings *print READ print RESET resetPrint)
    Q_PROPERTY(CalcSettings *calc READ calc RESET resetCalc)

public:
    Settings(QObject *parent = Q_NULLPTR);
    virtual ~Settings();

    MainSettings *main() { return m_main; }
    PrintSettings *print() const { return m_print; }
    CalcSettings *calc() const { return m_calc; }

public slots:
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

    void setValue(const QString &key, const QVariant &value);
    QVariant value(const QString &key, const QVariant &defaultValue = {}) const;
};

#endif // SETTINGS_H
