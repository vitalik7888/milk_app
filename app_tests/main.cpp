#include <QCoreApplication>
#include <QTest>

#include "Test_MainSettings.h"
#include "Test_SettingsColumn.h"
#include "Test_CalcSettings.h"


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setAttribute(Qt::AA_Use96Dpi, true);

    Test_MainSettings mainSettingsTest;
    Test_CalcSettings calcSettingsTest;
    Test_SettingsColumn settingsColumnTest;

    int status = 0;
    status |= QTest::qExec(&mainSettingsTest, argc, argv);
    status |= QTest::qExec(&settingsColumnTest, argc, argv);
    status |= QTest::qExec(&calcSettingsTest, argc, argv);

    return status;
}
