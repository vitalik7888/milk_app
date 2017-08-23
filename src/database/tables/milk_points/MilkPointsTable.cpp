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
MilkPointsTable::MilkPointsTable(QObject *parent):
    MilkPointsTable(Q_NULLPTR, QSqlDatabase(), parent)
{

}

MilkPointsTable::MilkPointsTable(LocalitiesTable *localities, QSqlDatabase db, QObject *parent):
    Table(new MilkPointDao(db), parent, db),
    m_localities(localities)
{
    setObjectName("MilkPointsTable");
    qDebug() << "init " + objectName();

    setQuery(selectAll());
}

MilkPointsTable::~MilkPointsTable()
{

}

QString MilkPointsTable::tableName() const
{
    return TABLE_NAME;
}

MilkPointData MilkPointsTable::getMilkPointData(const milk_id milkPointId) const
{
    return dao()->get(milkPointId);
}

MilkPoint *MilkPointsTable::getMilkPoint(const qlonglong milkPointId)
{
    return new MilkPoint(dao()->get(milkPointId), this);
}

void MilkPointsTable::insert(int index, MilkPoint *milkPoint)
{
    if(index < 0 || index > rowCount()) {
        return;
    }

    emit beginInsertRows(QModelIndex(), index, index);
    dao()->insert(milkPoint->data());
    emit endInsertRows();
}

void MilkPointsTable::append(MilkPoint *milkPoint)
{
    insert(rowCount(), milkPoint);
}

void MilkPointsTable::update(MilkPoint *milkPoint) const
{
    dao()->update(milkPoint->data());
}

void MilkPointsTable::setName(const milk_id milkPointId, const QString &milkPointName) const
{
    m_dao->updateValue(FN_NAME, milkPointId, milkPointName);
}

void MilkPointsTable::setDescription(const milk_id milkPointId, const QString &description) const
{
    m_dao->updateValue(FN_DESCRIPTION, milkPointId, description);
}

LocalitiesTable *MilkPointsTable::localities() const
{
    return m_localities;
}

QString MilkPointsTable::primaryField() const
{
    return FN_ID;
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

MilkPointDao *MilkPointsTable::dao() const
{
    return dynamic_cast<MilkPointDao *>(m_dao.data());
}

int db::MilkPointsTable::getColPosition(const QString &columnName) const
{
    if (columnName == FN_ID)
        return MilkPointsTableColumns::MPT_ID;
    if (columnName == FN_LOCALITY_ID)
        return MilkPointsTableColumns::MPT_LOCALITY_ID;
    if (columnName == FN_NAME)
        return MilkPointsTableColumns::MPT_NAME;
    if (columnName == FN_DESCRIPTION)
        return MilkPointsTableColumns::MPT_DESCRIPTION;
    return -1;
}
