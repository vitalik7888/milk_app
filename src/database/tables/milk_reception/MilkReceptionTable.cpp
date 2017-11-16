#include "MilkReceptionTable.h"

#include "milkrecepriondao.h"
#include "tables/deliverers/DeliverersTable.h"
#include "tables/milk_points/MilkPointsTable.h"
#include "SettingsConstants.h"
#include "Utils.h"
// Qt
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

using SC = SettingsConstants;

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
MilkReceptionDao::MilkReceptionDao(MilkReceptionTable *table) : Dao(table) { }

std::experimental::optional<MilkReceptionData> MilkReceptionDao::get(const milk_id id) const
{
    QSqlQuery query(m_table->database());
    query.prepare(QString("%1 WHERE %2 = ?")
                  .arg(Utils::Main::getSelectStr(TABLE_NAME,
    { FN_ID_DELIVERER, FN_MILK_POINT_ID, FN_DELIVERY_DATE, FN_PRICE_LITER, FN_LITERS, FN_FAT }))
                  .arg(FN_ID));
    query.addBindValue(id);

    if (query.exec() && query.first())
    {
        return MilkReceptionData(
                    id,
                    query.value(FN_ID_DELIVERER).toLongLong(),
                    query.value(FN_MILK_POINT_ID).toLongLong(),
                    query.value(FN_DELIVERY_DATE).toDate(),
                    query.value(FN_PRICE_LITER).toDouble(),
                    query.value(FN_LITERS).toDouble(),
                    query.value(FN_FAT).toDouble()
                    );
    } else
        _error(QString("Отсутствует сдача молока с id = %1").arg(id));

    return {};
}

QList<MilkReceptionData> MilkReceptionDao::get(const QString &where) const
{
    QSqlQuery query(m_table->database());
    query.prepare(QString("%1%2")
                  .arg(Utils::Main::getSelectStr(TABLE_NAME,
    { FN_ID, FN_ID_DELIVERER, FN_MILK_POINT_ID, FN_DELIVERY_DATE, FN_PRICE_LITER, FN_LITERS, FN_FAT }))
                  .arg(where.isEmpty() ? QString() : " WHERE " + where));

    QList<MilkReceptionData> mrd;
    if (query.exec())
    {
        while (query.next()) {
            mrd.append({query.value(FN_ID).toLongLong(),
                        query.value(FN_ID_DELIVERER).toLongLong(),
                        query.value(FN_MILK_POINT_ID).toLongLong(),
                        query.value(FN_DELIVERY_DATE).toDate(),
                        query.value(FN_PRICE_LITER).toDouble(),
                        query.value(FN_LITERS).toDouble(),
                        query.value(FN_FAT).toDouble()
                       });
        }
    } else
        _error(query.lastError().text());

    return mrd;
}

bool MilkReceptionDao::insert(const MilkReceptionData &data) const
{
    QSqlQuery query(m_table->database());
    query.prepare(Utils::Main::getPrepInsertStr(TABLE_NAME,
    { FN_ID_DELIVERER, FN_MILK_POINT_ID, FN_DELIVERY_DATE, FN_PRICE_LITER, FN_LITERS, FN_FAT }));
    query.addBindValue(data.delivererId());
    query.addBindValue(data.milkPointId());
    query.addBindValue(data.deliveryDate().toString(SC::defaultDateFormat()));
    query.addBindValue(data.priceLiter());
    query.addBindValue(data.liters());
    query.addBindValue(data.fat());

    if (!query.exec()) {
        _error(query.lastError().text());
        return false;
    }

    return true;
}

bool MilkReceptionDao::update(const MilkReceptionData &data) const
{
    QSqlQuery query(m_table->database());
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
        _error(query.lastError().text());
        return false;
    }

    return true;
}

bool MilkReceptionDao::updatePriceLiter(const double price, const QDate &dateFrom, const QDate &dateTo) const
{
    QSqlQuery query(m_table->database());
    query.prepare(QString("UPDATE %1 SET %2 = ? WHERE %3 BETWEEN ? AND ?")
                  .arg(TABLE_NAME)
                  .arg(FN_PRICE_LITER)
                  .arg(FN_DELIVERY_DATE));
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
                  .arg(FN_PRICE_LITER)
                  .arg(TABLE_NAME)
                  .arg(FN_DELIVERY_DATE)
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
                  .arg(FN_DELIVERY_DATE)
                  .arg(TABLE_NAME));

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

std::experimental::optional<MilkReceptionData> MilkReceptionTable::getMilkReceptionData(const milk_id milkReceptionId) const
{
    return dao()->get(milkReceptionId);
}

MilkReception *MilkReceptionTable::getMilkReception(const qlonglong milkReceptionId)
{
    const auto data = getMilkReceptionData(milkReceptionId);
    if (!data)
        return Q_NULLPTR;

    const auto mrData = data.value();
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

bool MilkReceptionTable::insert(int index, MilkReception *milkReception)
{
    if(index < 0 || index > rowCount()) {
        return false;
    }

    emit beginInsertRows(QModelIndex(), index, index);
    const bool isOk = dao()->insert(milkReception->data());
    emit endInsertRows();

    return isOk;
}

bool MilkReceptionTable::append(MilkReception *milkReception)
{
    return insert(rowCount(), milkReception);
}

bool MilkReceptionTable::update(MilkReception *milkReception) const
{
    return dao()->update(milkReception->data());
}

bool MilkReceptionTable::setIdDeliverer(const milk_id milkReceptionId, const milk_id delivererId) const
{
    return m_dao->updateValue(FN_ID, milkReceptionId, delivererId);
}

bool MilkReceptionTable::setIdMilkPoint(const milk_id milkReceptionId, const milk_id milkPointId) const
{
    return m_dao->updateValue(FN_MILK_POINT_ID, milkReceptionId, milkPointId);
}

bool MilkReceptionTable::setDeliveryDate(const milk_id milkReceptionId, const QDate &deliveryDate) const
{
    return m_dao->updateValue(FN_DELIVERY_DATE, milkReceptionId, deliveryDate);
}

bool MilkReceptionTable::setPriceLiter(const milk_id milkReceptionId, const double priceLiter) const
{
    return m_dao->updateValue(FN_PRICE_LITER, milkReceptionId, priceLiter);
}

bool MilkReceptionTable::setLiters(const milk_id milkReceptionId, const double liters) const
{
    return m_dao->updateValue(FN_LITERS, milkReceptionId, liters);
}

bool MilkReceptionTable::setFat(const milk_id milkReceptionId, const double fat) const
{
    return m_dao->updateValue(FN_FAT, milkReceptionId, fat);
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
