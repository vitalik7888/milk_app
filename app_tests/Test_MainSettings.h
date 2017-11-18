#ifndef TEST_MAINSETTINGS_H
#define TEST_MAINSETTINGS_H

#include <QObject>

class MainSettings;


class Test_MainSettings : public QObject
{
    Q_OBJECT
public:
    explicit Test_MainSettings(QObject *parent = nullptr);

    static void compare(MainSettings *ms, const QString &lastChoosenDb, const float priceLiter, const QString &firmName,
                 const QString &milkInspector, const QString &milkInspector_2,
                 const bool isFetchTablesOnRefresh);
    static void compareDefault(MainSettings *ms);

private slots:
    void testEmptyConstructor();
    void testConstructor();
    void testMethods();
    void testReset();
    void testSignalLastChoosenDbChanged();
    void testSignalPriceLiterChanged();
    void testSignalFirmNameChanged();
    void testSignalMilkInspectorChanged();
    void testSignalMilkInspector2Changed();
    void testSignalIsFetchTablesOnRefreshChanged();
};

#endif // TEST_MAINSETTINGS_H
