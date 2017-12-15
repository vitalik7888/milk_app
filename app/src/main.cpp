#include "src/core/MilkCore.h"
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
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtInfoMsg:
        logStream << "INFO: " << localMsg.constData();
        fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        logStream << "WARNING: " << localMsg.constData();
        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        logStream << "CRITICAL: " << localMsg.constData();
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        logStream << "FATAL: " << localMsg.constData();
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
