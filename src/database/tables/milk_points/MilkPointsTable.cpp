#include "MilkPointsTable.h"

#include "tables/localities/LocalitiesTable.h"
#include "Utils.h"
// qt
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

static const char *FN_ID = "id";
static const char *FN_LOCALITY_ID = "locality_id";
static const char *FN_NAME = "name";
static const char *FN_DESCRIPTION = "description";


MilkPointsTable::MilkPointsTable(LocalitiesTable *parent, QSqlDatabase db):
    Table(parent, db),
    m_localities(parent)
{
    setObjectName("MilkPointsTable");
    qDebug() << "init " + objectName();

    initColumns();
    setQuery(selectAll());
}

MilkPointsTable::~MilkPointsTable()
{
    qDebug() << "delete " + objectName();
}

QString MilkPointsTable::tableName() const
{
    return "milk_points";
}

QString MilkPointsTable::getNameColumnId(const bool withTableName) const
{
    if (!withTableName)
        return FN_ID;
    return QString(tableName() + "." + FN_ID);
}

QString MilkPointsTable::getNameColumnLocalityId(const bool withTableName) const
{
    if (!withTableName)
        return FN_LOCALITY_ID;
    return QString(tableName() + "." + FN_LOCALITY_ID);
}

QString MilkPointsTable::getNameColumnName(const bool withTableName) const
{
    if (!withTableName)
        return FN_NAME;
    return QString(tableName() + "." + FN_NAME);
}

QString MilkPointsTable::getNameColumnDescription(const bool withTableName) const
{
    if (!withTableName)
        return FN_DESCRIPTION;
    return QString(tableName() + "." + FN_DESCRIPTION);
}

QSqlField MilkPointsTable::getFieldId() const
{
    return getColumnByName(FN_ID);
}

QSqlField MilkPointsTable::getFieldLocalityId() const
{
    return getColumnByName(FN_LOCALITY_ID);
}

QSqlField MilkPointsTable::getFieldName() const
{
    return getColumnByName(FN_NAME);
}

QSqlField MilkPointsTable::getFieldDescription() const
{
    return getColumnByName(FN_DESCRIPTION);
}

MilkPoint MilkPointsTable::getMilkPoint(const qint32 milkPointId) const
{
    QSqlQuery query;
    query.prepare(QString("%1 WHERE %2 = ?")
                    .arg(Utils::Main::getSelectStr(tableName(), QStringList()
                                      << getNameColumnLocalityId(true)
                                      << getNameColumnName(true)
                                      << getNameColumnDescription()))
                    .arg(getFieldId().name()));
    query.addBindValue(milkPointId);

    if (query.exec() && query.first())
    {
        return MilkPoint(m_localities->getLocality(query.value(0).toLongLong()),
                         query.value(1).toString(),
                         query.value(2).toString(),
                         milkPointId);
    } else
        emit error(tr("Отсутствует молокопункт с id = ") + QString::number(milkPointId));

    return MilkPoint::CREATE_NULL();
}

bool MilkPointsTable::insert(const MilkPoint &milkPoint)
{
    QSqlQuery query;
    query.prepare(Utils::Main::getPrepInsertStr(tableName(), QStringList()
                                   << getNameColumnLocalityId()
                                   << getNameColumnName()
                                   << getNameColumnDescription()));
    query.addBindValue(milkPoint.locality().id());
    query.addBindValue(milkPoint.name());
    query.addBindValue(milkPoint.description());

    if (!query.exec()) {
        emit error(query.lastError().text());
        return false;
    }

    return true;
}

bool MilkPointsTable::update(const MilkPoint &milkPoint) const
{
    QSqlQuery query;
    query.prepare(QString("%1 WHERE %2 = ?")
                  .arg(Utils::Main::getPrepUpdateStr(tableName(), QStringList()
                                   << getNameColumnLocalityId()
                                   << getNameColumnName()
                                   << getNameColumnDescription()))
                  .arg(getNameColumnId()));
    query.addBindValue(milkPoint.locality().id());
    query.addBindValue(milkPoint.name());
    query.addBindValue(milkPoint.description());
    query.addBindValue(milkPoint.id());

    if (!query.exec()) {
        emit error(query.lastError().text());
        return false;
    }

    return true;
}

bool MilkPointsTable::setName(const qint32 milkPointId, const QString &milkPointName) const
{
    return updateValue(getColumnPosition(FN_NAME), milkPointId, milkPointName);
}

bool MilkPointsTable::setDescription(const qint32 milkPointId, const QString &description) const
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

void MilkPointsTable::initColumns()
{
    m_columns.append(QSqlField(FN_ID, QVariant::LongLong));
    m_columns.append(QSqlField(FN_LOCALITY_ID, QVariant::LongLong));
    m_columns.append(QSqlField(FN_NAME, QVariant::String));
    m_columns.append(QSqlField(FN_DESCRIPTION, QVariant::String));
}
