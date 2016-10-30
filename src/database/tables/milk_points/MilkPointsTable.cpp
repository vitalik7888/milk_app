#include "MilkPointsTable.h"

#include "milkpointdao.h"
#include "tables/localities/LocalitiesTable.h"
#include "Utils.h"
// Qt
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

USE_DB_NAMESPACE

static const char *TABLE_NAME = "milk_points";
static const char *FN_ID = "id";
static const char *FN_LOCALITY_ID = "locality_id";
static const char *FN_NAME = "name";
static const char *FN_DESCRIPTION = "description";

//--------------------------------------------------------------------------------------------------
MilkPointDao::MilkPointDao(const QSqlDatabase &db):
    Dao(TABLE_NAME, FN_ID, db) {}

MilkPointData MilkPointDao::get(const milk_id id) const
{
    QSqlQuery query;
    query.prepare(QString("%1 WHERE %2 = ?")
                    .arg(Utils::Main::getSelectStr(
                             TABLE_NAME, { FN_LOCALITY_ID, FN_NAME, FN_DESCRIPTION }))
                    .arg(FN_ID));
    query.addBindValue(id);

    MilkPointData data;
    if (query.exec() && query.first())
    {
        data.setLocalityId(query.value(0).toLongLong());
        data.setName(query.value(1).toString());
        data.setDescription(query.value(2).toString());
        data.setId(id);
    } else {
        const auto err = QString("Отсутствует молокопункт с id = %1").arg(id);
        qDebug() << err;
        throw err;
    }

    return data;
}

void MilkPointDao::insert(const MilkPointData &data) const
{
    QSqlQuery query;
    query.prepare(Utils::Main::getPrepInsertStr(
                      TABLE_NAME, { FN_LOCALITY_ID, FN_NAME, FN_DESCRIPTION }));
    query.addBindValue(data.localityId());
    query.addBindValue(data.name());
    query.addBindValue(data.description());

    if (!query.exec()) {
        const auto err = query.lastError().text();
        qDebug() << err;
        throw err;
    }
}

void MilkPointDao::update(const MilkPointData &data) const
{
    QSqlQuery query;
    query.prepare(QString("%1 WHERE %2 = ?")
                  .arg(Utils::Main::getPrepUpdateStr(
                           TABLE_NAME, { FN_LOCALITY_ID, FN_NAME, FN_DESCRIPTION }))
                  .arg(FN_ID));
    query.addBindValue(data.localityId());
    query.addBindValue(data.name());
    query.addBindValue(data.description());
    query.addBindValue(data.id());

    if (!query.exec()) {
        const auto err = query.lastError().text();
        qDebug() << err;
        throw err;
    }
}

//--------------------------------------------------------------------------------------------------
MilkPointsTable::MilkPointsTable(LocalitiesTable *parent, QSqlDatabase db):
    Table(new MilkPointDao(db), parent, db),
    m_localities(parent)
{
    setObjectName("MilkPointsTable");
    qDebug() << "init " + objectName();

    initColumns();
    setQuery(selectAll());
}

MilkPointsTable::~MilkPointsTable()
{

}

QString MilkPointsTable::tableName() const
{
    return TABLE_NAME;
}

MilkPointData MilkPointsTable::getMilkPoint(const milk_id milkPointId) const
{
    return dao()->get(milkPointId);
}

void MilkPointsTable::insert(const MilkPointData &milkPoint)
{
    dao()->insert(milkPoint);
}

void MilkPointsTable::update(const MilkPointData &milkPoint) const
{
    dao()->update(milkPoint);
}

bool MilkPointsTable::setName(const milk_id milkPointId, const QString &milkPointName) const
{
    return updateValue(getColumnPosition(FN_NAME), milkPointId, milkPointName);
}

bool MilkPointsTable::setDescription(const milk_id milkPointId, const QString &description) const
{
    return updateValue(getColumnPosition(FN_DESCRIPTION), milkPointId, description);
}

LocalitiesTable *MilkPointsTable::getLocalities() const
{
    return m_localities;
}

QSqlField MilkPointsTable::primaryField() const
{
    return getColumnByName(FN_ID);
}

QString MilkPointsTable::getColName(const int position, const bool withTableName) const
{
    QString columnName;
    switch (position) {
    case MilkPointsTableColumns::MPT_ID:
        columnName = FN_ID;
        break;
    case MilkPointsTableColumns::MPT_LOCALITY_ID:
        columnName = FN_LOCALITY_ID;
        break;
    case MilkPointsTableColumns::MPT_NAME:
        columnName = FN_NAME;
        break;
    case MilkPointsTableColumns::MPT_DESCRIPTION:
        columnName = FN_DESCRIPTION;
        break;
    default:
        columnName = "";
        break;
    }

    return withTableName ? QString("%1.%2").arg(TABLE_NAME).arg(columnName) : columnName;
}

void MilkPointsTable::initColumns()
{
    m_columns.append(QSqlField(FN_ID, QVariant::LongLong));
    m_columns.append(QSqlField(FN_LOCALITY_ID, QVariant::LongLong));
    m_columns.append(QSqlField(FN_NAME, QVariant::String));
    m_columns.append(QSqlField(FN_DESCRIPTION, QVariant::String));
}

MilkPointDao *MilkPointsTable::dao() const
{
    return dynamic_cast<MilkPointDao *>(m_dao.data());
}
