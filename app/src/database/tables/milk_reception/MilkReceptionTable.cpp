#include "MilkReceptionTable.h"

#include "MilkReceprionDao.h"
#include "tables/deliverers/DeliverersTable.h"
#include "tables/milk_points/MilkPointsTable.h"
#include "SettingsConstants.h"
#include "DbUtils.h"
// Qt
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

using SC = SettingsConstants;

USE_DB_NAMESPACE
using DC = DbConstants;


MilkReceptionDao::MilkReceptionDao(MilkReceptionTable *table) : Dao(table) { }

bool MilkReceptionDao::insert(const QVariant &data) const
{
    Q_ASSERT(data.canConvert<MilkReceptionData>());
    const MilkReceptionData milkReception = data.value<MilkReceptionData>();

    QSqlQuery query(m_table->database());
    query.prepare(DbUtils::getPrepInsertStr(DC::TMR_TABLE_NAME,
    { DC::TMR_FN_ID_DELIVERER, DC::TMR_FN_MILK_POINT_ID, DC::TMR_FN_DELIVERY_DATE, DC::TMR_FN_PRICE_LITER, DC::TMR_FN_LITERS, DC::TMR_FN_FAT }));
    query.addBindValue(milkReception.delivererId());
    query.addBindValue(milkReception.milkPointId());
    query.addBindValue(milkReception.deliveryDate().toString(SC::defaultDateFormat()));
    query.addBindValue(milkReception.priceLiter());
    query.addBindValue(milkReception.liters());
    query.addBindValue(milkReception.fat());
    if (!query.exec()) {
        _error(query.lastError().text());
        return false;
    }

    return true;
}

bool MilkReceptionDao::update(const QVariant &data) const
{
    Q_ASSERT(data.canConvert<MilkReceptionData>());
    const MilkReceptionData milkReception = data.value<MilkReceptionData>();

    QSqlQuery query(m_table->database());
    query.prepare(QString("%1 WHERE %2 = ?").arg(DbUtils::getPrepUpdateStr(DC::TMR_TABLE_NAME,
    { DC::TMR_FN_ID_DELIVERER, DC::TMR_FN_MILK_POINT_ID, DC::TMR_FN_DELIVERY_DATE, DC::TMR_FN_PRICE_LITER, DC::TMR_FN_LITERS, DC::TMR_FN_FAT }))
                  .arg(DC::TMR_FN_ID));
    query.addBindValue(milkReception.milkPointId());
    query.addBindValue(milkReception.deliveryDate());
    query.addBindValue(milkReception.priceLiter());
    query.addBindValue(milkReception.liters());
    query.addBindValue(milkReception.fat());
    query.addBindValue(milkReception.delivererId());

    if (!query.exec()) {
        _error(query.lastError().text());
        return false;
    }

    return true;
}

bool MilkReceptionDao::updatePriceLiter(const double price, const QDate &dateFrom, const QDate &dateTo) const
{
    QSqlQuery query(m_table->database());
    query.prepare(QString("UPDATE %1 SET %2 = ? WHERE %3 BETWEEN ? AND ?")
                  .arg(DC::TMR_TABLE_NAME)
                  .arg(DC::TMR_FN_PRICE_LITER)
                  .arg(DC::TMR_FN_DELIVERY_DATE));
    query.addBindValue(price);
    query.addBindValue(dateFrom.toString(SC::defaultDateFormat()));
    query.addBindValue(dateTo.toString(SC::defaultDateFormat()));

    if (!query.exec()) {
        _error(query.lastError().text());
        return false;
    }

    return true;
}

double MilkReceptionDao::getMinPriceLiter(const QDate &from, const QDate &to) const
{
    auto query = getMinAndOrMaxPriceLiter(from, to, MinMax::Min);
    if (query.first())
        return query.value(0).toDouble();

    return -1;
}

double MilkReceptionDao::getMaxPriceLiter(const QDate &from, const QDate &to) const
{
    auto query = getMinAndOrMaxPriceLiter(from, to, MinMax::Max);
    if (query.first())
        return query.value(0).toDouble();

    return -1;
}

std::tuple<double, double> MilkReceptionDao::getMinMaxPriceLiter(const QDate &from, const QDate &to) const
{
    auto query = getMinAndOrMaxPriceLiter(from, to, MinMax::Both);
    if (query.first())
        return std::make_tuple(query.value(0).toDouble(), query.value(1).toDouble());

    return std::make_tuple(-1.0, -1.0);
}

QSqlQuery MilkReceptionDao::getMinAndOrMaxPriceLiter(const QDate &from, const QDate &to, const MinMax minMax) const
{
    const auto fromDateStr = from.toString(SC::defaultDateFormat());
    const auto toDateStr = to.toString(SC::defaultDateFormat());

    QString minMaxStr;
    switch (minMax) {
    case MinMax::Min:
        minMaxStr = "MIN(%2)";
        break;
    case MinMax::Max:
        minMaxStr = "MAX(%2)";
        break;
    case MinMax::Both:
        minMaxStr = "MIN(%2), MAX(%2)";
        break;
    default:
        break;
    }

    QSqlQuery query(m_table->database());
    query.prepare(QString("SELECT %1 FROM %3 WHERE %4 BETWEEN '%5' AND '%6'")
                  .arg(minMaxStr)
                  .arg(DC::TMR_FN_PRICE_LITER)
                  .arg(DC::TMR_TABLE_NAME)
                  .arg(DC::TMR_FN_DELIVERY_DATE)
                  .arg(fromDateStr)
                  .arg(to.isValid() == false ? fromDateStr : toDateStr));

    if (!query.exec())
        _error(query.lastError().text());

    return query;
}

QDate MilkReceptionDao::getMinDeliveryDate() const
{
    return getMinMaxDeliveryDate(true);
}

QDate MilkReceptionDao::getMaxDeliveryDate() const
{
    return getMinMaxDeliveryDate(false);
}

QDate MilkReceptionDao::getMinMaxDeliveryDate(bool isMin) const
{
    QSqlQuery query(m_table->database());
    query.prepare(QString("SELECT %1(%2) FROM %3")
                  .arg(isMin ? "MIN" : "MAX")
                  .arg(DC::TMR_FN_DELIVERY_DATE)
                  .arg(DC::TMR_TABLE_NAME));

    if (query.exec()) {
        if (query.first())
            return query.value(0).toDate();
    } else
        _error(query.lastError().text());

    return QDate();
}

//--------------------------------------------------------------------------------------------------
MilkReceptionTable::MilkReceptionTable(QObject *parent):
    MilkReceptionTable(Q_NULLPTR, Q_NULLPTR, QSqlDatabase(), parent)
{

}

MilkReceptionTable::MilkReceptionTable(DeliverersTable *_deliverers, MilkPointsTable *milkPoints,
                                       QSqlDatabase db, QObject *parent):
    Table(new MilkReceptionDao(this), db, parent),
    m_deliverers(_deliverers),
    m_milkPoints(milkPoints)
{
    setObjectName("MilkReceptionTable");

    setQuery(selectAll());
}

MilkReceptionTable::~MilkReceptionTable()
{
}

QString MilkReceptionTable::tableName() const
{
    return DC::TMR_TABLE_NAME;
}

std::experimental::optional<MilkReceptionData> MilkReceptionTable::getMilkReceptionData(const DbConstants::milk_id milkReceptionId) const
{
    auto data = dao()->get(milkReceptionId);
    if (data.isNull())
        return {};

    return fromRecord(data.value<QSqlRecord>());
}

MilkReception *MilkReceptionTable::getMilkReception(const int milkReceptionId)
{
    const auto data = getMilkReceptionData(milkReceptionId);
    if (!data)
        return Q_NULLPTR;

    const auto mrData = data.value();
    const auto deliverer = deliverers()->getDeliverer(mrData.delivererId());
    const auto milkPoint = milkPoints()->getMilkPoint(mrData.milkPointId());

    auto milkReception = new MilkReception(mrData.id(), mrData.deliveryDate(), mrData.priceLiter(),
                                           mrData.liters(), mrData.fat(), deliverer, milkPoint, this);
    deliverer->setParent(milkReception);
    milkPoint->setParent(milkReception);

    return milkReception;
}

QList<MilkReceptionData> MilkReceptionTable::getMilkReceptionsData(const QString &where) const
{
    const QList<QSqlRecord> data = dao()->getAll(where).value< QList<QSqlRecord> >();

    QList<MilkReceptionData> milkReceptions;
    for (const auto &record : data)
        milkReceptions.append(fromRecord(record));

    return milkReceptions;
}

bool MilkReceptionTable::insert(int index, MilkReception *milkReception)
{
    if(index < 0 || index > rowCount()) {
        return false;
    }

    emit beginInsertRows(QModelIndex(), index, index);
    const bool isOk = dao()->insert(QVariant::fromValue(milkReception->data()));
    emit endInsertRows();

    return isOk;
}

bool MilkReceptionTable::append(MilkReception *milkReception)
{
    return insert(rowCount(), milkReception);
}

bool MilkReceptionTable::update(MilkReception *milkReception) const
{
    return dao()->update(QVariant::fromValue(milkReception->data()));
}

bool MilkReceptionTable::setIdDeliverer(const DbConstants::milk_id milkReceptionId, const DbConstants::milk_id delivererId) const
{
    return m_dao->updateValue(DC::TMR_FN_ID, milkReceptionId, delivererId);
}

bool MilkReceptionTable::setIdMilkPoint(const DbConstants::milk_id milkReceptionId, const DbConstants::milk_id milkPointId) const
{
    return m_dao->updateValue(DC::TMR_FN_MILK_POINT_ID, milkReceptionId, milkPointId);
}

bool MilkReceptionTable::setDeliveryDate(const DbConstants::milk_id milkReceptionId, const QDate &deliveryDate) const
{
    return m_dao->updateValue(DC::TMR_FN_DELIVERY_DATE, milkReceptionId, deliveryDate);
}

bool MilkReceptionTable::setPriceLiter(const DbConstants::milk_id milkReceptionId, const double priceLiter) const
{
    return m_dao->updateValue(DC::TMR_FN_PRICE_LITER, milkReceptionId, priceLiter);
}

bool MilkReceptionTable::setLiters(const DbConstants::milk_id milkReceptionId, const double liters) const
{
    return m_dao->updateValue(DC::TMR_FN_LITERS, milkReceptionId, liters);
}

bool MilkReceptionTable::setFat(const DbConstants::milk_id milkReceptionId, const double fat) const
{
    return m_dao->updateValue(DC::TMR_FN_FAT, milkReceptionId, fat);
}

bool MilkReceptionTable::updatePriceLiters(const double price, const QDate &dateFrom, const QDate &dateTo) const
{
    return dao()->updatePriceLiter(price, dateFrom, dateTo);
}

std::tuple<double, double> MilkReceptionTable::getMinMaxPriceLiter(const QDate &from, const QDate &to) const
{
    return dao()->getMinMaxPriceLiter(from, to);
}

QDate MilkReceptionTable::getMinDeliveryDate() const
{
    return dao()->getMinDeliveryDate();
}

QDate MilkReceptionTable::getMaxDeliveryDate() const
{
    return dao()->getMaxDeliveryDate();
}

QString MilkReceptionTable::primaryField() const
{
    return DC::TMR_FN_ID;
}

QString MilkReceptionTable::selectAll() const
{
    const auto select = DbUtils::getSelectStr(DC::TMR_TABLE_NAME,
    {
                                                  getColName(DC::TMR_ID, true),
                                                  getColName(DC::TMR_ID_DELIVERER, true),
                                                  m_deliverers->getColName(DC::TD_NAME, true) + " AS " + DC::TMR_FN_DELIVERER_NAME,
                                                  getColName(DC::TMR_MILK_POINT_ID, true),
                                                  m_milkPoints->getColName(DC::TMP_NAME, true) + " AS " + DC::TMR_FN_MILK_POINT_NAME,
                                                  getColName(DC::TMR_DELIVERY_DATE, true),
                                                  getColName(DC::TMR_PRICE_LITER, true),
                                                  getColName(DC::TMR_LITERS, true),
                                                  getColName(DC::TMR_FAT, true)
                                              });
    const auto join = QString("LEFT JOIN %2 ON %3 = %4 LEFT JOIN %5 ON %6 = %7")
            .arg(m_deliverers->tableName())
            .arg(getColName(DC::TMR_ID_DELIVERER, true))
            .arg(m_deliverers->getColName(DC::TD_ID, true))
            .arg(m_milkPoints->tableName())
            .arg(getColName(DC::TMR_MILK_POINT_ID, true))
            .arg(m_milkPoints->getColName(DC::TMP_ID, true));

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


DeliverersTable *MilkReceptionTable::deliverers() const
{
    return m_deliverers;
}

MilkPointsTable *MilkReceptionTable::milkPoints() const
{
    return m_milkPoints;
}

QString MilkReceptionTable::getColName(const int position, const bool withTableName) const
{
    QString columnName;
    switch (position) {
    case DC::TMR_ID:
        columnName = DC::TMR_FN_ID;
        break;
    case DC::TMR_ID_DELIVERER:
        columnName = DC::TMR_FN_ID_DELIVERER;
        break;
    case DC::TMR_DELIVERER_NAME:
        columnName = DC::TMR_FN_DELIVERER_NAME;
        break;
    case DC::TMR_MILK_POINT_ID:
        columnName = DC::TMR_FN_MILK_POINT_ID;
        break;
    case DC::TMR_MILK_POINT_NAME:
        columnName = DC::TMR_FN_MILK_POINT_NAME;
        break;
    case DC::TMR_DELIVERY_DATE:
        columnName = DC::TMR_FN_DELIVERY_DATE;
        break;
    case DC::TMR_PRICE_LITER:
        columnName = DC::TMR_FN_PRICE_LITER;
        break;
    case DC::TMR_LITERS:
        columnName = DC::TMR_FN_LITERS;
        break;
    case DC::TMR_FAT:
        columnName = DC::TMR_FN_FAT;
        break;
    default:
        columnName = "";
        break;
    }

    return withTableName ? QString("%1.%2").arg(DC::TMR_TABLE_NAME).arg(columnName) : columnName;
}

int db::MilkReceptionTable::getColPosition(const QString &columnName) const
{
    if (columnName == DC::TMR_FN_ID)
        return DC::TMR_ID;
    if (columnName == DC::TMR_FN_ID_DELIVERER)
        return DC::TMR_ID_DELIVERER;
    if (columnName == DC::TMR_FN_DELIVERER_NAME)
        return DC::TMR_DELIVERER_NAME;
    if (columnName == DC::TMR_FN_MILK_POINT_ID)
        return DC::TMR_MILK_POINT_ID;
    if (columnName == DC::TMR_FN_MILK_POINT_NAME)
        return DC::TMR_MILK_POINT_NAME;
    if (columnName == DC::TMR_FN_DELIVERY_DATE)
        return DC::TMR_DELIVERY_DATE;
    if (columnName == DC::TMR_FN_PRICE_LITER)
        return DC::TMR_PRICE_LITER;
    if (columnName == DC::TMR_FN_LITERS)
        return DC::TMR_LITERS;
    if (columnName == DC::TMR_FN_FAT)
        return DC::TMR_FAT;
    return -1;
}

MilkReceptionData MilkReceptionTable::fromRecord(const QSqlRecord &record)
{
    return {
        record.value(DC::TMR_FN_ID).toInt(),
                record.value(DC::TMR_FN_ID_DELIVERER).toInt(),
                record.value(DC::TMR_FN_MILK_POINT_ID).toInt(),
                record.value(DC::TMR_FN_DELIVERY_DATE).toDate(),
                record.value(DC::TMR_FN_PRICE_LITER).toDouble(),
                record.value(DC::TMR_FN_LITERS).toDouble(),
                record.value(DC::TMR_FN_FAT).toDouble()
    };
}


QVariant db::MilkReceptionTable::get(const int row)
{
    return QVariant::fromValue(getMilkReception(data(index(row, 0)).toInt()));
}
