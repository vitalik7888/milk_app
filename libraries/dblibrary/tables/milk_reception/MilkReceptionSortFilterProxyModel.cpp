#include "MilkReceptionSortFilterProxyModel.h"

USE_DB_NAMESPACE

using DBC = DbConstants;


MilkReceptionSortFilterProxyModel::MilkReceptionSortFilterProxyModel(QObject *parent) :
    MilkSortFilterProxyModel(parent)
{

}

void MilkReceptionSortFilterProxyModel::setMilkPointId(int milkPointId)
{
    if (m_milkPointId == milkPointId)
        return;

    m_milkPointId = milkPointId;
    emit milkPointIdChanged(m_milkPointId);
    invalidateFilter();
}

void MilkReceptionSortFilterProxyModel::setMilkReceptionId(int milkReceptionId)
{
    if (m_milkReceptionId == milkReceptionId)
        return;

    m_milkReceptionId = milkReceptionId;
    emit milkReceptionIdChanged(m_milkReceptionId);
    invalidateFilter();
}

void MilkReceptionSortFilterProxyModel::setDelivererId(int delivererId)
{
    if (m_delivererId == delivererId)
        return;

    m_delivererId = delivererId;
    emit delivererIdChanged(m_delivererId);
    invalidateFilter();
}

void MilkReceptionSortFilterProxyModel::setMinimumDate(const QDate &date)
{
    m_minDate = date;
    invalidateFilter();
}

void MilkReceptionSortFilterProxyModel::setMaximumDate(const QDate &date)
{
    m_maxDate = date;
    invalidateFilter();
}

void MilkReceptionSortFilterProxyModel::reset()
{
    setMilkReceptionId(-1);
    setDelivererId(-1);
    setMilkPointId(-1);
    setMinimumDate(QDate());
    setMaximumDate(QDate());
}

bool MilkReceptionSortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    const QModelIndex indexId = sourceModel()->index(sourceRow, DBC::TMR_ID, sourceParent),
            indexDelivererId = sourceModel()->index(sourceRow,  DBC::TMR_ID_DELIVERER, sourceParent),
            indexMilkPointId = sourceModel()->index(sourceRow,  DBC::TMR_MILK_POINT_ID, sourceParent),
            indexDate = sourceModel()->index(sourceRow, DBC::TMR_DELIVERY_DATE, sourceParent);

    return isFilterAcceptRowById(sourceModel()->data(indexId).toInt()) &&
            isFilterAcceptRowByDelivererId(sourceModel()->data(indexDelivererId).toInt()) &&
            isFilterAcceptRowByMilkPointId(sourceModel()->data(indexMilkPointId).toInt()) &&
            dateInRange(sourceModel()->data(indexDate).toDate());
}

bool MilkReceptionSortFilterProxyModel::lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const
{
    QVariant leftData = sourceModel()->data(sourceLeft);
    QVariant rightData = sourceModel()->data(sourceRight);

    if (leftData.type() == QVariant::String){
        return leftData.toString() < rightData.toString();
    } else if (leftData.type() == QVariant::Int){
        return leftData.toInt() < rightData.toInt();
    } else if (leftData.type() == QVariant::Date){
        return leftData.toDate() < rightData.toDate();
    } else if (leftData.type() == QVariant::Double){
        return leftData.toDouble() < rightData.toDouble();
    }

    return QSortFilterProxyModel::lessThan(sourceLeft, sourceRight);
}

bool MilkReceptionSortFilterProxyModel::isFilterAcceptRowById(const int id) const
{
    return m_milkReceptionId <= 0 ? true : m_milkReceptionId == id;
}

bool MilkReceptionSortFilterProxyModel::isFilterAcceptRowByDelivererId(const int delivererId) const
{
    return m_delivererId <= 0 ? true : m_delivererId == delivererId;
}

bool MilkReceptionSortFilterProxyModel::isFilterAcceptRowByMilkPointId(const int milkPointId) const
{
    return m_milkPointId <= 0 ? true : m_milkPointId == milkPointId;
}

bool MilkReceptionSortFilterProxyModel::dateInRange(const QDate &date) const
{
    return (!m_minDate.isValid() || date > m_minDate) && (!m_maxDate.isValid() || date < m_maxDate);
}
