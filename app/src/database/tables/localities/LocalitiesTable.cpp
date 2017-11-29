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
using DCL = DC::Localities;

//--------------------------------------------------------------------------------------------------
LocalitiesDao::LocalitiesDao(LocalitiesTable *table):
    Dao(table) {}

bool LocalitiesDao::insert(const QVariant &data) const
{
    Q_ASSERT(data.canConvert<LocalityData>());
    const LocalityData locality = data.value<LocalityData>();

    QSqlQuery query(m_table->database());
    query.prepare(DbUtils::getPrepInsertStr(DCL::TABLE_NAME, { DCL::FN_NAME, DCL::FN_DESCRIPTION }));
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
                  .arg(DbUtils::getPrepUpdateStr(DCL::TABLE_NAME, { DCL::FN_NAME, DCL::FN_DESCRIPTION }))
                  .arg(DCL::FN_ID));
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
    return DCL::TABLE_NAME;
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
                                 this->data(index(row, DCL::LT_NAME)).toString(),
                                 this->data(index(row, DCL::LT_DESCRIPTION)).toString()
                             },
                             this));
}

bool LocalitiesTable::set(const int row, Locality *locality)
{
    return Table::set(row, QVariant::fromValue(locality->data()));
}

QString LocalitiesTable::primaryField() const
{
    return DCL::FN_ID;
}

QString LocalitiesTable::getColName(const int position, const bool withTableName) const
{
    QString columnName;
    switch (position) {
    case DCL::LT_ID:
        columnName = DCL::FN_ID;
        break;
    case DCL::LT_NAME:
        columnName = DCL::FN_NAME;
        break;
    case DCL::LT_DESCRIPTION:
        columnName = DCL::FN_DESCRIPTION;
        break;
    default:
        columnName = "";
        break;
    }

    return withTableName ? QString("%1.%2").arg(DCL::TABLE_NAME).arg(columnName) : columnName;
}

LocalitiesDao *LocalitiesTable::dao() const
{
    return dynamic_cast<LocalitiesDao *>(m_dao.data());
}

LocalityData LocalitiesTable::fromRecord(const QSqlRecord &record)
{
    return {
        record.value(DCL::FN_ID).toInt(),
                record.value(DCL::FN_NAME).toString(),
                record.value(DCL::FN_DESCRIPTION).toString()
    };
}

int db::LocalitiesTable::getColPosition(const QString &columnName) const
{
    if (columnName == DCL::FN_ID)
        return DCL::LT_ID;
    if (columnName == DCL::FN_NAME)
        return DCL::LT_NAME;
    if (columnName == DCL::FN_DESCRIPTION)
        return DCL::LT_DESCRIPTION;
    return -1;
}
