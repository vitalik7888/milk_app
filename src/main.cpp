#include "src/core/MilkCore.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Settings>("Milk.Settings", 1, 0, "Settings");
    qmlRegisterType<MainSettings>("Milk.Settings", 1, 0, "MainSettings");
    qmlRegisterType<DB_NAMESPACE::Database>("Milk.Database", 1, 0, "Database");
    qmlRegisterType<DB_NAMESPACE::LocalitiesTable>("Milk.Database", 1, 0, "LocalitiesTable");
    qmlRegisterType<DB_NAMESPACE::MilkPointsTable>("Milk.Database", 1, 0, "MilkPointsTable");
    qmlRegisterType<DB_NAMESPACE::DeliverersTable>("Milk.Database", 1, 0, "DeliverersTable");
    qmlRegisterType<DB_NAMESPACE::MilkReceptionTable>("Milk.Database", 1, 0, "MilkReceptionTable");
    qmlRegisterType<Locality>("Milk.Core", 1, 0, "Locality");
    qmlRegisterType<MilkPoint>("Milk.Core", 1, 0, "MilkPoint");
    qmlRegisterType<Deliverer>("Milk.Core", 1, 0, "Deliverer");
    qmlRegisterType<MilkReception>("Milk.Core", 1, 0, "MilkReception");

    MilkCore core;

    QQmlApplicationEngine engine;

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("database", core.database());
    context->setContextProperty("settings", core.settings());

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
