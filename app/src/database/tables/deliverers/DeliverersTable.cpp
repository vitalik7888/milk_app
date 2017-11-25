#include "DeliverersTable.h"

#include "DeliverersDao.h"
#include "tables/localities/LocalitiesTable.h"
#include "DbUtils.h"
// Qt
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

USE_DB_NAMESPACE
using DC = DbConstants;
using DCD = DC::Deliverers;
using DCL = DC::Localities;


DeliverersDao::DeliverersDao(DeliverersTable *table):
    Dao(table)
{

}

bool DeliverersDao::insert(const QVariant &data) const
{
    Q_ASSERT(data.canConvert<DelivererData>());
    const auto deliverer = data.value<DelivererData>();

    QSqlQuery query;
    query.prepare(DbUtils::getPrepInsertStr(DCD::TABLE_NAME,
    { DCD::FN_NAME, DCD::FN_LOCALITY_ID, DCD::FN_INN, DCD::FN_ADDRESS, DCD::FN_PHONE_NUMBER }));
    query.addBindValue(deliverer.name());
    query.addBindValue(deliverer.localityId());
    query.addBindValue(deliverer.inn());
    query.addBindValue(deliverer.address());
    query.addBindValue(deliverer.phoneNumber());

    if (!query.exec()) {
        _error(query.lastError().text());
        return false;
    }

    return true;
}

bool DeliverersDao::update(const QVariant &data) const
{
    Q_ASSERT(data.canConvert<DelivererData>());
    const auto deliverer = data.value<DelivererData>();

    QSqlQuery query;
    query.prepare(QString("%1 WHERE %2 = ?")
                  .arg(DbUtils::getPrepUpdateStr(DCD::TABLE_NAME,
    { DCD::FN_NAME, DCD::FN_LOCALITY_ID, DCD::FN_INN, DCD::FN_ADDRESS, DCD::FN_PHONE_NUMBER })).arg(DCD::FN_ID));

    query.addBindValue(deliverer.name());
    query.addBindValue(deliverer.localityId());
    query.addBindValue(deliverer.inn());
    query.addBindValue(deliverer.address());
    query.addBindValue(deliverer.phoneNumber());
    query.addBindValue(deliverer.id());

    if (!query.exec()) {
        _error(query.lastError().text());
        return false;
    }

    return true;
}

//--------------------------------------------------------------------------------------------------
DeliverersTable::DeliverersTable(QObject *parent):
    DeliverersTable(Q_NULLPTR, QSqlDatabase(), parent)
{

}

DeliverersTable::DeliverersTable(LocalitiesTable *localities, QSqlDatabase db, QObject *parent) :
    Table(new DeliverersDao(this), db, parent),
    m_localities(localities)
{
    setObjectName("DeliverersTable");

    setQuery(selectAll());
}

DeliverersTable::~DeliverersTable()
{

}

std::experimental::optional<DelivererData> DeliverersTable::getDelivererData(const DbConstants::milk_id delivererId) const
{
    const auto deliverer = dao()->get(delivererId);
    if (!deliverer.isNull())
        return fromRecord(deliverer.value<QSqlRecord>());

    return {};
}

QList<DelivererData> DeliverersTable::getDeliverersData(const QString &where) const
{
    const auto data = dao()->getAll(where).value< QList<QSqlRecord> >();

    QList<DelivererData> deliverers;
    for (const auto &record : data)
        deliverers.append(fromRecord(record));

    return deliverers;
}

Deliverer *DeliverersTable::getDeliverer(const qlonglong delivererId)
{
    const auto delivererData = getDelivererData(delivererId);
    if (!delivererData)
        return Q_NULLPTR;

    const auto data = delivererData.value();
    auto locality = localities()->getLocality(data.localityId());
    auto deliverer = new Deliverer(data.id(), data.name(), data.inn(), data.address(),
                                   data.phoneNumber(), locality, this);
    locality->setParent(deliverer);

    return deliverer;
}

bool DeliverersTable::insert(int index, Deliverer *deliverer)
{
    if(index < 0 || index > rowCount()) {
        emit error("Данная позиция не входит в диапазон");
        return false;
    }

    emit beginInsertRows(QModelIndex(), index, index);
    const bool isOk = dao()->insert(QVariant::fromValue(deliverer->data()));
    emit endInsertRows();

    return isOk;
}

bool DeliverersTable::append(Deliverer *deliverer)
{
    return insert(rowCount(), deliverer);
}

bool DeliverersTable::update(Deliverer *deliverer) const
{
    return dao()->update(QVariant::fromValue(deliverer->data()));
}

bool DeliverersTable::setName(const DbConstants::milk_id delivererId, const QString &_name) const
{
    return m_dao->updateValue(DCD::FN_NAME, delivererId, _name);
}

bool DeliverersTable::setLocalityId(const DbConstants::milk_id delivererId, const DbConstants::milk_id localityId) const
{
    return m_dao->updateValue(DCD::FN_LOCALITY_ID, delivererId, localityId);
}

bool DeliverersTable::setInn(const DbConstants::milk_id delivererId, const DbConstants::milk_inn inn) const
{
    return m_dao->updateValue(DCD::FN_INN, delivererId, inn);
}

bool DeliverersTable::setAddress(const DbConstants::milk_id delivererId, const QString &address) const
{
    return m_dao->updateValue(DCD::FN_ADDRESS, delivererId, address);
}

bool DeliverersTable::setPhoneNumber(const DbConstants::milk_id delivererId, const QString &phoneNumber) const
{
    return m_dao->updateValue(DCD::FN_PHONE_NUMBER, delivererId, phoneNumber);
}

LocalitiesTable *DeliverersTable::localities() const
{
    return m_localities;
}

QString DeliverersTable::tableName() const
{
    return DCD::TABLE_NAME;
}

QVariant DeliverersTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (section) {
    case DCD::DT_ID:
        return QVariant(tr("ID"));
    case DCD::DT_NAME:
        return QVariant(tr("ФИО"));
    case DCD::DT_LOCALITY_ID:
        return QVariant(tr("Населенный пункт"));
    case DCD::DT_INN:
        return QVariant(tr("ИНН"));
    case DCD::DT_ADDRESS:
        return QVariant(tr("Адрес"));
    case DCD::DT_PHONE_NUMBER:
        return QVariant(tr("Номер телефона"));
    }

    return Table::headerData(section, orientation, role);
}

QString DeliverersTable::primaryField() const
{
    return DCD::FN_ID;
}

DeliverersDao *DeliverersTable::dao() const
{
    return dynamic_cast<DeliverersDao *>(m_dao.data());
}

DelivererData DeliverersTable::fromRecord(const QSqlRecord &record)
{
    return {
        record.value(DCD::FN_ID).toInt(),
                record.value(DCD::FN_NAME).toString(),
                record.value(DCD::FN_LOCALITY_ID).toInt(),
                record.value(DCD::FN_INN).toLongLong(),
                record.value(DCD::FN_ADDRESS).toString(),
                record.value(DCD::FN_PHONE_NUMBER).toString(),
    };
}

QString db::DeliverersTable::getColName(const int position, const bool withTableName) const
{
    QString columnName;
    switch (position) {
    case DCD::DT_ID:
        columnName = DCD::FN_ID;
        break;
    case DCD::DT_NAME:
        columnName = DCD::FN_NAME;
        break;
    case DCD::DT_LOCALITY_ID:
        columnName = DCD::FN_LOCALITY_ID;
        break;
    case DCD::DT_INN:
        columnName = DCD::FN_INN;
        break;
    case DCD::DT_ADDRESS:
        columnName = DCD::FN_ADDRESS;
        break;
    case DCD::DT_PHONE_NUMBER:
        columnName = DCD::FN_PHONE_NUMBER;
        break;
    default:
        columnName = "";
        break;
    }

    return withTableName ? QString("%1.%2").arg(DCD::TABLE_NAME).arg(columnName) : columnName;
}

int db::DeliverersTable::getColPosition(const QString &columnName) const
{
    if (columnName == DCD::FN_ID)
        return DCD::DT_ID;
    if (columnName == DCD::FN_NAME)
        return DCD::DT_NAME;
    if (columnName == DCD::FN_LOCALITY_ID)
        return DCD::DT_LOCALITY_ID;
    if (columnName == DCD::FN_INN)
        return DCD::DT_INN;
    if (columnName == DCD::FN_ADDRESS)
        return DCD::DT_ADDRESS;
    if (columnName == DCD::FN_PHONE_NUMBER)
        return DCD::DT_PHONE_NUMBER;
    return -1;
}
