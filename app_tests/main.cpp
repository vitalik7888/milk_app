#include <QCoreApplication>
#include <QTest>

#include "Test_MainSettings.h"
#include "Test_SettingsColumn.h"
#include "Test_CalcSettings.h"
#include "Test_PrintSettings.h"
#include "Test_Settings.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setAttribute(Qt::AA_Use96Dpi, true);

    Test_MainSettings mainSettingsTest;
    Test_SettingsColumn settingsColumnTest;
    Test_CalcSettings calcSettingsTest;
    Test_PrintSettings printSettingsTest;
    Test_Settings settingsTest;

    QList<QObject *> tests = {
        &mainSettingsTest,
        &settingsColumnTest,
        &calcSettingsTest,
        &printSettingsTest,
        &settingsTest
    };

    int status = 0;
    for (auto test : tests)
        status |= QTest::qExec(test, argc, argv);

    return status;
}
