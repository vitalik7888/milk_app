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
    QSqlQuery query(m_db);
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
        data.setPriceLiter(query.value(3).toDouble());
        data.setLiters(query.value(4).toDouble());
        data.setFat(query.value(5).toDouble());
    } else {
        const auto err = QString("Отсутствует сдача молока с id = %1").arg(id);
        qDebug() << err;
        throw err;
    }

    return data;
}

QList<MilkReceptionData> MilkReceptionDao::get(const QString &where) const
{
    QSqlQuery query(m_db);
    query.prepare(QString("%1%2")
                  .arg(Utils::Main::getSelectStr(TABLE_NAME,
    { FN_ID, FN_ID_DELIVERER, FN_MILK_POINT_ID, FN_DELIVERY_DATE, FN_PRICE_LITER, FN_LITERS, FN_FAT }))
                  .arg(where.isEmpty() ? QString() : " WHERE " + where));

    QList<MilkReceptionData> mrd;
    if (query.exec())
    {
        while (query.next()) {
            MilkReceptionData data;
            data.setId(query.value(0).toLongLong());
            data.setDelivererId(query.value(1).toLongLong());
            data.setMilkPointId(query.value(2).toLongLong());
            data.setDeliveryDate(query.value(3).toDate());
            data.setPriceLiter(query.value(4).toDouble());
            data.setLiters(query.value(5).toDouble());
            data.setFat(query.value(6).toDouble());

            mrd.append(data);
        }
    } else {
        const auto err = query.lastError().text();
        qDebug() << err;
        throw err;
    }

    return mrd;
}

void MilkReceptionDao::insert(const MilkReceptionData &data) const
{
    QSqlQuery query(m_db);
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
    QSqlQuery query(m_db);
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
MilkReceptionTable::MilkReceptionTable(QObject *parent):
    MilkReceptionTable(Q_NULLPTR, Q_NULLPTR, QSqlDatabase(), parent)
{

}

MilkReceptionTable::MilkReceptionTable(DeliverersTable *_deliverers, MilkPointsTable *milkPoints,
                                       QSqlDatabase db, QObject *parent):
    Table(new MilkReceptionDao(db), db, parent),
    m_deliverers(_deliverers),
    m_milkPoints(milkPoints)
{
    setObjectName("MilkReceptionTable");
    qDebug() << "init " + objectName();

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

MilkReceptionData MilkReceptionTable::getMilkReceptionData(const milk_id milkReceptionId) const
{
    return dao()->get(milkReceptionId);
}

MilkReception *MilkReceptionTable::getMilkReception(const qlonglong milkReceptionId)
{
    const auto mrData = getMilkReceptionData(milkReceptionId);
    const auto deliverer = getDeliverers()->getDeliverer(mrData.delivererId());
    const auto milkPoint = getMilkPoints()->getMilkPoint(mrData.milkPointId());

    auto milkReception = new MilkReception(mrData.id(), mrData.deliveryDate(), mrData.priceLiter(),
                                           mrData.liters(), mrData.fat(), deliverer, milkPoint, this);
    deliverer->setParent(milkReception);
    milkPoint->setParent(milkReception);

    return milkReception;
}

QList<MilkReceptionData> MilkReceptionTable::getMilkReceptions(const QString &where) const
{
    return dao()->get(where);
}

void MilkReceptionTable::insert(int index, MilkReception *milkReception)
{
    if(index < 0 || index > rowCount()) {
        return;
    }

    emit beginInsertRows(QModelIndex(), index, index);
    dao()->insert(milkReception->data());
    emit endInsertRows();
}

void MilkReceptionTable::append(MilkReception *milkReception)
{
    insert(rowCount(), milkReception);
}

void MilkReceptionTable::update(MilkReception *milkReception) const
{
    dao()->update(milkReception->data());
}

void MilkReceptionTable::setIdDeliverer(const milk_id milkReceptionId, const milk_id delivererId) const
{
    m_dao->updateValue(FN_ID, milkReceptionId, delivererId);
}

void MilkReceptionTable::setIdMilkPoint(const milk_id milkReceptionId, const milk_id milkPointId) const
{
    m_dao->updateValue(FN_MILK_POINT_ID, milkReceptionId, milkPointId);
}

void MilkReceptionTable::setDeliveryDate(const milk_id milkReceptionId, const QDate &deliveryDate) const
{
    m_dao->updateValue(FN_DELIVERY_DATE, milkReceptionId, deliveryDate);
}

void MilkReceptionTable::setPriceLiter(const milk_id milkReceptionId, const price priceLiter) const
{
    m_dao->updateValue(FN_PRICE_LITER, milkReceptionId, priceLiter);
}

void MilkReceptionTable::setLiters(const milk_id milkReceptionId, const double liters) const
{
    m_dao->updateValue(FN_LITERS, milkReceptionId, liters);
}

void MilkReceptionTable::setFat(const milk_id milkReceptionId, const double fat) const
{
    m_dao->updateValue(FN_FAT, milkReceptionId, fat);
}

bool MilkReceptionTable::updatePriceLiters(const price price, const QDate &dateFrom, const QDate &dateTo) const
{
    QSqlQuery query(m_db);
    query.prepare(QString("UPDATE %1 SET %2 = ? WHERE %3 BETWEEN ? AND ?")
                  .arg(TABLE_NAME)
                  .arg(FN_PRICE_LITER)
                  .arg(FN_DELIVERY_DATE));
    query.addBindValue(price);
    query.addBindValue(dateFrom.toString(Constants::defaultDateFormat()));
    query.addBindValue(dateTo.toString(Constants::defaultDateFormat()));

    if (!query.exec()) {
        emit error(query.lastError().text());
        return false;
    }
    return true;
}

QString MilkReceptionTable::primaryField() const
{
    return FN_ID;
}

QString MilkReceptionTable::selectAll() const
{
    const auto select = Utils::Main::getSelectStr(TABLE_NAME,
    {
                                                      getColName(RMT_ID, true),
                                                      getColName(RMT_ID_DELIVERER, true),
                                                      m_deliverers->getColName(DT_NAME, true) + " AS " + FN_DELIVERER_NAME,
                                                      getColName(RMT_MILK_POINT_ID, true),
                                                      m_milkPoints->getColName(MPT_NAME, true) + " AS " + FN_MILK_POINT_NAME,
                                                      getColName(RMT_DELIVERY_DATE, true),
                                                      getColName(RMT_PRICE_LITER, true),
                                                      getColName(RMT_LITERS, true),
                                                      getColName(RMT_FAT, true)
                                                  });
    const auto join = QString("LEFT JOIN %2 ON %3 = %4 LEFT JOIN %5 ON %6 = %7")
            .arg(m_deliverers->tableName())
            .arg(getColName(RMT_ID_DELIVERER, true))
            .arg(m_deliverers->getColName(DT_ID, true))
            .arg(m_milkPoints->tableName())
            .arg(getColName(RMT_MILK_POINT_ID, true))
            .arg(m_milkPoints->getColName(MPT_ID, true));

    return select + " " + join;
}

QVariant MilkReceptionTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    return Table::headerData(section, orientation, role);
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

QPair<double, double> MilkReceptionTable::getMinMaxPriceLiter(const QDate &min, QDate max) const
{
    if (!max.isValid())
        max = min;

    QSqlQuery query(m_db);
    query.prepare(QString("SELECT MIN(%1), MAX(%1) FROM %2 WHERE %3 BETWEEN '%4' AND '%5'")
                  .arg(FN_PRICE_LITER)
                  .arg(TABLE_NAME)
                  .arg(FN_DELIVERY_DATE)
                  .arg(min.toString(Constants::defaultDateFormat()))
                  .arg(max.toString(Constants::defaultDateFormat())));

    if (query.exec() && query.first()) {
        QPair<double, double>(query.value(0).toDouble(), query.value(1).toDouble());
    }

    return QPair<double, double>(.0, .0);
}

QDate MilkReceptionTable::getMinDeliveryDate() const
{
    QSqlQuery query(m_db);
    query.prepare(QString("SELECT MIN(%1) FROM %2")
                  .arg(FN_DELIVERY_DATE)
                  .arg(TABLE_NAME));

    if (query.exec() && query.first())
        return query.value(0).toDate();

    return QDate();
}

QDate MilkReceptionTable::getMaxDeliveryDate() const
{
    QSqlQuery query(m_db);
    query.prepare(QString("SELECT MAX(%1) FROM %2").arg(FN_DELIVERY_DATE).arg(TABLE_NAME));

    if (query.exec() && query.first())
        return query.value(0).toDate();

    return QDate();
}

QString db::MilkReceptionTable::getColName(const int position, const bool withTableName) const
{
    QString columnName;
    switch (position) {
    case ReceptionMilkTableColumns::RMT_ID:
        columnName = FN_ID;
        break;
    case ReceptionMilkTableColumns::RMT_ID_DELIVERER:
        columnName = FN_ID_DELIVERER;
        break;
    case ReceptionMilkTableColumns::RMT_DELIVERER_NAME:
        columnName = FN_DELIVERER_NAME;
        break;
    case ReceptionMilkTableColumns::RMT_MILK_POINT_ID:
        columnName = FN_MILK_POINT_ID;
        break;
    case ReceptionMilkTableColumns::RMT_MILK_POINT_NAME:
        columnName = FN_MILK_POINT_NAME;
        break;
    case ReceptionMilkTableColumns::RMT_DELIVERY_DATE:
        columnName = FN_DELIVERY_DATE;
        break;
    case ReceptionMilkTableColumns::RMT_PRICE_LITER:
        columnName = FN_PRICE_LITER;
        break;
    case ReceptionMilkTableColumns::RMT_LITERS:
        columnName = FN_LITERS;
        break;
    case ReceptionMilkTableColumns::RMT_FAT:
        columnName = FN_FAT;
        break;
    default:
        columnName = "";
        break;
    }

    return withTableName ? QString("%1.%2").arg(TABLE_NAME).arg(columnName) : columnName;
}

int db::MilkReceptionTable::getColPosition(const QString &columnName) const
{
    if (columnName == FN_ID)
        return ReceptionMilkTableColumns::RMT_ID;
    if (columnName == FN_ID_DELIVERER)
        return ReceptionMilkTableColumns::RMT_ID_DELIVERER;
    if (columnName == FN_DELIVERER_NAME)
        return ReceptionMilkTableColumns::RMT_DELIVERER_NAME;
    if (columnName == FN_MILK_POINT_ID)
        return ReceptionMilkTableColumns::RMT_MILK_POINT_ID;
    if (columnName == FN_MILK_POINT_NAME)
        return ReceptionMilkTableColumns::RMT_MILK_POINT_NAME;
    if (columnName == FN_DELIVERY_DATE)
        return ReceptionMilkTableColumns::RMT_DELIVERY_DATE;
    if (columnName == FN_PRICE_LITER)
        return ReceptionMilkTableColumns::RMT_PRICE_LITER;
    if (columnName == FN_LITERS)
        return ReceptionMilkTableColumns::RMT_LITERS;
    if (columnName == FN_FAT)
        return ReceptionMilkTableColumns::RMT_FAT;
    return -1;
}
