#ifndef TEST_SETTINGSCOLUMN_H
#define TEST_SETTINGSCOLUMN_H

#include <QObject>

class SettingsColumn;


class Test_SettingsColumn : public QObject
{
    Q_OBJECT
public:
    explicit Test_SettingsColumn(QObject *parent = nullptr);

private slots:
    void testEmptyConstructor();
    void testConstructor();
    void testMethods();
    void testReset();
    void testSignalDisplayChanged();
    void testSignalTypeChanged();
    void testSignalPrecChanged();
    void testSignalIsShowChanged();

private:
    void compare(const SettingsColumn &sc, const QString display, const int type,
                 const int prec, bool isShow);
    void compareDefault(const SettingsColumn &sc);
};

#endif // TEST_SETTINGSCOLUMN_H
