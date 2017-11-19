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
using DC = DbConstants;
using DCMP = DC::MilkPoints;
using DCL = DC::Localities;


MilkPointDao::MilkPointDao(MilkPointsTable *table):
    Dao(table) {}

std::experimental::optional<MilkPointData> MilkPointDao::get(const milk_id id) const
{
    QSqlQuery query;
    query.prepare(QString("%1 WHERE %2 = ?")
                  .arg(Utils::Main::getSelectStr(
                           DCMP::TABLE_NAME, { DCMP::FN_LOCALITY_ID, DCMP::FN_NAME, DCMP::FN_DESCRIPTION }))
                  .arg(DCMP::FN_ID));
    query.addBindValue(id);

    if (query.exec() && query.first())
    {
        return MilkPointData(
                    id,
                    query.value(DCMP::FN_LOCALITY_ID).toLongLong(),
                    query.value(DCMP::FN_NAME).toString(),
                    query.value(DCMP::FN_DESCRIPTION).toString()
                    );
    } else
        _error(QString("Отсутствует молокопункт с id = %1").arg(id));

    return {};
}

bool MilkPointDao::insert(const MilkPointData &data) const
{
    QSqlQuery query;
    query.prepare(Utils::Main::getPrepInsertStr(
                      DCMP::TABLE_NAME, { DCMP::FN_LOCALITY_ID, DCMP::FN_NAME, DCMP::FN_DESCRIPTION }));
    query.addBindValue(data.localityId());
    query.addBindValue(data.name());
    query.addBindValue(data.description());

    if (!query.exec()) {
        _error(query.lastError().text());
        return false;
    }

    return true;
}

bool MilkPointDao::update(const MilkPointData &data) const
{
    QSqlQuery query;
    query.prepare(QString("%1 WHERE %2 = ?")
                  .arg(Utils::Main::getPrepUpdateStr(
                           DCMP::TABLE_NAME, { DCMP::FN_LOCALITY_ID, DCMP::FN_NAME, DCMP::FN_DESCRIPTION }))
                  .arg(DCMP::FN_ID));
    query.addBindValue(data.localityId());
    query.addBindValue(data.name());
    query.addBindValue(data.description());
    query.addBindValue(data.id());

    if (!query.exec()) {
        _error(query.lastError().text());
        return false;
    }

    return true;
}

//--------------------------------------------------------------------------------------------------
MilkPointsTable::MilkPointsTable(QObject *parent):
    MilkPointsTable(Q_NULLPTR, QSqlDatabase(), parent)
{

}

MilkPointsTable::MilkPointsTable(LocalitiesTable *localities, QSqlDatabase db, QObject *parent):
    Table(new MilkPointDao(this), db, parent),
    m_localities(localities)
{
    setObjectName("MilkPointsTable");

    setQuery(selectAll());
}

MilkPointsTable::~MilkPointsTable()
{

}

QString MilkPointsTable::tableName() const
{
    return DCMP::TABLE_NAME;
}

std::experimental::optional<MilkPointData> MilkPointsTable::getMilkPointData(const milk_id milkPointId) const
{
    return dao()->get(milkPointId);
}

MilkPoint *MilkPointsTable::getMilkPoint(const qlonglong milkPointId)
{
    const auto mpData = getMilkPointData(milkPointId);
    if (!mpData)
        return Q_NULLPTR;

    const auto data = mpData.value();
    auto locality = localities()->getLocality(data.localityId());
    auto milkPoint = new MilkPoint(data.id(), data.name(), data.description(), locality, this);
    locality->setParent(milkPoint);

    return milkPoint;
}

bool MilkPointsTable::insert(int index, MilkPoint *milkPoint)
{
    if(index < 0 || index > rowCount()) {
        return false;
    }

    emit beginInsertRows(QModelIndex(), index, index);
    const bool isOk = dao()->insert(milkPoint->data());
    emit endInsertRows();

    return isOk;
}

bool MilkPointsTable::append(MilkPoint *milkPoint)
{
    return insert(rowCount(), milkPoint);
}

bool MilkPointsTable::update(MilkPoint *milkPoint) const
{
    return dao()->update(milkPoint->data());
}

bool MilkPointsTable::setName(const milk_id milkPointId, const QString &milkPointName) const
{
    return m_dao->updateValue(DCMP::FN_NAME, milkPointId, milkPointName);
}

bool MilkPointsTable::setDescription(const milk_id milkPointId, const QString &description) const
{
    return m_dao->updateValue(DCMP::FN_DESCRIPTION, milkPointId, description);
}

LocalitiesTable *MilkPointsTable::localities() const
{
    return m_localities;
}

QString MilkPointsTable::primaryField() const
{
    return DCMP::FN_ID;
}

QString MilkPointsTable::getColName(const int position, const bool withTableName) const
{
    QString columnName;
    switch (position) {
    case DCMP::MPT_ID:
        columnName = DCMP::FN_ID;
        break;
    case DCMP::MPT_LOCALITY_ID:
        columnName = DCMP::FN_LOCALITY_ID;
        break;
    case DCMP::MPT_NAME:
        columnName = DCMP::FN_NAME;
        break;
    case DCMP::MPT_DESCRIPTION:
        columnName = DCMP::FN_DESCRIPTION;
        break;
    default:
        columnName = "";
        break;
    }

    return withTableName ? QString("%1.%2").arg(DCMP::TABLE_NAME).arg(columnName) : columnName;
}

MilkPointDao *MilkPointsTable::dao() const
{
    return dynamic_cast<MilkPointDao *>(m_dao.data());
}

int db::MilkPointsTable::getColPosition(const QString &columnName) const
{
    if (columnName == DCMP::FN_ID)
        return DCMP::MPT_ID;
    if (columnName == DCMP::FN_LOCALITY_ID)
        return DCMP::MPT_LOCALITY_ID;
    if (columnName == DCMP::FN_NAME)
        return DCMP::MPT_NAME;
    if (columnName == DCMP::FN_DESCRIPTION)
        return DCMP::MPT_DESCRIPTION;
    return -1;
}
