#include <QCoreApplication>
#include <QTest>

// settings
#include "settings/Test_MainSettings.h"
#include "settings/Test_SettingsColumn.h"
#include "settings/Test_CalcSettings.h"
#include "settings/Test_PrintSettings.h"
#include "settings/Test_Settings.h"
// types
#include <Deliverer.h>
#include <Locality.h>
#include <MilkPoint.h>
#include "types/Test_DelivererData.h"
#include "types/Test_Deliverer.h"
#include "types/Test_LocalityData.h"
#include "types/Test_Locality.h"
#include "types/Test_MilkPointData.h"
#include "types/Test_MilkPoint.h"
#include "types/Test_MilkReceptionData.h"
#include "types/Test_MilkReception.h"
// calc
#include "calc/Test_CalcUtils.h"
#include "calc/Test_CalculatedItemData.h"
// db
#include "db/Test_LocalitiesDao.h"
#include "db/Test_LocalitiesTable.h"


using Tests = QList<QObject *>;

void addSettingsTests(Tests &tests, QObject *parent) {
    tests.append({
                     new Test_MainSettings(parent),
                     new Test_SettingsColumn(parent),
                     new Test_CalcSettings(parent),
                     new Test_PrintSettings(parent),
                     new Test_Settings(parent)
                 });
}

void addTypesTests(Tests &tests, QObject *parent) {
    tests.append({
                     new Test_DelivererData(parent),
                     new Test_Deliverer(parent),
                     new Test_LocalityData(parent),
                     new Test_Locality(parent),
                     new Test_MilkPointData(parent),
                     new Test_MilkPoint(parent),
                     new Test_MilkReceptionData(parent),
                     new Test_MilkReception(parent)
                 });
}

void addCalcTests(Tests &tests, QObject *parent) {
    tests.append({
                     new Test_CalcUtils(parent),
                     new Test_CalculatedItemData(parent)
                 });
}

void addDbTests(Tests &tests, QObject *parent) {
    tests.append({
                     new Test_LocalitiesDao(parent),
                     new Test_LocalitiesModel(parent)
                 });
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setAttribute(Qt::AA_Use96Dpi, true);

    qMetaTypeId<Locality>();
    qMetaTypeId<Deliverer>();
    qMetaTypeId<MilkPoint>();

    QList<QObject *> tests;
//    addSettingsTests(tests, &app);
//    addTypesTests(tests, &app);
//    addCalcTests(tests, &app);
    addDbTests(tests, &app);

    int status = 0;
    for (auto test : tests)
        status |= QTest::qExec(test, argc, argv);

    return status;
}
