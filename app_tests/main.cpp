#include <QCoreApplication>
#include <QTest>

#include "Test_MainSettings.h"


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setAttribute(Qt::AA_Use96Dpi, true);

    int status = 0;
    Test_MainSettings mainSettingsTest;

    status |= QTest::qExec(&mainSettingsTest, argc, argv);

    return status;
}
