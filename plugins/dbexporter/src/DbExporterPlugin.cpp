#include "DbExporterPlugin.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonArray>


#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(dbexporterplugin, DbExporterPlugin)
#endif // QT_VERSION < 0x050000


void DbExporterPlugin::setDb(const QSqlDatabase &db)
{
    m_db = db;
}


bool DbExporterPlugin::dump() const
{
    QFile file(m_filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Error opening file '" + m_filePath +"' for db export";
        return false;
    }

    QJsonObject objRoot;

    for (const auto &table : m_tables) {
        QSqlQuery query("SELECT * FROM " + table);
        if (!query.exec()) {
            qWarning() << QString("Exporting table '%1' error: %2").arg(table).arg(query.lastError().text());
            return false;
        }

        QJsonArray array;

        QMapIterator<QString, QVariant> i(query.boundValues());
        while (i.hasNext()) {
            i.next();

            QJsonObject obj;
            obj[i.key().toUtf8().data()] = i.value().toString().toUtf8().data();
            array.append(obj);
        }
        objRoot[table] = array;
    }

    QJsonDocument doc(objRoot);
    file.write(doc.toJson());

    return true;
}

void DbExporterPlugin::setType(const QString &type)
{
    m_type = type;
}

QString DbExporterPlugin::type() const
{
    return m_type;
}

QStringList DbExporterPlugin::types() const
{
    return {"json"/*, "html", "doc"*/};
}

QString DbExporterPlugin::filePath() const
{
    return m_filePath;
}

void DbExporterPlugin::setFilePath(const QString &filePath)
{
    m_filePath = filePath;
}

QStringList DbExporterPlugin::tables() const
{
    return m_tables;
}

void DbExporterPlugin::setTables(const QStringList &tables)
{
    m_tables = tables;
}
