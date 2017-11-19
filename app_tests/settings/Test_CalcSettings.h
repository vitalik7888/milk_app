#ifndef TEST_CALCSETTINGS_H
#define TEST_CALCSETTINGS_H

#include "SettingsConstants.h"
// Qt
#include <QObject>

class CalcSettings;


class Test_CalcSettings : public QObject
{
    Q_OBJECT
public:
    explicit Test_CalcSettings(QObject *parent = nullptr);

    static void compare(CalcSettings *cs, const QFont &textFont, const QColor &textBackColor,
                            const QFont &delivResultFont, const QColor &delivResultColor,
                            const QFont &allResultFont, const QColor &allResultColor,
                        const QString &dateFormat, const SettingsConstants::SettingsColumns &columns);
    static void compareDefault(CalcSettings *cs);

private slots:
    void testEmptyConstructor();
    void testMethods();
    void testReset();
    void testSignalTextFontChanged();
    void testSignalTextBackColorChanged();
    void testSignalDelivResultFontChanged();
    void testSignalDelivResultColorChanged();
    void testSignalAllResultFontChanged();
    void testSignalAllResultColorChanged();
    void testSignalDateFormatChanged();
};

#endif // TEST_CALCSETTINGS_H
