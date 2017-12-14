#include "src/core/MilkCore.h"
#include "DbConstants.h"
// Qt
#include <QFile>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>


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

    QQmlApplicationEngine engine;
#ifdef Q_OS_OSX
    engine->addImportPath(app.applicationDirPath() + "/../PlugIns");
#endif
    qmlRegisterCalcTypes();
    qmlRegisterType<MilkCore>("com.milk.core", 1, 0, "MilkCore");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
