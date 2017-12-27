#include "MilkReceptionModel.h"

#include "MilkReceprionDao.h"
#include <MilkReception.h>
#include <Deliverer.h>
#include <MilkPoint.h>
#include "SettingsConstants.h"
#include <TypesConstants.h>
#include "DbUtils.h"
// Qt
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>


USE_DB_NAMESPACE
using DC = DbConstants;
using SC = SettingsConstants;
using TC = TypesConstants;


MilkReceptionDao::MilkReceptionDao(QObject *parent) : DaoSql(parent) { }

QString MilkReceptionDao::getCreateTableStr() const
{
    return DC::TMR_CREATE_TABLE_SQL;
}

QString MilkReceptionDao::_tableName() const
{
    return DC::TMR_TABLE_NAME;
}

QString MilkReceptionDao::_primaryFieldName() const
{
    return DC::TMR_FN_ID;
}

QStringList MilkReceptionDao::_fieldsNames() const
{
    return { primaryFieldName(),
                DC::TMR_FN_ID_DELIVERER,
                DC::TMR_FN_DELIVERER_FNAME,
                DC::TMR_FN_DELIVERER_LNAME,
                DC::TMR_FN_MILK_POINT_ID,
                DC::TMR_FN_MILK_POINT_NAME,
                DC::TMR_FN_DELIVERY_DATE,
                DC::TMR_FN_PRICE_LITER,
                DC::TMR_FN_LITERS,
                DC::TMR_FN_FAT
    };
}

DaoItem MilkReceptionDao::fromRecord(const QSqlRecord &record)
{
    if (record.isEmpty())
        return Q_NULLPTR;

    return std::make_unique<MilkReceptionData>(record.value(DC::TMR_FN_ID).toInt(),
                                           record.value(DC::TMR_FN_ID_DELIVERER).toInt(),
                                           record.value(DC::TMR_FN_MILK_POINT_ID).toInt(),
                                           record.value(DC::TMR_FN_DELIVERY_DATE).toDate(),
                                           record.value(DC::TMR_FN_PRICE_LITER).toDouble(),
                                           record.value(DC::TMR_FN_LITERS).toDouble(),
                                           record.value(DC::TMR_FN_FAT).toDouble());
}

bool MilkReceptionDao::_insert(MilkBaseItem *item)
{
    const auto milkReception = static_cast<MilkReception *>(item);
    Q_ASSERT(milkReception);

    QSqlQuery query(m_db);
    query.prepare(DbUtils::getPrepInsertStr(DC::TMR_TABLE_NAME,
    { DC::TMR_FN_ID_DELIVERER, DC::TMR_FN_MILK_POINT_ID, DC::TMR_FN_DELIVERY_DATE,
      DC::TMR_FN_PRICE_LITER, DC::TMR_FN_LITERS, DC::TMR_FN_FAT }));
    query.addBindValue(milkReception->deliverer()->milkId());
    query.addBindValue(milkReception->milkPoint()->milkId());
    query.addBindValue(milkReception->deliveryDate().toString(SC::defaultDateFormat()));
    query.addBindValue(milkReception->priceLiter());
    query.addBindValue(milkReception->liters());
    query.addBindValue(milkReception->fat());
    if (!query.exec()) {
        _error(query.lastError().text());
        return false;
    }

    item->setMilkId(query.lastInsertId().toInt());
    return true;
}

bool MilkReceptionDao::_update(const MilkBaseItem *item)
{
    const auto milkReception = static_cast<const MilkReception *>(item);
    Q_ASSERT(milkReception);

    QSqlQuery query(m_db);
    query.prepare(QString("%1 WHERE %2 = ?").arg(DbUtils::getPrepUpdateStr(DC::TMR_TABLE_NAME,
    { DC::TMR_FN_ID_DELIVERER, DC::TMR_FN_MILK_POINT_ID, DC::TMR_FN_DELIVERY_DATE, DC::TMR_FN_PRICE_LITER, DC::TMR_FN_LITERS, DC::TMR_FN_FAT }))
                  .arg(DC::TMR_FN_ID));
    query.addBindValue(milkReception->milkPoint()->milkId());
    query.addBindValue(milkReception->deliveryDate());
    query.addBindValue(milkReception->priceLiter());
    query.addBindValue(milkReception->liters());
    query.addBindValue(milkReception->fat());
    query.addBindValue(milkReception->deliverer()->milkId());

    if (!query.exec()) {
        _error(query.lastError().text());
        return false;
    }

    return true;
}

bool MilkReceptionDao::updatePriceLiter(const double price, const QDate &dateFrom, const QDate &dateTo)
{
    QSqlQuery query(m_db);
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

double MilkReceptionDao::getMinPriceLiter(const QDate &from, const QDate &to)
{
    auto query = getMinAndOrMaxPriceLiter(from, to, MinMax::Min);
    if (query.first())
        return query.value(0).toDouble();

    return -1;
}

double MilkReceptionDao::getMaxPriceLiter(const QDate &from, const QDate &to)
{
    auto query = getMinAndOrMaxPriceLiter(from, to, MinMax::Max);
    if (query.first())
        return query.value(0).toDouble();

    return -1;
}

std::tuple<double, double> MilkReceptionDao::getMinMaxPriceLiter(const QDate &from, const QDate &to)
{
    auto query = getMinAndOrMaxPriceLiter(from, to, MinMax::Both);
    if (query.first())
        return std::make_tuple(query.value(0).toDouble(), query.value(1).toDouble());

    return std::make_tuple(-1.0, -1.0);
}

QSqlQuery MilkReceptionDao::getMinAndOrMaxPriceLiter(const QDate &from, const QDate &to, const MinMax minMax)
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

    QSqlQuery query(m_db);
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

QDate MilkReceptionDao::getMinDeliveryDate()
{
    return getMinMaxDeliveryDate(true);
}

QDate MilkReceptionDao::getMaxDeliveryDate()
{
    return getMinMaxDeliveryDate(false);
}

QDate MilkReceptionDao::getMinMaxDeliveryDate(bool isMin)
{
    QSqlQuery query(m_db);
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
MilkReceptionModel::MilkReceptionModel(QObject *parent):
    MilkReceptionModel(Q_NULLPTR, Q_NULLPTR, parent)
{

}

MilkReceptionModel::MilkReceptionModel(DeliverersModel *_deliverers, MilkPointsModel *milkPoints,
                                       QObject *parent):
    MilkModel(parent),
    m_deliverers(_deliverers),
    m_milkPoints(milkPoints)
{
//    connect(m_deliverers, &LocalitiesModel::endRefresh, this, &MilkReceptionModel::refresh);
//    connect(m_milkPoints, &MilkPointsModel::endRefresh, this, &MilkReceptionModel::refresh);
}

DeliverersModel *MilkReceptionModel::deliverers() const
{
    return m_deliverers;
}

MilkPointsModel *MilkReceptionModel::milkPoints() const
{
    return m_milkPoints;
}

QVariant db::MilkReceptionModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return {};

    const auto milkReception = static_cast<const MilkReception *>(m_repository.get(index.row()));

    switch (role) {
    case static_cast<int>(DC::MilkReceptionRoles::MilkIdRole):
        return milkReception->milkId();
    case static_cast<int>(DC::MilkReceptionRoles::MR_DelivererIdRole):
        return milkReception->deliverer() ? milkReception->deliverer()->milkId() : TC::DEFAULT_ID;
    case static_cast<int>(DC::MilkReceptionRoles::MR_DelivererFullNameRole):
        return milkReception->deliverer() ? milkReception->deliverer()->fullName() : "";
    case static_cast<int>(DC::MilkReceptionRoles::MR_MilkPointIdRole):
        return milkReception->milkPoint() ? milkReception->milkPoint()->milkId() : TC::DEFAULT_ID;
    case static_cast<int>(DC::MilkReceptionRoles::MR_MilkPointNameRole):
        return milkReception->milkPoint() ? milkReception->milkPoint()->name() : "";
    case static_cast<int>(DC::MilkReceptionRoles::MR_DeliveryDateRole):
        return milkReception->deliveryDate();
    case static_cast<int>(DC::MilkReceptionRoles::MR_PriceLiterRole):
        return milkReception->priceLiter();
    case static_cast<int>(DC::MilkReceptionRoles::MR_LitersRole):
        return milkReception->liters();
    case static_cast<int>(DC::MilkReceptionRoles::MR_FatRole):
        return milkReception->fat();
    }

    return {};
}

bool db::MilkReceptionModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role == static_cast<int>(DC::MilkReceptionRoles::MilkIdRole) ||
             role == static_cast<int>(DC::MilkReceptionRoles::MR_DelivererFullNameRole) ||
             role == static_cast<int>(DC::MilkReceptionRoles::MR_MilkPointNameRole))
        return false;

    MilkReception& milkReception = static_cast<MilkReception&>(*m_repository.get(index.row()));

    bool isOk = false;
    switch (role) {
    case static_cast<int>(DC::MilkReceptionRoles::MR_DelivererIdRole):
        isOk = m_dao->updateValue(DC::TMR_ID_DELIVERER, milkReception.milkId(), value.toInt());
        if(isOk)
            milkReception.setDeliverer(static_cast<const Deliverer *>(
                                           deliverers()->getItemById(value.toInt())));
        break;
    case static_cast<int>(DC::MilkReceptionRoles::MR_MilkPointIdRole):
        isOk = m_dao->updateValue(DC::TMR_MILK_POINT_ID, milkReception.milkId(), value.toInt());
        if(isOk)
            milkReception.setMilkPoint(static_cast<const MilkPoint *>(
                                           milkPoints()->getItemById(value.toInt())));
        break;
    case static_cast<int>(DC::MilkReceptionRoles::MR_DeliveryDateRole):
        isOk = m_dao->updateValue(DC::TMR_DELIVERY_DATE, milkReception.milkId(), value.toDate());
        if(isOk)
            milkReception.setDeliveryDate(value.toDate());
        break;
    case static_cast<int>(DC::MilkReceptionRoles::MR_PriceLiterRole):
        isOk = m_dao->updateValue(DC::TMR_PRICE_LITER, milkReception.milkId(), value.toDouble());
        if(isOk)
            milkReception.setPriceLiter(value.toDouble());
        break;
    case static_cast<int>(DC::MilkReceptionRoles::MR_LitersRole):
        isOk = m_dao->updateValue(DC::TMR_LITERS, milkReception.milkId(), value.toDouble());
        if(isOk)
            milkReception.setLiters(value.toDouble());
        break;
    case static_cast<int>(DC::MilkReceptionRoles::MR_FatRole):
        isOk = m_dao->updateValue(DC::TMR_FAT, milkReception.milkId(), value.toDouble());
        if(isOk)
            milkReception.setFat(value.toDouble());
        break;
    }

    if (isOk)
        emit dataChanged(index, index);

    return isOk;
}

QHash<int, QByteArray> db::MilkReceptionModel::roleNames() const
{
    return {
        {static_cast<int>(DC::MilkReceptionRoles::MilkIdRole), "milkId"},
        {static_cast<int>(DC::MilkReceptionRoles::MR_DelivererIdRole), "delivererId"},
        {static_cast<int>(DC::MilkReceptionRoles::MR_DelivererFullNameRole), "delivererFullName"},
        {static_cast<int>(DC::MilkReceptionRoles::MR_MilkPointIdRole), "milkPointId"},
        {static_cast<int>(DC::MilkReceptionRoles::MR_MilkPointNameRole), "milkPointName"},
        {static_cast<int>(DC::MilkReceptionRoles::MR_DeliveryDateRole), "deliveryDate"},
        {static_cast<int>(DC::MilkReceptionRoles::MR_PriceLiterRole), "priceLiter"},
        {static_cast<int>(DC::MilkReceptionRoles::MR_LitersRole), "liters"},
        {static_cast<int>(DC::MilkReceptionRoles::MR_FatRole), "fat"},
    };
}

void MilkReceptionModel::copyItemValues(MilkBaseItem *left, const MilkBaseItem *right)
{
    auto itemSource = static_cast<MilkReception *>(left);
    auto item = static_cast<const MilkReception *>(right);
    itemSource->setDeliverer(item->deliverer());
    itemSource->setMilkPoint(item->milkPoint());
    itemSource->setDeliveryDate(item->deliveryDate());
    itemSource->setPriceLiter(item->priceLiter());
    itemSource->setLiters(item->liters());
    itemSource->setFat(item->fat());
}

void MilkReceptionModel::appendToRepository(const MilkBaseItem *item)
{
    m_repository.append<MilkReception>(item);
}

void db::MilkReceptionModel::refresh()
{
    emit beginRefresh();
    clear();

    const auto items = m_dao->get();
    for (const auto &item : *items)
    {
        const auto daoItem = static_cast<const MilkReceptionData *>(item.get());
        const auto deliverer = static_cast<const Deliverer *>(
                    m_deliverers->getItemById(daoItem->delivererId()));
        const auto milkPoint = static_cast<const MilkPoint *>(
                    m_milkPoints->getItemById(daoItem->milkPointId()));
        MilkReception mr(daoItem->milkId(), daoItem->deliveryDate(), daoItem->priceLiter(),
                         daoItem->liters(), daoItem->fat(), deliverer, milkPoint);
        appendToRepository(&mr);
    }

    emit endRefresh();
}
