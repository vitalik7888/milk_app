#ifndef TEST_SETTINGSCOLUMN_H
#define TEST_SETTINGSCOLUMN_H

#include <QObject>

class SettingsColumn;


class Test_SettingsColumn : public QObject
{
    Q_OBJECT
public:
    explicit Test_SettingsColumn(QObject *parent = nullptr);

    static void compare(SettingsColumn *sc, const QString display, const int type,
                 const int prec, bool isShow);
    static void compareDefault(SettingsColumn *sc);

private slots:
    void testEmptyConstructor();
    void testConstructor();
    void testMethods();
    void testReset();
    void testSignalDisplayChanged();
    void testSignalTypeChanged();
    void testSignalPrecChanged();
    void testSignalIsShowChanged();
};

#endif // TEST_SETTINGSCOLUMN_H
