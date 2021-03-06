#include "MilkCore.h"
// Qt
#include <QFile>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>


QTextStream logStream;

void milkMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s\n", localMsg.constData());
        break;
    case QtInfoMsg:
        logStream << "INFO: " << localMsg.constData();
        fprintf(stderr, "Info: %s\n", localMsg.constData());
        break;
    case QtWarningMsg:
        logStream << "WARNING: " << localMsg.constData() << "\n";
        fprintf(stderr, "Warning: %s\n", localMsg.constData());
        break;
    case QtCriticalMsg:
        logStream << "CRITICAL: " << localMsg.constData() << "\n";
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        logStream << "FATAL: " << localMsg.constData() << "\n";
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
}

int main(int argc, char *argv[])
{
    QFile data("milk.log");
    if (data.open(QFile::WriteOnly | QFile::Truncate)) {
        logStream.setDevice(&data);
        qInstallMessageHandler(milkMessageOutput);
    } else {
        qWarning() << "Cannot open file for logging";
    }

    QApplication app(argc, argv);
    QCoreApplication::setApplicationName(Constants::appName());
    QCoreApplication::setOrganizationName(Constants::organization());
    QCoreApplication::setApplicationVersion(Constants::getCurrentVersion().toString());

    qRegisterMetaType<MILK_ID>("MILK_ID");
    qmlRegisterInterface<MilkBaseItem>("MilkBaseItem");
    qmlRegisterType<MilkCore>("com.milk.core", 1, 0, "MilkCore");
    qmlRegisterType<MilkPlugins>("com.milk.plugins", 1, 0, "MilkPlugins");
    qmlRegisterType<DbExporter>("com.milk.plugins", 1, 0, "DbExporter");
    qmlRegisterType<CalcExporter>("com.milk.plugins", 1, 0, "CalcExporter");

    MilkCore core;

    QQmlApplicationEngine engine;
#ifdef Q_OS_OSX
    engine->addImportPath(app.applicationDirPath() + "/../PlugIns");
#endif
    engine.rootContext()->setContextProperty("milkCore", &core);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
