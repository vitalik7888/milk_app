#include "src/core/MilkCore.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<MilkCore>("MilkCore", 1, 0, "MilkCore");
    qmlRegisterType<Settings>("Settings", 1, 0, "Settings");
    qmlRegisterType<MainSettings>("MainSettings", 1, 0, "MainSettings");

    MilkCore core;

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("core", &core);

    return app.exec();
}
