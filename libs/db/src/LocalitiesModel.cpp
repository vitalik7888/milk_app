#include "LocalitiesModel.h"

#include "LocalitiesDao.h"
#include <Locality.h>
#include "DbUtils.h"
// Qt
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>

USE_DB_NAMESPACE
using DC = DbConstants;

//--------------------------------------------------------------------------------------------------
LocalitiesDao::LocalitiesDao(QObject *parent):
    DaoSql(parent) {}

QString LocalitiesDao::getCreateTableStr() const
{
    return DC::TL_CREATE_TABLE_SQL;
}

QString LocalitiesDao::_tableName() const
{
    return DC::TL_TABLE_NAME;
}

QString LocalitiesDao::_primaryFieldName() const
{
    return DC::TL_FN_ID;
}

QStringList LocalitiesDao::_fieldsNames() const
{
    return { primaryFieldName(),
                DC::TL_FN_NAME,
                DC::TL_FN_DESCRIPTION,
    };
}

bool LocalitiesDao::_insert(MilkBaseItem *item)
{
    const auto locality = dynamic_cast<Locality *>(item);
    Q_ASSERT(locality);

    QSqlQuery query(m_db);
    query.prepare(DbUtils::getPrepInsertStr(DC::TL_TABLE_NAME, { DC::TL_FN_NAME, DC::TL_FN_DESCRIPTION }));
    query.addBindValue(locality->name());
    query.addBindValue(locality->description());

    if (!query.exec()) {
        _error(query.lastError().text());
        return false;
    }

    item->setMilkId(query.lastInsertId().toInt());
    return true;
}

bool LocalitiesDao::_update(const MilkBaseItem *item)
{
    const auto locality = static_cast<const Locality *>(item);
    Q_ASSERT(locality);

    QSqlQuery query(m_db);
    query.prepare(QString("%1 WHERE %2 = ?")
                  .arg(DbUtils::getPrepUpdateStr(DC::TL_TABLE_NAME, { DC::TL_FN_NAME, DC::TL_FN_DESCRIPTION }))
                  .arg(DC::TL_FN_ID));
    query.addBindValue(locality->name());
    query.addBindValue(locality->description());
    query.addBindValue(locality->milkId());

    if (!query.exec()) {
        _error(query.lastError().text());
        return false;
    }

    return true;
}

DaoItem LocalitiesDao::fromRecord(const QSqlRecord &record)
{
    if (record.isEmpty())
        return Q_NULLPTR;

    return std::make_unique<Locality>(record.value(DC::TL_FN_ID).toInt(),
                                      record.value(DC::TL_FN_NAME).toString(),
                                      record.value(DC::TL_FN_DESCRIPTION).toString());
}

//--------------------------------------------------------------------------------------------------
LocalitiesModel::LocalitiesModel(QObject *parent):
    MilkModel(parent)
{
}

QVariant db::LocalitiesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return {};

    const Locality& locality = static_cast<const Locality&>(*m_repository.get(index.row()));

    switch (role) {
    case static_cast<int>(DC::LocalitiesRoles::MilkIdRole):
        return locality.milkId();
    case static_cast<int>(DC::LocalitiesRoles::NameRole):
        return locality.name();
    case static_cast<int>(DC::LocalitiesRoles::DescriptionRole):
        return locality.description();
    }

    return {};
}

bool db::LocalitiesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role == static_cast<int>(DC::LocalitiesRoles::MilkIdRole))
        return false;

    Locality& locality = static_cast<Locality&>(*m_repository.get(index.row()));

    bool isOk = false;
    switch (role) {
    case static_cast<int>(DC::LocalitiesRoles::NameRole):
        locality.setName(value.toString());
        isOk = m_dao->updateValue(DC::TL_NAME, locality.milkId(), value.toString());
        break;
    case static_cast<int>(DC::LocalitiesRoles::DescriptionRole):
        locality.setDescription(value.toString());
        isOk = m_dao->updateValue(DC::TL_DESCRIPTION, locality.milkId(), value.toString());
        break;
    }

    if (isOk)
        emit dataChanged(index, index);

    return isOk;
}

QHash<int, QByteArray> db::LocalitiesModel::roleNames() const
{
    return {
        {static_cast<int>(DC::LocalitiesRoles::MilkIdRole), "milkId"},
        {static_cast<int>(DC::LocalitiesRoles::NameRole), "name"},
        {static_cast<int>(DC::LocalitiesRoles::DescriptionRole), "description"},
    };
}

void db::LocalitiesModel::copyItemValues(MilkBaseItem *left, const MilkBaseItem *right)
{
    auto itemSource = static_cast<Locality *>(left);
    auto item = static_cast<const Locality *>(right);
    itemSource->setName(item->name());
    itemSource->setDescription(item->description());
}

void db::LocalitiesModel::appendToRepository(const MilkBaseItem *item)
{
    m_repository.append<Locality>(item);
}
