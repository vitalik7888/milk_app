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

    int status = 0;
    status |= QTest::qExec(&mainSettingsTest, argc, argv);
    status |= QTest::qExec(&settingsColumnTest, argc, argv);
    status |= QTest::qExec(&calcSettingsTest, argc, argv);
    status |= QTest::qExec(&printSettingsTest, argc, argv);
    status |= QTest::qExec(&settingsTest, argc, argv);

    return status;
}
