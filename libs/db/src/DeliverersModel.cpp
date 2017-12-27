#include "DeliverersModel.h"

#include "DeliverersDao.h"
#include <Deliverer.h>
#include <Locality.h>
#include "DbUtils.h"
#include <TypesConstants.h>
// Qt
#include <QSqlQuery>
#include <QSqlError>
#include <QMetaEnum>
#include <QDebug>

USE_DB_NAMESPACE
using DC = DbConstants;
using TC = TypesConstants;


DeliverersDao::DeliverersDao(QObject *parent):
    DaoSql(parent)
{

}

QString DeliverersDao::_tableName() const
{
    return DC::TD_TABLE_NAME;
}

QString DeliverersDao::_primaryFieldName() const
{
    return DC::TD_FN_ID;
}

QStringList DeliverersDao::_fieldsNames() const
{
    return { primaryFieldName(),
                DC::TD_FN_FIRST_NAME,
                DC::TD_FN_LAST_NAME,
                DC::TD_FN_LOCALITY_ID,
                DC::TD_FN_INN,
                DC::TD_FN_ADDRESS,
                DC::TD_FN_PHONE_NUMBER,
    };
}

QString DeliverersDao::getCreateTableStr() const
{
    return DC::TD_CREATE_TABLE_SQL;
}

bool DeliverersDao::_insert(MilkBaseItem *item)
{
    const auto deliverer = static_cast<Deliverer *>(item);
    Q_ASSERT(deliverer);

    QSqlQuery query(m_db);
    query.prepare(DbUtils::getPrepInsertStr(DC::TD_TABLE_NAME,
    { DC::TD_FN_FIRST_NAME, DC::TD_FN_LAST_NAME, DC::TD_FN_LOCALITY_ID,
      DC::TD_FN_INN, DC::TD_FN_ADDRESS, DC::TD_FN_PHONE_NUMBER }));
    query.addBindValue(deliverer->firstName());
    query.addBindValue(deliverer->lastName());
    query.addBindValue(deliverer->locality()->milkId());
    query.addBindValue(deliverer->inn());
    query.addBindValue(deliverer->address());
    query.addBindValue(deliverer->phoneNumber());

    if (!query.exec()) {
        _error(query.lastError().text());
        return false;
    }

    item->setMilkId(query.lastInsertId().toInt());
    return true;
}

bool DeliverersDao::_update(const MilkBaseItem *data)
{
    const auto deliverer = static_cast<const Deliverer*>(data);
    Q_ASSERT(deliverer);

    QSqlQuery query;
    query.prepare(QString("%1 WHERE %2 = ?")
                  .arg(DbUtils::getPrepUpdateStr(
                           DC::TD_TABLE_NAME,  { DC::TD_FN_FIRST_NAME,
                                                 DC::TD_FN_LAST_NAME,
                                                 DC::TD_FN_LOCALITY_ID,
                                                 DC::TD_FN_INN,
                                                 DC::TD_FN_ADDRESS,
                                                 DC::TD_FN_PHONE_NUMBER })
                       )
                  .arg(DC::TD_FN_ID));
    query.addBindValue(deliverer->firstName());
    query.addBindValue(deliverer->lastName());
    query.addBindValue(deliverer->locality()->milkId());
    query.addBindValue(deliverer->inn());
    query.addBindValue(deliverer->address());
    query.addBindValue(deliverer->phoneNumber());
    query.addBindValue(deliverer->milkId());

    if (!query.exec()) {
        _error(query.lastError().text());
        return false;
    }

    return true;
}

DaoItem DeliverersDao::fromRecord(const QSqlRecord &record)
{
    if (record.isEmpty())
        return Q_NULLPTR;

    return std::make_unique<DelivererData>(record.value(DC::TD_FN_ID).toInt(),
                                       record.value(DC::TD_FN_FIRST_NAME).toString(),
                                       record.value(DC::TD_FN_LAST_NAME).toString(),
                                       record.value(DC::TD_FN_LOCALITY_ID).toInt(),
                                       record.value(DC::TD_FN_INN).toString(),
                                       record.value(DC::TD_FN_ADDRESS).toString(),
                                       record.value(DC::TD_FN_PHONE_NUMBER).toString());
}

//--------------------------------------------------------------------------------------------------
DeliverersModel::DeliverersModel(QObject *parent):
    DeliverersModel(Q_NULLPTR, parent)
{

}

DeliverersModel::DeliverersModel(LocalitiesModel *localities, QObject *parent) :
    MilkModel(parent),
    m_localities(localities)
{
//    connect(m_localities, &LocalitiesModel::endRefresh, this, &DeliverersModel::refresh);
}

LocalitiesModel *DeliverersModel::localities() const
{
    return m_localities;
}

QVariant DeliverersModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (section) {
    case DC::TD_ID:
        return QVariant(tr("ID"));
    case DC::TD_FIRST_NAME:
        return QVariant(tr("Имя"));
    case DC::TD_LAST_NAME:
        return QVariant(tr("Фамилия"));
    case DC::TD_LOCALITY_ID:
        return QVariant(tr("Населенный пункт"));
    case DC::TD_INN:
        return QVariant(tr("ИНН"));
    case DC::TD_ADDRESS:
        return QVariant(tr("Адрес"));
    case DC::TD_PHONE_NUMBER:
        return QVariant(tr("Номер телефона"));
    }

    return MilkModel::headerData(section, orientation, role);
}

//QString db::DeliverersTable::selectAll() const
//{
//    return MilkModel::selectAll() + QString(" ORDER BY %1, %2")
//            .arg(fieldNameByPosition(DC::TD_LAST_NAME)).arg(fieldNameByPosition(DC::TD_FIRST_NAME));
//}


QVariant db::DeliverersModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return {};

    const auto deliverer = static_cast<const Deliverer*>(m_repository.get(index.row()));

    switch (role) {
    case static_cast<int>(DC::DeliverersRoles::MilkIdRole):
        return deliverer->milkId();
    case static_cast<int>(DC::DeliverersRoles::DM_FirstNameRole):
        return deliverer->firstName();
    case static_cast<int>(DC::DeliverersRoles::DM_LastNameRole):
        return deliverer->lastName();
    case static_cast<int>(DC::DeliverersRoles::DM_FullNameRole):
        return deliverer->fullName();
    case static_cast<int>(DC::DeliverersRoles::DM_InnRole):
        return deliverer->inn();
    case static_cast<int>(DC::DeliverersRoles::DM_LocalityIdRole):
        return deliverer->locality() ? deliverer->locality()->milkId() : TC::DEFAULT_ID;
    case static_cast<int>(DC::DeliverersRoles::DM_LocalityNameRole):
        return deliverer->locality() ? deliverer->locality()->name() : TC::Localities::DEF_NAME;
    case static_cast<int>(DC::DeliverersRoles::DM_AddressRole):
        return deliverer->address();
    case static_cast<int>(DC::DeliverersRoles::DM_PhoneNumberRole):
        return deliverer->phoneNumber();
    }

    return {};
}

bool db::DeliverersModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role == static_cast<int>(DC::DeliverersRoles::MilkIdRole) ||
            role == static_cast<int>(DC::DeliverersRoles::DM_FullNameRole) ||
            role == static_cast<int>(DC::DeliverersRoles::DM_LocalityNameRole))
        return false;

    auto &deliverer = static_cast<Deliverer&>(*m_repository.get(index.row()));

    bool isOk = false;
    switch (role) {
    case static_cast<int>(DC::DeliverersRoles::DM_FirstNameRole):
        isOk = m_dao->updateValue(DC::TD_FIRST_NAME, deliverer.milkId(), value.toString());
        if (isOk)
            deliverer.setFirstName(value.toString());
        break;
    case static_cast<int>(DC::DeliverersRoles::DM_LastNameRole):
        isOk = m_dao->updateValue(DC::TD_LAST_NAME, deliverer.milkId(), value.toString());
        if (isOk)
            deliverer.setLastName(value.toString());
        break;
    case static_cast<int>(DC::DeliverersRoles::DM_InnRole):
        isOk = m_dao->updateValue(DC::TD_INN, deliverer.milkId(), value.toString());
        if (isOk)
            deliverer.setInn(value.toString());
        break;
    case static_cast<int>(DC::DeliverersRoles::DM_LocalityIdRole):
        isOk = m_dao->updateValue(DC::TD_LOCALITY_ID, deliverer.milkId(), value.toInt());
        if (isOk)
            deliverer.setLocality(static_cast<const Locality*>(localities()->getItemById(value.toInt())));
        break;
    case static_cast<int>(DC::DeliverersRoles::DM_AddressRole):
        isOk = m_dao->updateValue(DC::TD_ADDRESS, deliverer.milkId(), value.toString());
        if (isOk)
            deliverer.setAddress(value.toString());
        break;
    case static_cast<int>(DC::DeliverersRoles::DM_PhoneNumberRole):
        isOk = m_dao->updateValue(DC::TD_PHONE_NUMBER, deliverer.milkId(), value.toString());
        if (isOk)
            deliverer.setPhoneNumber(value.toString());
        break;
    }

    if (isOk)
        emit dataChanged(index, index);

    return isOk;
}

QHash<int, QByteArray> db::DeliverersModel::roleNames() const
{
    return {
        {static_cast<int>(DC::DeliverersRoles::MilkIdRole), "milkId"},
        {static_cast<int>(DC::DeliverersRoles::DM_FirstNameRole), "firstName"},
        {static_cast<int>(DC::DeliverersRoles::DM_LastNameRole), "lastName"},
        {static_cast<int>(DC::DeliverersRoles::DM_FullNameRole), "fullName"},
        {static_cast<int>(DC::DeliverersRoles::DM_InnRole), "inn"},
        {static_cast<int>(DC::DeliverersRoles::DM_LocalityIdRole), "localityId"},
        {static_cast<int>(DC::DeliverersRoles::DM_AddressRole), "address"},
        {static_cast<int>(DC::DeliverersRoles::DM_PhoneNumberRole), "phoneNumber"},
    };
}

void DeliverersModel::copyItemValues(MilkBaseItem *left, const MilkBaseItem *right)
{
    auto itemSource = static_cast<Deliverer *>(left);
    auto item = static_cast<const Deliverer *>(right);
    itemSource->setFirstName(item->firstName());
    itemSource->setLastName(item->lastName());
    itemSource->setInn(item->inn());
    itemSource->setLocality(item->locality());
    itemSource->setAddress(item->address());
    itemSource->setPhoneNumber(item->phoneNumber());
}

void DeliverersModel::appendToRepository(const MilkBaseItem *item)
{
    m_repository.append<Deliverer>(item);
}

void db::DeliverersModel::refresh()
{
    emit beginRefresh();
    clear();

    const auto items = m_dao->get({}, QString("%1, %2")
                                  .arg(DC::TD_FN_LAST_NAME)
                                  .arg(DC::TD_FN_FIRST_NAME));
    for (const auto &item : *items)
    {
        const auto daoItem = static_cast<const DelivererData *>(item.get());
        const auto locality = static_cast<const Locality *>(m_localities->getItemById(daoItem->localityId()));
        Deliverer deliverer(daoItem->milkId(), daoItem->firstName(),  daoItem->lastName(),
                            daoItem->inn(), daoItem->address(), daoItem->phoneNumber(), locality);
        appendToRepository(&deliverer);
    }

    emit endRefresh();
}
