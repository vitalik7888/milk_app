#include "DeliverersTable.h"

#include "deliverersdao.h"
#include "tables/localities/LocalitiesTable.h"
#include "Utils.h"
// Qt
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

USE_DB_NAMESPACE

static const char *TABLE_NAME = "deliverers";
static const char *FN_ID = "id";
static const char *FN_NAME = "name";
static const char *FN_LOCALITY_ID = "locality_id";
static const char *FN_INN = "inn";
static const char *FN_ADDRESS = "address";
static const char *FN_PHONE_NUMBER = "phone_number";

//--------------------------------------------------------------------------------------------------
DeliverersDao::DeliverersDao(const QSqlDatabase &db):
    Dao(TABLE_NAME, FN_ID, db)
{  }

std::experimental::optional<DelivererData> DeliverersDao::getDeliverer(const milk_id delivererId) const
{
    QSqlQuery query;
    query.prepare(QString("%1 WHERE %2 = ?")
                  .arg(Utils::Main::getSelectStr(TABLE_NAME,
    { FN_NAME, FN_LOCALITY_ID, FN_INN, FN_ADDRESS, FN_PHONE_NUMBER })).arg(FN_ID));
    query.addBindValue(delivererId);

    if (query.exec() && query.first())
    {
        return DelivererData(
                    delivererId,
                    query.value(FN_NAME).toString(),
                    query.value(FN_LOCALITY_ID).toLongLong(),
                    query.value(FN_INN).toInt(),
                    query.value(FN_ADDRESS).toString(),
                    query.value(FN_PHONE_NUMBER).toString()
                    );
    } else
        qDebug() << QString("Отсутствует сдатчик с id = %1").arg(QString::number(delivererId));

    return {};
}

void DeliverersDao::insert(const DelivererData &deliverer) const
{
    QSqlQuery query;
    query.prepare(Utils::Main::getPrepInsertStr(TABLE_NAME,
    { FN_NAME, FN_LOCALITY_ID, FN_INN, FN_ADDRESS, FN_PHONE_NUMBER }));
    query.addBindValue(deliverer.name());
    query.addBindValue(deliverer.localityId());
    query.addBindValue(deliverer.inn());
    query.addBindValue(deliverer.address());
    query.addBindValue(deliverer.phoneNumber());

    if (!query.exec()) {
        const QString errDesc = query.lastError().text();
        qDebug() << errDesc;
        throw errDesc;
    }
}

void DeliverersDao::update(const DelivererData &deliverer) const
{
    QSqlQuery query;
    query.prepare(QString("%1 WHERE %2 = ?")
                  .arg(Utils::Main::getPrepUpdateStr(TABLE_NAME,
    { FN_NAME, FN_LOCALITY_ID, FN_INN, FN_ADDRESS, FN_PHONE_NUMBER })).arg(FN_ID));

    query.addBindValue(deliverer.name());
    query.addBindValue(deliverer.localityId());
    query.addBindValue(deliverer.inn());
    query.addBindValue(deliverer.address());
    query.addBindValue(deliverer.phoneNumber());
    query.addBindValue(deliverer.id());

    if (!query.exec()) {
        const QString errDesc = query.lastError().text();
        qDebug() << errDesc;
        throw errDesc;
    }
}

//--------------------------------------------------------------------------------------------------
DeliverersTable::DeliverersTable(QObject *parent):
    DeliverersTable(Q_NULLPTR, QSqlDatabase(), parent)
{

}

DeliverersTable::DeliverersTable(LocalitiesTable *localities, QSqlDatabase db, QObject *parent) :
    Table(new DeliverersDao(db), db, parent),
    m_localities(localities)
{
    setObjectName("DeliverersTable");
    qDebug() << "init " + objectName();

    setQuery(selectAll());
}

DeliverersTable::~DeliverersTable()
{

}

std::experimental::optional<DelivererData> DeliverersTable::getDelivererData(const milk_id delivererId) const
{
    const auto deliverer = dao()->getDeliverer(delivererId);
    if (!deliverer)
        emit error(QString("Отсутствует сдатчик с id = %1").arg(QString::number(delivererId)));

    return deliverer;
}

Deliverer *DeliverersTable::getDeliverer(const qlonglong delivererId)
{
    const auto delivererData = getDelivererData(delivererId);
    if (!delivererData)
        return Q_NULLPTR;

    const auto data = delivererData.value();
    auto locality = getLocalities()->getLocality(data.localityId());
    auto deliverer = new Deliverer(data.id(), data.name(), data.inn(), data.address(),
                                   data.phoneNumber(), locality, this);
    locality->setParent(deliverer);

    return deliverer;
}

void DeliverersTable::insert(int index, Deliverer *deliverer)
{
    if(index < 0 || index > rowCount()) {
        return;
    }

    emit beginInsertRows(QModelIndex(), index, index);
    dao()->insert(deliverer->data());
    emit endInsertRows();
}

void DeliverersTable::append(Deliverer *deliverer)
{
    insert(rowCount(), deliverer);
}

bool DeliverersTable::update(Deliverer *deliverer) const
{
    try {
        dao()->update(deliverer->data());
    } catch (const QString &err) {
        emit error(err);
        return false;
    }

    return true;
}

bool DeliverersTable::setName(const milk_id delivererId, const QString &_name) const
{
    try {
        m_dao->updateValue(FN_NAME, delivererId, _name);
        return true;
    } catch (const QString &err) {
        emit error(err);
        return false;
    }
}

bool DeliverersTable::setLocalityId(const milk_id delivererId, const milk_id localityId) const
{
    try {
        m_dao->updateValue(FN_LOCALITY_ID, delivererId, localityId);
        return true;
    } catch (const QString &err) {
        emit error(err);
        return false;
    }
}

bool DeliverersTable::setInn(const milk_id delivererId, const milk_inn inn) const
{
    try {
        m_dao->updateValue(FN_INN, delivererId, inn);
        return true;
    } catch (const QString &err) {
        emit error(err);
        return false;
    }
}

bool DeliverersTable::setAddress(const milk_id delivererId, const QString &address) const
{
    try {
        m_dao->updateValue(FN_ADDRESS, delivererId, address);
        return true;
    } catch (const QString &err) {
        emit error(err);
        return false;
    }
}

bool DeliverersTable::setPhoneNumber(const milk_id delivererId, const QString &phoneNumber) const
{
    try {
        m_dao->updateValue(FN_PHONE_NUMBER, delivererId, phoneNumber);
        return true;
    } catch (const QString &err) {
        emit error(err);
        return false;
    }
}

LocalitiesTable *DeliverersTable::getLocalities() const
{
    return m_localities;
}

QString DeliverersTable::tableName() const
{
    return TABLE_NAME;
}

QVariant DeliverersTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (section) {
    case DT_ID:
        return QVariant(tr("ID"));
    case DT_NAME:
        return QVariant(tr("ФИО"));
    case DT_LOCALITY_ID:
        return QVariant(tr("Населенный пункт"));
    case DT_INN:
        return QVariant(tr("ИНН"));
    case DT_ADDRESS:
        return QVariant(tr("Адрес"));
    case DT_PHONE_NUMBER:
        return QVariant(tr("Номер телефона"));
    }

    return Table::headerData(section, orientation, role);
}

QString DeliverersTable::primaryField() const
{
    return FN_ID;
}

DeliverersDao *DeliverersTable::dao() const
{
    return dynamic_cast<DeliverersDao *>(m_dao.data());
}

QString db::DeliverersTable::getColName(const int position, const bool withTableName) const
{
    QString columnName;
    switch (position) {
    case DeliverersTableColumns::DT_ID:
        columnName = FN_ID;
        break;
    case DeliverersTableColumns::DT_NAME:
        columnName = FN_NAME;
        break;
    case DeliverersTableColumns::DT_LOCALITY_ID:
        columnName = FN_LOCALITY_ID;
        break;
    case DeliverersTableColumns::DT_INN:
        columnName = FN_INN;
        break;
    case DeliverersTableColumns::DT_ADDRESS:
        columnName = FN_ADDRESS;
        break;
    case DeliverersTableColumns::DT_PHONE_NUMBER:
        columnName = FN_PHONE_NUMBER;
        break;
    default:
        columnName = "";
        break;
    }

    return withTableName ? QString("%1.%2").arg(TABLE_NAME).arg(columnName) : columnName;
}

int db::DeliverersTable::getColPosition(const QString &columnName) const
{
    if (columnName == FN_ID)
        return DeliverersTableColumns::DT_ID;
    if (columnName == FN_NAME)
        return DeliverersTableColumns::DT_NAME;
    if (columnName == FN_LOCALITY_ID)
        return DeliverersTableColumns::DT_LOCALITY_ID;
    if (columnName == FN_INN)
        return DeliverersTableColumns::DT_INN;
    if (columnName == FN_ADDRESS)
        return DeliverersTableColumns::DT_ADDRESS;
    if (columnName == FN_PHONE_NUMBER)
        return DeliverersTableColumns::DT_PHONE_NUMBER;
    return -1;
}
