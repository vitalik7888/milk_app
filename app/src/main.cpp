#include "src/core/MilkCore.h"
#include "DbConstants.h"
#include "src/database/tables/localities/LocalitiesSortFilterProxyModel.h"
#include "src/database/tables/milk_points/MilkPointsSortFilterProxyModel.h"
#include "src/database/tables/deliverers/DeliverersSortFilterProxyModel.h"
#include <tables/milk_reception/MilkReceptionSortFilterProxyModel.h>
// Qt
#include <QFile>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>


void qmlRegisterSettings()
{
    const char *uri = "com.milk.settings";
    qmlRegisterType<Settings>(uri, 1, 0, "Settings");
    qmlRegisterType<MainSettings>(uri, 1, 0, "MainSettings");
    qmlRegisterType<CalcSettings>(uri, 1, 0, "CalcSettings");
    qmlRegisterType<PrintSettings>(uri, 1, 0, "PrintSettings");
}

void qmlRegisterDb()
{
    const char *uri = "com.milk.db";
    qmlRegisterType<Database>(uri, 1, 0, "Database");
    qmlRegisterUncreatableType<DbConstants>(uri, 1, 0, "DBC", "Can not create instance of the DB constants");
    qmlRegisterType<Table>();
    qmlRegisterType<LocalitiesTable>(uri, 1, 0, "LocalitiesTable");
    qmlRegisterType<MilkPointsTable>(uri, 1, 0, "MilkPointsTable");
    qmlRegisterType<DeliverersTable>(uri, 1, 0, "DeliverersTable");
    qmlRegisterType<MilkReceptionTable>(uri, 1, 0, "MilkReceptionTable");
    qmlRegisterType<LocalitiesSortFilterProxyModel>(uri, 1, 0, "LocalitiesSortFilterProxyModel");
    qmlRegisterType<MilkPointsSortFilterProxyModel>(uri, 1, 0, "MilkPointsSortFilterProxyModel");
    qmlRegisterType<DeliverersSortFilterProxyModel>(uri, 1, 0, "DeliverersSortFilterProxyModel");
    qmlRegisterType<MilkReceptionSortFilterProxyModel>(uri, 1, 0, "MilkReceptionSortFilterProxyModel");
}

void qmlRegisterMilkTypes()
{
    const char *uri = "com.milk.types";
    qmlRegisterType<Locality>(uri, 1, 0, "Locality");
    qmlRegisterType<MilkPoint>(uri, 1, 0, "MilkPoint");
    qmlRegisterType<Deliverer>(uri, 1, 0, "Deliverer");
    qmlRegisterType<MilkReception>(uri, 1, 0, "MilkReception");
}

void qmlRegisterCalcTypes() {
    const char *uri = "com.milk.calc";
    qmlRegisterType<CalculatedItem>(uri, 1, 0, "CalculatedItem");
    qmlRegisterType<CalcItemModel>(uri, 1, 0, "CalcItemModel");
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName(Constants::appName());
    QCoreApplication::setOrganizationName(Constants::organization());
    QCoreApplication::setApplicationVersion(Constants::getCurrentVersion().toString());

//    QScopedPointer<MilkCore> milkCore(new MilkCore);
    QQmlApplicationEngine engine;
    qmlRegisterSettings();
    qmlRegisterDb();
    qmlRegisterMilkTypes();
    qmlRegisterCalcTypes();
    qmlRegisterType<MilkCore>("com.milk.core", 1, 0, "MilkCore");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
