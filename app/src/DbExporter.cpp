#include "DbExporter.h"

// Qt
#include <QDebug>


DbExporter::DbExporter(QObject *parent) :
    QObject(parent),
    m_dbExporter(Q_NULLPTR)
{

}

void DbExporter::setDbExporter(IDbExporter *dbExporter)
{
    m_dbExporter = dbExporter;
}

bool DbExporter::isNull() const
{
    return m_dbExporter == Q_NULLPTR;
}

void DbExporter::setDb(const QSqlDatabase &db)
{
    if (isNull()) {
        qWarning() << "Plugin db export is null";
        return;
    }

    m_dbExporter->setDb(db);
}


bool DbExporter::dump() const
{
    if (isNull()) {
        qWarning() << "Plugin db export is null";
        return false;
    }

    return m_dbExporter->dump();
}


void DbExporter::setType(const QString &type)
{
    if (isNull()) {
        qWarning() << "Plugin db export is null";
        return;
    }

    if (this->type() == type)
        return;

    m_dbExporter->setType(type);
    emit typeChanged(type);
}

QString DbExporter::type() const
{
    if (isNull()) {
        qWarning() << "Plugin db export is null";
        return {};
    }
    return m_dbExporter->type();
}

QStringList DbExporter::types() const
{
    if (isNull()) {
        qWarning() << "Plugin db export is null";
        return {};
    }

    return m_dbExporter->types();
}

QString DbExporter::filePath() const
{
    if (isNull()) {
        qWarning() << "Plugin db export is null";
        return {};
    }

    return m_dbExporter->filePath();
}

QStringList DbExporter::tables() const
{
    if (isNull()) {
        qWarning() << "Plugin db export is null";
        return {};
    }

    return m_dbExporter->tables();
}

void DbExporter::setFilePath(const QString &filePath)
{
    if (isNull()) {
        qWarning() << "Plugin db export is null";
        return;
    }

    if (this->filePath() == filePath)
        return;

    m_dbExporter->setFilePath(filePath);
    emit filePathChanged(filePath);
}

void DbExporter::setTables(const QStringList &tables)
{
    if (isNull()) {
        qWarning() << "Plugin db export is null";
        return;
    }

    if (this->tables() == tables)
        return;

    m_dbExporter->setTables(tables);
    emit tablesChanges(this->tables());
}
