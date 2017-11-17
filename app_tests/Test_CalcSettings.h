#ifndef TEST_CALCSETTINGS_H
#define TEST_CALCSETTINGS_H

#include <functional>
#include <QObject>

class CalcSettings;
class QSignalSpy;


class Test_CalcSettings : public QObject
{
    Q_OBJECT
public:
    explicit Test_CalcSettings(QObject *parent = nullptr);

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

private:
    void compare(const CalcSettings &cs, const QFont &textFont, const QColor &textBackColor,
                 const QFont &delivResultFont, const QColor &delivResultColor,
                 const QFont &allResultFont, const QColor &allResultColor, const QString &dateFormat);
    void compareDefault(const CalcSettings &cs);
};

#endif // TEST_CALCSETTINGS_H
