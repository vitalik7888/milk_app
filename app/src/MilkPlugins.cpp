#include "MilkPlugins.h"

// Qt
#include <QApplication>
#include <QDir>
#include <QPluginLoader>
#include <QDebug>


MilkPlugins::MilkPlugins(QObject *parent) :
    QObject(parent)
{
    m_dbExporter = new DbExporter(this);
}

void MilkPlugins::load()
{
    QDir pluginsDir(qApp->applicationDirPath());
#if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
        pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
    if (pluginsDir.dirName() == "MacOS") {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
#endif
    pluginsDir.cd("plugins");
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            auto dbExporter = qobject_cast<IDbExporter *>(plugin);
            if (dbExporter) {
                m_dbExporter->setDbExporter(dbExporter);
                qInfo() << "Loaded sqlite3 db utils plugin";
            }
        }
    }
}

DbExporter *MilkPlugins::dbExporter() const
{
    return m_dbExporter;
}
