#include "src/core/MilkCore.h"
#include "src/database/tables/localities/LocalitiesSortFilterProxyModel.h"
#include "src/database/tables/milk_points/MilkPointsSortFilterProxyModel.h"
#include "src/database/tables/deliverers/DeliverersSortFilterProxyModel.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

void qmlRegisterSettings()
{
    const char *uri = "Milk.Settings";
    qmlRegisterType<Settings>(uri, 1, 0, "Settings");
    qmlRegisterType<MainSettings>(uri, 1, 0, "MainSettings");
    qmlRegisterType<CalcSettings>(uri, 1, 0, "CalcSettings");
    qmlRegisterType<PrintSettings>(uri, 1, 0, "PrintSettings");
}

void qmlRegisterDb()
{
    const char *uri = "Milk.Database";
    qmlRegisterType<DB_NAMESPACE::Database>(uri, 1, 0, "Database");
    qmlRegisterType<DB_NAMESPACE::Table>();
    qmlRegisterType<DB_NAMESPACE::LocalitiesTable>(uri, 1, 0, "LocalitiesTable");
    qmlRegisterType<DB_NAMESPACE::MilkPointsTable>(uri, 1, 0, "MilkPointsTable");
    qmlRegisterType<DB_NAMESPACE::DeliverersTable>(uri, 1, 0, "DeliverersTable");
    qmlRegisterType<DB_NAMESPACE::MilkReceptionTable>(uri, 1, 0, "MilkReceptionTable");
    qmlRegisterType<DB_NAMESPACE::LocalitiesSortFilterProxyModel>(uri, 1, 0, "LocalitiesSortFilterProxyModel");
    qmlRegisterType<DB_NAMESPACE::MilkPointsSortFilterProxyModel>(uri, 1, 0, "MilkPointsSortFilterProxyModel");
    qmlRegisterType<DB_NAMESPACE::DeliverersSortFilterProxyModel>(uri, 1, 0, "DeliverersSortFilterProxyModel");
}

void qmlRegisterMilkTypes()
{
    const char *uri = "Milk.Core";
    qmlRegisterType<Locality>(uri, 1, 0, "Locality");
    qmlRegisterType<MilkPoint>(uri, 1, 0, "MilkPoint");
    qmlRegisterType<Deliverer>(uri, 1, 0, "Deliverer");
    qmlRegisterType<MilkReception>(uri, 1, 0, "MilkReception");
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QCoreApplication::setApplicationName(Constants::appName());
    QCoreApplication::setOrganizationName(Constants::organization());
    QCoreApplication::setApplicationVersion(Constants::getCurrentVersion().toString());

    qmlRegisterSettings();
    qmlRegisterDb();
    qmlRegisterMilkTypes();

    MilkCore core;

    QQmlApplicationEngine engine;

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("db", core.database());
    context->setContextProperty("settings", core.settings());

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
