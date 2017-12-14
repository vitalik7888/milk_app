#include "src/core/MilkCore.h"
// Qt
#include <QFile>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName(Constants::appName());
    QCoreApplication::setOrganizationName(Constants::organization());
    QCoreApplication::setApplicationVersion(Constants::getCurrentVersion().toString());

    QQmlApplicationEngine engine;
#ifdef Q_OS_OSX
    engine->addImportPath(app.applicationDirPath() + "/../PlugIns");
#endif
    qmlRegisterType<MilkCore>("com.milk.core", 1, 0, "MilkCore");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
