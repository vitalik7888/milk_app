#include <QCoreApplication>
#include <QTest>

#include <milkpoint.h>
#include <deliverer.h>
#include <locality.h>
#include "settings/Test_MainSettings.h"
#include "settings/Test_SettingsColumn.h"
#include "settings/Test_CalcSettings.h"
#include "settings/Test_PrintSettings.h"
#include "settings/Test_Settings.h"
#include "types/Test_Deliverer.h"
#include "types/Test_Locality.h"
#include "types/Test_MilkPoint.h"
#include "types/Test_MilkReception.h"


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setAttribute(Qt::AA_Use96Dpi, true);

    qRegisterMetaType<Locality *>();
    qRegisterMetaType<Deliverer *>();
    qRegisterMetaType<MilkPoint *>();

    QList<QObject *> tests = {
        new Test_MainSettings(&app),
        new Test_SettingsColumn(&app),
        new Test_CalcSettings(&app),
        new Test_PrintSettings(&app),
        new Test_Settings(&app),
        new Test_Deliverer(&app),
        new Test_Locality(&app),
        new Test_MilkPoint(&app),
        new Test_MilkReception(&app)
    };

    int status = 0;
    for (auto test : tests)
        status |= QTest::qExec(test, argc, argv);

    return status;
}
