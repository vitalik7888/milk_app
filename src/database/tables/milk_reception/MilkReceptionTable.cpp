#include "MilkReceptionTable.h"

#include "milkrecepriondao.h"
#include "tables/deliverers/DeliverersTable.h"
#include "tables/milk_points/MilkPointsTable.h"
#include "Constants.h"
#include "Utils.h"
// Qt
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

USE_DB_NAMESPACE

static const char *TABLE_NAME = "milk_reception";
static const char *FN_ID = "id";
static const char *FN_ID_DELIVERER = "id_deliverer";
static const char *FN_DELIVERER_NAME = "deliverer_name";
static const char *FN_MILK_POINT_ID = "milk_point_id";
static const char *FN_MILK_POINT_NAME = "milk_point_name";
static const char *FN_DELIVERY_DATE = "delivery_date";
static const char *FN_PRICE_LITER = "price_liter";
static const char *FN_LITERS = "liters";
static const char *FN_FAT = "fat";

//--------------------------------------------------------------------------------------------------
MilkReceptionDao::MilkReceptionDao(const QSqlDatabase &db) : Dao(TABLE_NAME, FN_ID, db) { }

MilkReceptionData MilkReceptionDao::get(const milk_id id) const
{
    QSqlQuery query;
    query.prepare(QString("%1 WHERE %2 = ?")
                  .arg(Utils::Main::getSelectStr(TABLE_NAME,
    { FN_ID_DELIVERER, FN_MILK_POINT_ID, FN_DELIVERY_DATE, FN_PRICE_LITER, FN_LITERS, FN_FAT }))
                  .arg(FN_ID));
    query.addBindValue(id);

    MilkReceptionData data;
    if (query.exec() && query.first())
    {
        data.setId(id);
        data.setDelivererId(query.value(0).toLongLong());
        data.setMilkPointId(query.value(1).toLongLong());
        data.setDeliveryDate(query.value(2).toDate());
        data.setPriceLiter(query.value(3).toFloat());
        data.setLiters(query.value(4).toFloat());
        data.setFat(query.value(5).toFloat());
    } else {
        const auto err = QString("Отсутствует сдача молока с id = %1").arg(id);
        qDebug() << err;
        throw err;
    }

    return data;
}

void MilkReceptionDao::insert(const MilkReceptionData &data) const
{
    QSqlQuery query;
    query.prepare(Utils::Main::getPrepInsertStr(TABLE_NAME,
        { FN_ID_DELIVERER, FN_MILK_POINT_ID, FN_DELIVERY_DATE, FN_PRICE_LITER, FN_LITERS, FN_FAT }));
    query.addBindValue(data.delivererId());
    query.addBindValue(data.milkPointId());
    query.addBindValue(data.deliveryDate().toString(Constants::defaultDateFormat()));
    query.addBindValue(data.priceLiter());
    query.addBindValue(data.liters());
    query.addBindValue(data.fat());

    if (!query.exec()) {
        const auto err = query.lastError().text();
        qDebug() << err;
        throw err;
    }
}

void MilkReceptionDao::update(const MilkReceptionData &data) const
{
    QSqlQuery query;
    query.prepare(QString("%1 WHERE %2 = ?").arg(Utils::Main::getPrepUpdateStr(TABLE_NAME,
        { FN_ID_DELIVERER, FN_MILK_POINT_ID, FN_DELIVERY_DATE, FN_PRICE_LITER, FN_LITERS, FN_FAT }))
                  .arg(FN_ID));
    query.addBindValue(data.milkPointId());
    query.addBindValue(data.deliveryDate());
    query.addBindValue(data.priceLiter());
    query.addBindValue(data.liters());
    query.addBindValue(data.fat());
    query.addBindValue(data.delivererId());

    if (!query.exec()) {
        const auto err = query.lastError().text();
        qDebug() << err;
        throw err;
    }
}

//--------------------------------------------------------------------------------------------------
MilkReceptionTable::MilkReceptionTable(DeliverersTable *_deliverers, MilkPointsTable *milkPoints,
                                       QSqlDatabase db):
    Table(new MilkReceptionDao(db), _deliverers, db),
    m_deliverers(_deliverers),
    m_milkPoints(milkPoints)
{
    setObjectName("MilkReceptionTable");
    qDebug() << "init " + objectName();

    initColumns();
    setQuery(selectAll());
}

MilkReceptionTable::~MilkReceptionTable()
{
    qDebug() << "delete " + objectName();
}

QString MilkReceptionTable::tableName() const
{
    return TABLE_NAME;
}

QSqlField MilkReceptionTable::getFieldId() const
{
    return getColumnByName(FN_ID);
}

QSqlField MilkReceptionTable::getFieldIdDeliverer() const
{
    return getColumnByName(FN_ID_DELIVERER);
}

QSqlField MilkReceptionTable::getFieldMilkPointId() const
{
    return getColumnByName(FN_MILK_POINT_ID);
}

QSqlField MilkReceptionTable::getFieldDeliveryDate() const
{
    return getColumnByName(FN_DELIVERY_DATE);
}

QSqlField MilkReceptionTable::getFieldPriceLiter() const
{
    return getColumnByName(FN_PRICE_LITER);
}

QSqlField MilkReceptionTable::getFieldLiters() const
{
    return getColumnByName(FN_LITERS);
}

QSqlField MilkReceptionTable::getFieldFat() const
{
    return getColumnByName(FN_FAT);
}

MilkReceptionData MilkReceptionTable::getMilkReception(const milk_id milkReceptionId) const
{
    return dao()->get(milkReceptionId);
}

void MilkReceptionTable::insert(const MilkReceptionData &milkReception) const
{
    dao()->insert(milkReception);
}

void MilkReceptionTable::update(const MilkReceptionData &milkReception) const
{
    dao()->update(milkReception);
}

bool MilkReceptionTable::setIdDeliverer(const milk_id milkReceptionId, const milk_id delivererId) const
{
    return updateValue(getColumnPosition(FN_ID), milkReceptionId, delivererId);
}

bool MilkReceptionTable::setIdMilkPoint(const milk_id milkReceptionId, const milk_id milkPointId) const
{
    return updateValue(getColumnPosition(FN_MILK_POINT_ID), milkReceptionId, milkPointId);
}

bool MilkReceptionTable::setDeliveryDate(const milk_id milkReceptionId, const QDate &deliveryDate) const
{
    return updateValue(getColumnPosition(FN_DELIVERY_DATE), milkReceptionId, deliveryDate);
}

bool MilkReceptionTable::setPriceLiter(const milk_id milkReceptionId, const float priceLiter) const
{
    return updateValue(getColumnPosition(FN_PRICE_LITER), milkReceptionId, priceLiter);
}

bool MilkReceptionTable::setLiters(const milk_id milkReceptionId, const float liters) const
{
    return updateValue(getColumnPosition(FN_LITERS), milkReceptionId, liters);
}

bool MilkReceptionTable::setFat(const milk_id milkReceptionId, const float fat) const
{
    return updateValue(getColumnPosition(FN_FAT), milkReceptionId, fat);
}

bool MilkReceptionTable::updatePriceLiters(const double price, const QDate &dateFrom, const QDate &dateTo) const
{
    QSqlQuery query;
    query.prepare(QString("UPDATE %1 SET %2 = ? WHERE %3 BETWEEN ? AND ?")
                  .arg(tableName())
                  .arg(getColumnById(getColumnPosition(FN_PRICE_LITER)).name())
                  .arg(getColumnById(getColumnPosition(FN_DELIVERY_DATE)).name()));
    query.addBindValue(price);
    query.addBindValue(dateFrom.toString(Constants::defaultDateFormat()));
    query.addBindValue(dateTo.toString(Constants::defaultDateFormat()));

    if (!query.exec()) {
        emit error(query.lastError().text());
        return false;
    }
    return true;
}

QSqlField MilkReceptionTable::primaryField() const
{
    return getColumnByName(FN_ID);
}

QString MilkReceptionTable::selectAll() const
{
    const auto select = Utils::Main::getSelectStr(
                tableName(),
                QStringList()
                << getNameColumnId(true)
                << getNameColumnIdDeliverer(true)
                << m_deliverers->getNameColumnName(true) + " AS " + FN_DELIVERER_NAME
                << getNameColumnMilkPointId(true)
                << m_milkPoints->getNameColumnName(true) + " AS " + FN_MILK_POINT_NAME
                << getNameColumnDeliveryDate(true)
                << getNameColumnPriceLiter(true)
                << getNameColumnLiters(true)
                << getNameColumnFat(true));

    const auto join = QString("LEFT JOIN %2 ON %3 = %4 LEFT JOIN %5 ON %6 = %7")
            .arg(m_deliverers->tableName())
            .arg(getNameColumnIdDeliverer(true))
            .arg(m_deliverers->getNameColumnId(true))
            .arg(m_milkPoints->tableName())
            .arg(getNameColumnMilkPointId(true))
            .arg(m_milkPoints->getNameColumnId(true));
    return select + " " + join;
}

QString MilkReceptionTable::getNameColumnId(const bool withTableName) const
{
    if (!withTableName)
        return FN_ID;
    return QString(tableName() + "." + FN_ID);
}

QString MilkReceptionTable::getNameColumnIdDeliverer(const bool withTableName) const
{
    if (!withTableName)
        return FN_ID_DELIVERER;
    return QString(tableName() + "." + FN_ID_DELIVERER);
}

QString MilkReceptionTable::getNameColumnDelivererName(const bool withTableName) const
{
    if (!withTableName)
        return FN_DELIVERER_NAME;
    return QString(tableName() + "." + FN_DELIVERER_NAME);
}

QString MilkReceptionTable::getNameColumnMilkPointId(const bool withTableName) const
{
    if (!withTableName)
        return FN_MILK_POINT_ID;
    return QString(tableName() + "." + FN_MILK_POINT_ID);
}

QString MilkReceptionTable::getNameColumnMilkPointName(const bool withTableName) const
{
    if (!withTableName)
        return FN_MILK_POINT_NAME;
    return QString(tableName() + "." + FN_MILK_POINT_NAME);
}

QString MilkReceptionTable::getNameColumnDeliveryDate(const bool withTableName) const
{
    if (!withTableName)
        return FN_DELIVERY_DATE;
    return QString(tableName() + "." + FN_DELIVERY_DATE);
}

QString MilkReceptionTable::getNameColumnPriceLiter(const bool withTableName) const
{
    if (!withTableName)
        return FN_PRICE_LITER;
    return QString(tableName() + "." + FN_PRICE_LITER);
}

QString MilkReceptionTable::getNameColumnLiters(const bool withTableName) const
{
    if (!withTableName)
        return FN_LITERS;
    return QString(tableName() + "." + FN_LITERS);
}

QString MilkReceptionTable::getNameColumnFat(const bool withTableName) const
{
    if (!withTableName)
        return FN_FAT;
    return QString(tableName() + "." + FN_FAT);
}

QVariant MilkReceptionTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    return Table::headerData(section, orientation, role);
}

void MilkReceptionTable::initColumns()
{
    m_columns.append(QSqlField(FN_ID, QVariant::LongLong));
    m_columns.append(QSqlField(FN_ID_DELIVERER, QVariant::LongLong));
    m_columns.append(QSqlField(FN_DELIVERER_NAME, QVariant::String));
    m_columns.append(QSqlField(FN_MILK_POINT_ID, QVariant::Date));
    m_columns.append(QSqlField(FN_MILK_POINT_NAME, QVariant::String));
    m_columns.append(QSqlField(FN_DELIVERY_DATE, QVariant::Double));
    m_columns.append(QSqlField(FN_PRICE_LITER, QVariant::Double));
    m_columns.append(QSqlField(FN_LITERS, QVariant::Double));
    m_columns.append(QSqlField(FN_FAT, QVariant::Double));
}

MilkReceptionDao *MilkReceptionTable::dao() const
{
    return dynamic_cast<MilkReceptionDao *>(m_dao.data());
}

DeliverersTable *MilkReceptionTable::getDeliverers() const
{
    return m_deliverers;
}

MilkPointsTable *MilkReceptionTable::getMilkPoints() const
{
    return m_milkPoints;
}

QList<float> MilkReceptionTable::getMinMaxPriceLiter(const QDate &min, QDate max) const
{
    if (!max.isValid())
        max = min;

    QList<float> minMax;

    QSqlQuery query;
    query.prepare(QString("SELECT MIN(%1), MAX(%1) FROM %2 WHERE %3 BETWEEN '%4' AND '%5'")
                  .arg(getNameColumnPriceLiter(true))
                  .arg(tableName())
                  .arg(getNameColumnDeliveryDate(true))
                  .arg(min.toString(Constants::defaultDateFormat()))
                  .arg(max.toString(Constants::defaultDateFormat())));

    if (query.exec() && query.first()) {
        minMax.append(query.value(0).toFloat());
        minMax.append(query.value(1).toFloat());
    }

    return minMax;
}

QDate MilkReceptionTable::getMinDeliveryDate() const
{
    QSqlQuery query;
    query.prepare(QString("SELECT MIN(%1) FROM %2")
                  .arg(getNameColumnDeliveryDate(true))
                  .arg(tableName())) ;

    if (query.exec() && query.first())
        return query.value(0).toDate();

    return QDate();
}

QDate MilkReceptionTable::getMaxDeliveryDate() const
{
    QSqlQuery query;
    query.prepare(QString("SELECT MAX(%1) FROM %2")
                  .arg(getNameColumnDeliveryDate(true))
                  .arg(tableName())) ;

    if (query.exec() && query.first())
        return query.value(0).toDate();

    return QDate();
}
