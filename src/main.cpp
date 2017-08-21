#include "src/core/MilkCore.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<MilkCore>("MilkCore", 1, 0, "MilkCore");
    //qmlRegisterType<Settings>("Settings", 1, 0, "Settings");
    //qmlRegisterType<MainSettings>("MainSettings", 1, 0, "MainSettings");
    qmlRegisterType<DB_NAMESPACE::Database>("Database", 1, 0, "Database");

    MilkCore core;

    QQmlApplicationEngine engine;

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("core", &core);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
