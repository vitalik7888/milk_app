#include <QCoreApplication>
#include <QTest>
#include <locality.h>

#include "Test_MainSettings.h"
#include "Test_SettingsColumn.h"
#include "Test_CalcSettings.h"
#include "Test_PrintSettings.h"
#include "Test_Settings.h"
#include "types/Test_Deliverer.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setAttribute(Qt::AA_Use96Dpi, true);

    qRegisterMetaType<Locality *>();

    // settings
    Test_MainSettings mainSettingsTest;
    Test_SettingsColumn settingsColumnTest;
    Test_CalcSettings calcSettingsTest;
    Test_PrintSettings printSettingsTest;
    Test_Settings settingsTest;
    // types
    Test_Deliverer delivererTest;

    QList<QObject *> tests = {
        &mainSettingsTest,
        &settingsColumnTest,
        &calcSettingsTest,
        &printSettingsTest,
        &settingsTest,
        &delivererTest
    };

    int status = 0;
    for (auto test : tests)
        status |= QTest::qExec(test, argc, argv);

    return status;
}
