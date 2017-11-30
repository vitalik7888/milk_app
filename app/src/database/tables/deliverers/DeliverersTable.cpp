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


DeliverersDao::DeliverersDao(DeliverersTable *table):
    Dao(table)
{

}

bool DeliverersDao::insert(const QVariant &data) const
{
    Q_ASSERT(data.canConvert<DelivererData>());
    const auto deliverer = data.value<DelivererData>();

    QSqlQuery query;
    query.prepare(DbUtils::getPrepInsertStr(DC::TD_TABLE_NAME,
    { DC::TD_FN_NAME, DC::TD_FN_LOCALITY_ID, DC::TD_FN_INN, DC::TD_FN_ADDRESS, DC::TD_FN_PHONE_NUMBER }));
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
                  .arg(DbUtils::getPrepUpdateStr(DC::TD_TABLE_NAME,
    { DC::TD_FN_NAME, DC::TD_FN_LOCALITY_ID, DC::TD_FN_INN, DC::TD_FN_ADDRESS, DC::TD_FN_PHONE_NUMBER })).arg(DC::TD_FN_ID));

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

std::experimental::optional<DelivererData> DeliverersTable::getDelivererData(const int delivererId) const
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

Deliverer *DeliverersTable::getDeliverer(const int delivererId)
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
    return Table::insert(index, QVariant::fromValue(deliverer->data()));
}

bool DeliverersTable::append(Deliverer *deliverer)
{
    return Table::append(QVariant::fromValue(deliverer->data()));
}

bool DeliverersTable::set(const int row, Deliverer *deliverer)
{
    return Table::set(row, QVariant::fromValue(deliverer->data()));
}

LocalitiesTable *DeliverersTable::localities() const
{
    return m_localities;
}

QString DeliverersTable::tableName() const
{
    return DC::TD_TABLE_NAME;
}

QVariant DeliverersTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (section) {
    case DC::TD_ID:
        return QVariant(tr("ID"));
    case DC::TD_NAME:
        return QVariant(tr("ФИО"));
    case DC::TD_LOCALITY_ID:
        return QVariant(tr("Населенный пункт"));
    case DC::TD_INN:
        return QVariant(tr("ИНН"));
    case DC::TD_ADDRESS:
        return QVariant(tr("Адрес"));
    case DC::TD_PHONE_NUMBER:
        return QVariant(tr("Номер телефона"));
    }

    return Table::headerData(section, orientation, role);
}

QString DeliverersTable::primaryField() const
{
    return DC::TD_FN_ID;
}

DeliverersDao *DeliverersTable::dao() const
{
    return dynamic_cast<DeliverersDao *>(m_dao.data());
}

DelivererData DeliverersTable::fromRecord(const QSqlRecord &record)
{
    return {
        record.value(DC::TD_FN_ID).toInt(),
                record.value(DC::TD_FN_NAME).toString(),
                record.value(DC::TD_FN_LOCALITY_ID).toInt(),
                record.value(DC::TD_FN_INN).toString(),
                record.value(DC::TD_FN_ADDRESS).toString(),
                record.value(DC::TD_FN_PHONE_NUMBER).toString(),
    };
}

QString db::DeliverersTable::getColName(const int position, const bool withTableName) const
{
    QString columnName;
    switch (position) {
    case DC::TD_ID:
        columnName = DC::TD_FN_ID;
        break;
    case DC::TD_NAME:
        columnName = DC::TD_FN_NAME;
        break;
    case DC::TD_LOCALITY_ID:
        columnName = DC::TD_FN_LOCALITY_ID;
        break;
    case DC::TD_INN:
        columnName = DC::TD_FN_INN;
        break;
    case DC::TD_ADDRESS:
        columnName = DC::TD_FN_ADDRESS;
        break;
    case DC::TD_PHONE_NUMBER:
        columnName = DC::TD_FN_PHONE_NUMBER;
        break;
    default:
        columnName = "";
        break;
    }

    return withTableName ? QString("%1.%2").arg(DC::TD_TABLE_NAME).arg(columnName) : columnName;
}

int db::DeliverersTable::getColPosition(const QString &columnName) const
{
    if (columnName == DC::TD_FN_ID)
        return DC::TD_ID;
    if (columnName == DC::TD_FN_NAME)
        return DC::TD_NAME;
    if (columnName == DC::TD_FN_LOCALITY_ID)
        return DC::TD_LOCALITY_ID;
    if (columnName == DC::TD_FN_INN)
        return DC::TD_INN;
    if (columnName == DC::TD_FN_ADDRESS)
        return DC::TD_ADDRESS;
    if (columnName == DC::TD_FN_PHONE_NUMBER)
        return DC::TD_PHONE_NUMBER;
    return -1;
}


QVariant db::DeliverersTable::get(const int row)
{
    const auto _id = getIdByRow(row);
    if (_id < 0)
        return {};

    auto locality = localities()->getLocality(data(index(row, DC::TD_LOCALITY_ID)).toInt());
    return QVariant::fromValue(new Deliverer(
                                   _id,
                                   data(index(row, DC::TD_NAME)).toString(),
                                   data(index(row, DC::TD_INN)).toString(),
                                   data(index(row, DC::TD_ADDRESS)).toString(),
                                   data(index(row, DC::TD_PHONE_NUMBER)).toString(),
                                   locality,
                                   this));
}
