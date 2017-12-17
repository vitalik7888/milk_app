#include "DbExporterPlugin.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlError>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>


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
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Error opening file '" + m_filePath +"' for db export";
        return false;
    }

    if (m_type == "json")
        return toJson(file);
    if (m_type == "csv")
        return toCsv(file);

    return false;
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
    return {"csv", "json"/*, "html"*/};
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

bool DbExporterPlugin::toJson(QFile &file) const
{
    QJsonObject objRoot;

    for (const auto &table : m_tables) {
        QSqlQuery query("SELECT * FROM " + table);
        if (!query.exec()) {
            qWarning() << QString("Exporting table '%1' error: %2").arg(table).arg(query.lastError().text());
            return false;
        }

        QJsonArray array;

        while (query.next())
        {
            QJsonObject obj;

            const auto record = query.record();
            for (int i = 0; i < record.count(); ++i)
            {
                const auto field = record.field(i);
                obj[field.name()] = field.value().toString();
            }
            array.append(obj);
        }
        objRoot[table] = array;
    }

    QJsonDocument doc(objRoot);

    file.write(doc.toJson());

    return true;
}

bool DbExporterPlugin::toCsv(QFile &file) const
{
    QTextStream out(&file);

    for (const auto &table : m_tables) {
        QSqlQuery query("SELECT * FROM " + table);
        if (!query.exec()) {
            qWarning() << QString("Exporting table '%1' error: %2").arg(table).arg(query.lastError().text());
            return false;
        }

        while (query.next())
        {
            QString row;
            const auto record = query.record();
            for (int i = 0; i < record.count(); ++i)
            {
                const auto field = record.field(i);
                row.append(field.value().toString() + ",");
            }

            out << row.replace(row.length() - 1, 1, "\n");
        }
    }

    return true;
}
