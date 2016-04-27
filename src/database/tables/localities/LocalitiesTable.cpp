#include "LocalitiesTable.h"

#include "Utils.h"
// qt
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

static const char *FN_ID = "id";
static const char *FN_NAME = "name";
static const char *FN_DESCRIPTION = "description";


LocalitiesTable::LocalitiesTable(QObject *parent, QSqlDatabase db):
    Table(parent, db)
{
    setObjectName("LocalitiesTable");
    qDebug() << "init " + objectName();

    initColumns();
    setQuery(selectAll());
}

QString LocalitiesTable::tableName() const
{
    return "localities";
}

QSqlField LocalitiesTable::getFieldId() const
{
    return getColumnByName(FN_ID);
}

QSqlField LocalitiesTable::getFieldName() const
{
    return getColumnByName(FN_NAME);
}

QSqlField LocalitiesTable::getFieldDescription() const
{
    return getColumnByName(FN_DESCRIPTION);
}

Locality LocalitiesTable::getLocality(const qlonglong localityId) const
{
    QSqlQuery query;
    query.prepare(QString("%1 WHERE %2 = ?")
                    .arg(Utils::Main::getSelectStr(tableName(), QStringList()
                                      << getNameColumnName(true)
                                      << getNameColumnDescription(true)))
                    .arg(getNameColumnId()));
    query.addBindValue(localityId);

    if (query.exec() && query.first())
    {
        return Locality(query.value(0).toString(),
                         query.value(1).toString(),
                         localityId);
    } else
        emit error(tr("Отсутствует населенный пункт с id = ")+ QString::number(localityId));

    return Locality::CREATE_NULL();
}

bool LocalitiesTable::insert(const Locality &locality)
{
    QSqlQuery query;
    query.prepare(Utils::Main::getPrepInsertStr(tableName(), QStringList()
                                   << getNameColumnName()
                                   << getNameColumnDescription()));
    query.addBindValue(locality.name());
    query.addBindValue(locality.description());

    if (!query.exec()) {
        emit error(query.lastError().text());
        return false;
    }

    return true;
}

bool LocalitiesTable::update(const Locality &locality) const
{
    QSqlQuery query;
    query.prepare(QString("%1 WHERE %2 = ?")
                  .arg(Utils::Main::getPrepUpdateStr(tableName(), QStringList()
                                   << getNameColumnName()
                                   << getNameColumnDescription()))
                  .arg(getNameColumnId()));
    query.addBindValue(locality.name());
    query.addBindValue(locality.description());
    query.addBindValue(locality.id());

    if (!query.exec()) {
        emit error(query.lastError().text());
        return false;
    }

    return true;
}

bool LocalitiesTable::setName(const qlonglong localityId, const QString &localityName) const
{
    return updateValue(getColumnPosition(FN_ID), localityId, localityName);
}

bool LocalitiesTable::setDescription(const qlonglong localityId, const QString &description) const
{
    return updateValue(getColumnPosition(FN_DESCRIPTION), localityId, description);
}

QSqlField LocalitiesTable::primaryField() const
{
    return getColumnByName(FN_ID);
}

QString LocalitiesTable::getNameColumnId(const bool withTableName) const
{
    if (!withTableName)
        return FN_ID;
    return QString(tableName() + "." + FN_ID);
}

QString LocalitiesTable::getNameColumnName(const bool withTableName) const
{
    if (!withTableName)
        return FN_NAME;
    return QString(tableName() + "." + FN_NAME);
}

QString LocalitiesTable::getNameColumnDescription(const bool withTableName) const
{
    if (!withTableName)
        return FN_DESCRIPTION;
    return QString(tableName() + "." + FN_DESCRIPTION);
}

void LocalitiesTable::initColumns()
{
    m_columns.append(QSqlField(FN_ID, QVariant::LongLong));
    m_columns.append(QSqlField(FN_NAME, QVariant::String));
    m_columns.append(QSqlField(FN_DESCRIPTION, QVariant::String));
}
