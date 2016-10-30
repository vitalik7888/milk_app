#include "DeliverersTable.h"

#include "deliverersdao.h"
#include "tables/localities/LocalitiesTable.h"
#include "Utils.h"
// Qt
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

USE_DB_NAMESPACE

//#include <cstdarg>

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

DelivererData DeliverersDao::getDeliverer(const milk_id delivererId) const
{
    QSqlQuery query;
    query.prepare(QString("%1 WHERE %2 = ?")
                  .arg(Utils::Main::getSelectStr(TABLE_NAME,
    { FN_NAME, FN_LOCALITY_ID, FN_INN, FN_ADDRESS, FN_PHONE_NUMBER })).arg(FN_ID));
    query.addBindValue(delivererId);

    DelivererData deliverer;
    if (query.exec() && query.first())
    {
        deliverer.setName(query.value(0).toString());
        deliverer.setLocalityId(query.value(1).toLongLong());
        deliverer.setInn(query.value(2).toInt());
        deliverer.setAddress(query.value(3).toString());
        deliverer.setPhoneNumber(query.value(4).toString());
        deliverer.setId(delivererId);
    } else {
        const auto errorDesc = QString("Отсутствует сдатчик с id = %1").arg(QString::number(delivererId));
        qDebug() << errorDesc;
        throw errorDesc;
    }

    return deliverer;

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
DeliverersTable::DeliverersTable(LocalitiesTable *parent, QSqlDatabase db) :
    Table(new DeliverersDao(db), parent, db),
    m_localities(parent)
{
    setObjectName("DeliverersTable");
    qDebug() << "init " + objectName();

    initColumns();
    setQuery(selectAll());
}

DeliverersTable::~DeliverersTable()
{

}

DelivererData DeliverersTable::getDeliverer(const milk_id delivererId) const
{
    DelivererData data;
    try {
        data = dao()->getDeliverer(delivererId);
    } catch (const QString &err) {
        emit error(err);
    }
    return data;
}

bool DeliverersTable::insert(const DelivererData &deliverer)
{
    try {
        dao()->insert(deliverer);
    } catch (const QString &err) {
        emit error(err);
        return false;
    }

    return true;
}

bool DeliverersTable::update(const DelivererData &deliverer)
{
    try {
        dao()->update(deliverer);
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
    if (section == getColumnPosition(FN_ID)) {
        return QVariant(tr("ID"));
    } else if (section == getColumnPosition(FN_NAME)) {
        return QVariant(tr("ФИО"));
    } /*else if (section == getColumnPosition(FN_LOCALITY_ID)) {
        return QVariant(tr("Населенный пункт"));
    }*/ else if (section == getColumnPosition(FN_INN)) {
        return QVariant(tr("ИНН"));
    } else if (section == getColumnPosition(FN_ADDRESS)) {
        return QVariant(tr("Адрес"));
    } else if (section == getColumnPosition(FN_PHONE_NUMBER)) {
        return QVariant(tr("Номер телефона"));
    }

    return Table::headerData(section, orientation, role);
}


QSqlField DeliverersTable::primaryField() const
{
    return getColumnByName(FN_ID);
}

void DeliverersTable::initColumns()
{
    m_columns.append(QSqlField(FN_ID, QVariant::LongLong));
    m_columns.append(QSqlField(FN_NAME, QVariant::String));
    m_columns.append(QSqlField(FN_LOCALITY_ID, QVariant::LongLong));
    m_columns.append(QSqlField(FN_INN, QVariant::LongLong));
    m_columns.append(QSqlField(FN_ADDRESS, QVariant::String));
    m_columns.append(QSqlField(FN_PHONE_NUMBER, QVariant::String));
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
    case DeliverersTableColumns::DT_PHONE_NUMBER:
        columnName = FN_PHONE_NUMBER;
        break;
    default:
        columnName = "";
        break;
    }

    return withTableName ? QString("%1.%2").arg(TABLE_NAME).arg(columnName) : columnName;
}
