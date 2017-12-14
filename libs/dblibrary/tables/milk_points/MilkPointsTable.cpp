#include "MilkPointsTable.h"

#include "MilkpointsDao.h"
#include "tables/localities/LocalitiesTable.h"
#include "DbUtils.h"
// Qt
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

USE_DB_NAMESPACE
using DC = DbConstants;


MilkPointDao::MilkPointDao(MilkPointsTable *table):
    Dao(table) {}

bool MilkPointDao::insert(const QVariant &data) const
{
    Q_ASSERT(data.canConvert<MilkPointData>());
    const MilkPointData milkPoint = data.value<MilkPointData>();

    QSqlQuery query;
    query.prepare(DbUtils::getPrepInsertStr(
                      DC::TMP_TABLE_NAME, { DC::TMP_FN_LOCALITY_ID, DC::TMP_FN_NAME, DC::TMP_FN_DESCRIPTION }));
    query.addBindValue(milkPoint.localityId());
    query.addBindValue(milkPoint.name());
    query.addBindValue(milkPoint.description());

    if (!query.exec()) {
        _error(query.lastError().text());
        return false;
    }

    return true;
}

bool MilkPointDao::update(const QVariant &data) const
{
    Q_ASSERT(data.canConvert<MilkPointData>());
    const MilkPointData milkPoint = data.value<MilkPointData>();

    QSqlQuery query;
    query.prepare(QString("%1 WHERE %2 = ?")
                  .arg(DbUtils::getPrepUpdateStr(
                           DC::TMP_TABLE_NAME, { DC::TMP_FN_LOCALITY_ID, DC::TMP_FN_NAME, DC::TMP_FN_DESCRIPTION }))
                  .arg(DC::TMP_FN_ID));
    query.addBindValue(milkPoint.localityId());
    query.addBindValue(milkPoint.name());
    query.addBindValue(milkPoint.description());
    query.addBindValue(milkPoint.id());

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
    return DC::TMP_TABLE_NAME;
}

std::experimental::optional<MilkPointData> MilkPointsTable::getMilkPointData(const int milkPointId) const
{
    auto data = dao()->get(milkPointId);
    if (data.isNull())
        return {};

    return fromRecord(data.value<QSqlRecord>());
}

MilkPoint *MilkPointsTable::getMilkPoint(const int milkPointId)
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
    return Table::insert(index, QVariant::fromValue(milkPoint->data()));
}

bool MilkPointsTable::append(MilkPoint *milkPoint)
{
    return Table::append(QVariant::fromValue(milkPoint->data()));
}

bool MilkPointsTable::set(const int row, MilkPoint *milkPoint)
{
    return Table::set(row, QVariant::fromValue(milkPoint->data()));
}

LocalitiesTable *MilkPointsTable::localities() const
{
    return m_localities;
}

QString MilkPointsTable::primaryField() const
{
    return DC::TMP_FN_ID;
}

QString MilkPointsTable::getColName(const int position, const bool withTableName) const
{
    QString columnName;
    switch (position) {
    case DC::TMP_ID:
        columnName = DC::TMP_FN_ID;
        break;
    case DC::TMP_LOCALITY_ID:
        columnName = DC::TMP_FN_LOCALITY_ID;
        break;
    case DC::TMP_NAME:
        columnName = DC::TMP_FN_NAME;
        break;
    case DC::TMP_DESCRIPTION:
        columnName = DC::TMP_FN_DESCRIPTION;
        break;
    default:
        columnName = "";
        break;
    }

    return withTableName ? QString("%1.%2").arg(DC::TMP_TABLE_NAME).arg(columnName) : columnName;
}

MilkPointDao *MilkPointsTable::dao() const
{
    return dynamic_cast<MilkPointDao *>(m_dao.data());
}

MilkPointData MilkPointsTable::fromRecord(const QSqlRecord &record)
{
    return {
        record.value(DC::TMP_FN_ID).toInt(),
                record.value(DC::TMP_FN_LOCALITY_ID).toInt(),
                record.value(DC::TMP_FN_NAME).toString(),
                record.value(DC::TMP_FN_DESCRIPTION).toString()
    };
}

int db::MilkPointsTable::getColPosition(const QString &columnName) const
{
    if (columnName == DC::TMP_FN_ID)
        return DC::TMP_ID;
    if (columnName == DC::TMP_FN_LOCALITY_ID)
        return DC::TMP_LOCALITY_ID;
    if (columnName == DC::TMP_FN_NAME)
        return DC::TMP_NAME;
    if (columnName == DC::TMP_FN_DESCRIPTION)
        return DC::TMP_DESCRIPTION;
    return -1;
}


QVariant db::MilkPointsTable::get(const int row)
{
    const auto _id = getIdByRow(row);
    if (_id < 0)
        return {};

    auto locality = localities()->getLocality(data(index(row, DC::TMP_LOCALITY_ID)).toInt());
    return QVariant::fromValue(new MilkPoint(
                                   _id,
                                   data(index(row, DC::TMP_NAME)).toString(),
                                   data(index(row, DC::TMP_DESCRIPTION)).toString(),
                                   locality,
                                   this)
                               );}
