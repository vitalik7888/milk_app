#include <QCoreApplication>
#include <QTest>
#include <locality.h>

#include "settings/Test_MainSettings.h"
#include "settings/Test_SettingsColumn.h"
#include "settings/Test_CalcSettings.h"
#include "settings/Test_PrintSettings.h"
#include "settings/Test_Settings.h"
#include "types/Test_Deliverer.h"
#include "types/Test_Locality.h"
#include "types/Test_MilkPoint.h"

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
    Test_Locality localityTest;
    Test_MilkPoint milkPointTest;

    QList<QObject *> tests = {
        &mainSettingsTest,
        &settingsColumnTest,
        &calcSettingsTest,
        &printSettingsTest,
        &settingsTest,
        &delivererTest,
        &localityTest,
        &milkPointTest
    };

    int status = 0;
    for (auto test : tests)
        status |= QTest::qExec(test, argc, argv);

    return status;
}
