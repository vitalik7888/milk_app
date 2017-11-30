#include "LocalitiesTable.h"

#include "LocalitiesDao.h"
#include "DbUtils.h"
// Qt
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>

USE_DB_NAMESPACE
using DC = DbConstants;

//--------------------------------------------------------------------------------------------------
LocalitiesDao::LocalitiesDao(LocalitiesTable *table):
    Dao(table) {}

bool LocalitiesDao::insert(const QVariant &data) const
{
    Q_ASSERT(data.canConvert<LocalityData>());
    const LocalityData locality = data.value<LocalityData>();

    QSqlQuery query(m_table->database());
    query.prepare(DbUtils::getPrepInsertStr(DC::TL_TABLE_NAME, { DC::TL_FN_NAME, DC::TL_FN_DESCRIPTION }));
    query.addBindValue(locality.name());
    query.addBindValue(locality.description());

    if (!query.exec()) {
        _error(query.lastError().text());
        return false;
    }

    return true;
}

bool LocalitiesDao::update(const QVariant &data) const
{
    Q_ASSERT(data.canConvert<LocalityData>());
    const LocalityData locality = data.value<LocalityData>();

    QSqlQuery query(m_table->database());
    query.prepare(QString("%1 WHERE %2 = ?")
                  .arg(DbUtils::getPrepUpdateStr(DC::TL_TABLE_NAME, { DC::TL_FN_NAME, DC::TL_FN_DESCRIPTION }))
                  .arg(DC::TL_FN_ID));
    query.addBindValue(locality.name());
    query.addBindValue(locality.description());
    query.addBindValue(locality.id());

    if (!query.exec()) {
        _error(query.lastError().text());
        return false;
    }

    return true;
}

//--------------------------------------------------------------------------------------------------
LocalitiesTable::LocalitiesTable(QObject *parent) : LocalitiesTable(QSqlDatabase(), parent) {}

LocalitiesTable::LocalitiesTable(QSqlDatabase db, QObject *parent):
    Table(new LocalitiesDao(this), db, parent)
{
    setObjectName("LocalitiesTable");

    setQuery(selectAll());
}

LocalitiesTable::~LocalitiesTable()
{
}

QString LocalitiesTable::tableName() const
{
    return DC::TL_TABLE_NAME;
}

std::experimental::optional<LocalityData> LocalitiesTable::getLocalityData(const DbConstants::milk_id localityId) const
{
    const auto data = dao()->get(localityId);
    if (data.isNull())
        return {};

    return fromRecord(data.value<QSqlRecord>());
}

Locality *LocalitiesTable::getLocality(const int localityId)
{
    const auto data = getLocalityData(localityId);
    if (!data)
        return Q_NULLPTR;

    return new Locality(data.value(), this);
}

bool LocalitiesTable::insert(int position, Locality *locality)
{
    return Table::insert(position, QVariant::fromValue(locality->data()));
}

bool LocalitiesTable::append(Locality *locality)
{
    return Table::append(QVariant::fromValue(locality->data()));
}

QVariant LocalitiesTable::get(const int row)
{
    const auto _id = getIdByRow(row);
    if (_id < 0)
        return {};

    return QVariant::fromValue(
                new Locality({
                                 _id,
                                 this->data(index(row, DC::TL_NAME)).toString(),
                                 this->data(index(row, DC::TL_DESCRIPTION)).toString()
                             },
                             this));
}

bool LocalitiesTable::set(const int row, Locality *locality)
{
    return Table::set(row, QVariant::fromValue(locality->data()));
}

QString LocalitiesTable::primaryField() const
{
    return DC::TL_FN_ID;
}

QString LocalitiesTable::getColName(const int position, const bool withTableName) const
{
    QString columnName;
    switch (position) {
    case DC::TL_ID:
        columnName = DC::TL_FN_ID;
        break;
    case DC::TL_NAME:
        columnName = DC::TL_FN_NAME;
        break;
    case DC::TL_DESCRIPTION:
        columnName = DC::TL_FN_DESCRIPTION;
        break;
    default:
        columnName = "";
        break;
    }

    return withTableName ? QString("%1.%2").arg(DC::TL_TABLE_NAME).arg(columnName) : columnName;
}

LocalitiesDao *LocalitiesTable::dao() const
{
    return dynamic_cast<LocalitiesDao *>(m_dao.data());
}

LocalityData LocalitiesTable::fromRecord(const QSqlRecord &record)
{
    return {
        record.value(DC::TL_FN_ID).toInt(),
                record.value(DC::TL_FN_NAME).toString(),
                record.value(DC::TL_FN_DESCRIPTION).toString()
    };
}

int db::LocalitiesTable::getColPosition(const QString &columnName) const
{
    if (columnName == DC::TL_FN_ID)
        return DC::TL_ID;
    if (columnName == DC::TL_FN_NAME)
        return DC::TL_NAME;
    if (columnName == DC::TL_FN_DESCRIPTION)
        return DC::TL_DESCRIPTION;
    return -1;
}
