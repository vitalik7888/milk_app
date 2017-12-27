#include "MilkPointsModel.h"

#include "MilkpointsDao.h"
#include <MilkPoint.h>
#include <Locality.h>
#include "DbUtils.h"
#include <TypesConstants.h>
// Qt
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

USE_DB_NAMESPACE
using DC = DbConstants;
using TC = TypesConstants;


MilkPointDao::MilkPointDao(QObject *parent):
    DaoSql(parent) {}

QString MilkPointDao::getCreateTableStr() const
{
    return DC::TMP_CREATE_TABLE_SQL;
}

QString MilkPointDao::_tableName() const
{
    return DC::TMP_TABLE_NAME;
}

QString MilkPointDao::_primaryFieldName() const
{
    return DC::TMP_FN_ID;
}

QStringList MilkPointDao::_fieldsNames() const
{
    return { primaryFieldName(),
                DC::TMP_FN_LOCALITY_ID,
                DC::TMP_FN_NAME,
                DC::TMP_FN_DESCRIPTION
    };
}

DaoItem MilkPointDao::fromRecord(const QSqlRecord &record)
{
    if (record.isEmpty())
        return Q_NULLPTR;

    return std::make_unique<MilkPointData>(record.value(DC::TMP_FN_ID).toInt(),
                                       record.value(DC::TMP_FN_LOCALITY_ID).toInt(),
                                       record.value(DC::TMP_FN_NAME).toString(),
                                       record.value(DC::TMP_FN_DESCRIPTION).toString());
}

bool MilkPointDao::_insert(MilkBaseItem *item)
{
    const auto milkPoint = static_cast<MilkPoint *>(item);
    Q_ASSERT(milkPoint);

    QSqlQuery query(m_db);
    query.prepare(DbUtils::getPrepInsertStr(
                      DC::TMP_TABLE_NAME, { DC::TMP_FN_LOCALITY_ID, DC::TMP_FN_NAME, DC::TMP_FN_DESCRIPTION }));
    query.addBindValue(milkPoint->locality()->milkId());
    query.addBindValue(milkPoint->name());
    query.addBindValue(milkPoint->description());

    if (!query.exec()) {
        _error(query.lastError().text());
        return false;
    }

    item->setMilkId(query.lastInsertId().toInt());
    return true;
}

bool MilkPointDao::_update(const MilkBaseItem *item)
{
    const auto milkPoint = static_cast<const MilkPoint *>(item);
    Q_ASSERT(milkPoint);

    QSqlQuery query(m_db);
    query.prepare(QString("%1 WHERE %2 = ?")
                  .arg(DbUtils::getPrepUpdateStr(
                           DC::TMP_TABLE_NAME, { DC::TMP_FN_LOCALITY_ID, DC::TMP_FN_NAME,
                                                 DC::TMP_FN_DESCRIPTION }))
                  .arg(DC::TMP_FN_ID));
    query.addBindValue(milkPoint->locality()->milkId());
    query.addBindValue(milkPoint->name());
    query.addBindValue(milkPoint->description());
    query.addBindValue(milkPoint->milkId());

    if (!query.exec()) {
        _error(query.lastError().text());
        return false;
    }

    return true;
}

//--------------------------------------------------------------------------------------------------
MilkPointsModel::MilkPointsModel(QObject *parent):
    MilkPointsModel(Q_NULLPTR, parent)
{

}

MilkPointsModel::MilkPointsModel(LocalitiesModel *localities, QObject *parent):
    MilkModel(parent),
    m_localities(localities)
{
//    connect(m_localities, &LocalitiesModel::endRefresh, this, &MilkPointsModel::refresh);
}

LocalitiesModel *MilkPointsModel::localities() const
{
    return m_localities;
}

QVariant db::MilkPointsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return {};

    const auto milkPoint = static_cast<const MilkPoint *>(m_repository.get(index.row()));

    switch (role) {
    case static_cast<int>(DC::MilkPointRoles::MilkIdRole):
        return milkPoint->milkId();
    case static_cast<int>(DC::MilkPointRoles::MP_NameRole):
        return milkPoint->name();
    case static_cast<int>(DC::MilkPointRoles::MP_DescriptionRole):
        return milkPoint->description();
    case static_cast<int>(DC::MilkPointRoles::MP_LocalityIdRole):
        return milkPoint->locality() ? milkPoint->locality()->milkId() : TC::DEFAULT_ID;
    case static_cast<int>(DC::MilkPointRoles::MP_LocalityNameRole):
        return milkPoint->locality() ? milkPoint->locality()->name() : TC::Localities::DEF_NAME;
    }

    return {};

}

bool db::MilkPointsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role == static_cast<int>(DC::MilkPointRoles::MilkIdRole) ||
            role == static_cast<int>(DC::MilkPointRoles::MP_LocalityNameRole))
        return false;

    auto &milkPoint = static_cast<MilkPoint&>(*m_repository.get(index.row()));

    bool isOk = false;
    switch (role) {
    case static_cast<int>(DC::MilkPointRoles::MP_NameRole):
        isOk = m_dao->updateValue(DC::TMP_NAME, milkPoint.milkId(), value.toString());
        if (isOk)
            milkPoint.setName(value.toString());
        break;
    case static_cast<int>(DC::MilkPointRoles::MP_DescriptionRole):
        isOk = m_dao->updateValue(DC::TMP_DESCRIPTION, milkPoint.milkId(), value.toString());
        if (isOk)
            milkPoint.setDescription(value.toString());
        break;
    case static_cast<int>(DC::MilkPointRoles::MP_LocalityIdRole):
        isOk = m_dao->updateValue(DC::TMP_LOCALITY_ID, milkPoint.milkId(), value.toInt());
        if (isOk)
            milkPoint.setLocality(static_cast<const Locality*>(localities()->getItemById(value.toInt())));
        break;
    }

    if (isOk)
        emit dataChanged(index, index);

    return isOk;
}

QHash<int, QByteArray> db::MilkPointsModel::roleNames() const
{
    return {
        {static_cast<int>(DC::MilkPointRoles::MilkIdRole), "milkId"},
        {static_cast<int>(DC::MilkPointRoles::MP_NameRole), "name"},
        {static_cast<int>(DC::MilkPointRoles::MP_DescriptionRole), "description"},
        {static_cast<int>(DC::MilkPointRoles::MP_LocalityIdRole), "localityId"},
        {static_cast<int>(DC::MilkPointRoles::MP_LocalityNameRole), "localityName"},
    };
}

void MilkPointsModel::copyItemValues(MilkBaseItem *left, const MilkBaseItem *right)
{
    auto itemSource = static_cast<MilkPoint *>(left);
    auto item = static_cast<const MilkPoint *>(right);
    itemSource->setName(item->name());
    itemSource->setDescription(item->description());
    itemSource->setLocality(item->locality());
}

void MilkPointsModel::appendToRepository(const MilkBaseItem *item)
{
    m_repository.append<MilkPoint>(item);
}

void db::MilkPointsModel::refresh()
{
    emit beginRefresh();
    clear();

    const auto items = m_dao->get();
    for (const auto &item : *items)
    {
        const auto daoItem = static_cast<const MilkPointData *>(item.get());
        const auto locality = static_cast<const Locality *>(m_localities->getItemById(daoItem->localityId()));
        MilkPoint milkPoint(daoItem->milkId(), daoItem->name(), daoItem->description(), locality);
        appendToRepository(&milkPoint);
    }

    emit endRefresh();
}
