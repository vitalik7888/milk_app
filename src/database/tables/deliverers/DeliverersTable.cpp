#include "DeliverersTable.h"

#include "tables/localities/LocalitiesTable.h"
#include "Utils.h"
// qt
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

USE_DB_NAMESPACE

//#include <cstdarg>

static const char *FN_ID = "id";
static const char *FN_NAME = "name";
static const char *FN_LOCALITY_ID = "locality_id";
static const char *FN_INN = "inn";
static const char *FN_ADDRESS = "address";
static const char *FN_PHONE_NUMBER = "phone_number";


DeliverersTable::DeliverersTable(LocalitiesTable *parent, QSqlDatabase db) :
    Table(parent, db),
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

QSqlField DeliverersTable::getFieldId() const
{
    return getColumnByName(FN_ID);
}

QSqlField DeliverersTable::getFieldName() const
{
    return getColumnByName(FN_NAME);
}

QSqlField DeliverersTable::getFieldLocalityId() const
{
    return getColumnByName(FN_LOCALITY_ID);
}

QSqlField DeliverersTable::getFieldInn() const
{
    return getColumnByName(FN_INN);
}

QSqlField DeliverersTable::getFieldAddress() const
{
    return getColumnByName(FN_ADDRESS);
}

QSqlField DeliverersTable::getFieldPhoneNumber() const
{
    return getColumnByName(FN_PHONE_NUMBER);
}

DelivererData DeliverersTable::getDeliverer(const milk_id delivererId) const
{
    QSqlQuery query;
    query.prepare(QString("%1 WHERE %2 = ?")
                    .arg(Utils::Main::getSelectStr(tableName(), QStringList()
                                       << getNameColumnName(true)
                                       << getNameColumnLocalityId(true)
                                       << getNameColumnInn(true)
                                       << getNameColumnAddress(true)
                                       << getNameColumnPhoneNumber(true)))
                    .arg(getNameColumnId(true)));
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
    } else
        emit error(tr("Отсутствует сдатчик с id = ") + QString::number(delivererId));

    return deliverer;
}

bool DeliverersTable::insert(const DelivererData &deliverer)
{
    QSqlQuery query;
    query.prepare(Utils::Main::getPrepInsertStr(tableName(), QStringList()
                                   << getNameColumnName()
                                   << getNameColumnLocalityId()
                                   << getNameColumnInn()
                                   << getNameColumnAddress()
                                   << getNameColumnPhoneNumber()));
    query.addBindValue(deliverer.name());
    query.addBindValue(deliverer.localityId());
    query.addBindValue(deliverer.inn());
    query.addBindValue(deliverer.address());
    query.addBindValue(deliverer.phoneNumber());

    if (!query.exec()) {
        qDebug() << query.lastQuery();
        emit error(query.lastError().text());
        return false;
    }

    return true;
}

bool DeliverersTable::update(const DelivererData &deliverer)
{
    QSqlQuery query;
    query.prepare(QString("%1 WHERE %2 = ?")
                  .arg(Utils::Main::getPrepUpdateStr(tableName(), QStringList()
                                   << getNameColumnName()
                                   << getNameColumnLocalityId()
                                   << getNameColumnInn()
                                   << getNameColumnAddress()
                                   << getNameColumnPhoneNumber()))
                  .arg(getNameColumnId()));

    query.addBindValue(deliverer.name());
    query.addBindValue(deliverer.localityId());
    query.addBindValue(deliverer.inn());
    query.addBindValue(deliverer.address());
    query.addBindValue(deliverer.phoneNumber());
    query.addBindValue(deliverer.id());

    if (!query.exec()) {
        emit error(query.lastError().text());
        return false;
    }
    return true;
}

bool DeliverersTable::setName(const milk_id delivererId, const QString &_name) const
{
    return updateValue(getNameColumnId(true), delivererId, _name);
}

bool DeliverersTable::setLocalityId(const milk_id delivererId, const milk_id localityId) const
{
    return updateValue(getNameColumnLocalityId(true), delivererId, localityId);
}

bool DeliverersTable::setInn(const milk_id delivererId, const milk_inn inn) const
{
    return updateValue(getNameColumnInn(true), delivererId, inn);
}

bool DeliverersTable::setAddress(const milk_id delivererId, const QString &address) const
{
    return updateValue(getNameColumnAddress(true), delivererId, address);
}

bool DeliverersTable::setPhoneNumber(const milk_id delivererId, const QString &phoneNumber) const
{
    return updateValue(getNameColumnPhoneNumber(true), delivererId, phoneNumber);
}

LocalitiesTable *DeliverersTable::getLocalities() const
{
    return m_localities;
}

QString DeliverersTable::tableName() const
{
    return "deliverers";
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

QString DeliverersTable::getNameColumnId(const bool withTableName) const
{
    if (!withTableName)
        return FN_ID;
    return QString(tableName() + "." + FN_ID);
}

QString DeliverersTable::getNameColumnName(const bool withTableName) const
{
    if (!withTableName)
        return FN_NAME;
    return QString(tableName() + "." + FN_NAME);
}

QString DeliverersTable::getNameColumnLocalityId(const bool withTableName) const
{
    if (!withTableName)
        return FN_LOCALITY_ID;
    return QString(tableName() + "." + FN_LOCALITY_ID);
}

QString DeliverersTable::getNameColumnInn(const bool withTableName) const
{
    if (!withTableName)
        return FN_INN;
    return QString(tableName() + "." + FN_INN);
}

QString DeliverersTable::getNameColumnAddress(const bool withTableName) const
{
    if (!withTableName)
        return FN_ADDRESS;
    return QString(tableName() + "." + FN_ADDRESS);
}

QString DeliverersTable::getNameColumnPhoneNumber(const bool withTableName) const
{
    if (!withTableName)
        return FN_PHONE_NUMBER;
    return QString(tableName() + "." + FN_PHONE_NUMBER);
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
