#include "SortFilterMilkReceptionTable.h"

#include "tables/milk_reception/MilkReceptionTable.h"
#include "Utils.h"
// Qt
#include <QDebug>

using utm = Utils::Main;


SortFilterMilkReceptionTable::SortFilterMilkReceptionTable(QObject *parent):
    QSortFilterProxyModel(parent),
    m_milkReceptionTable(nullptr),
    m_delivererId(-1),
    m_milkPointId(-1),
    m_dateMin(QDate()),
    m_dateMax(QDate())
{

}

/*void SortFilterMilkReceptionTable::setFilterMinimumDate(const QDate &date)
{
    m_dateMin = date;
    invalidateFilter();
}

void SortFilterMilkReceptionTable::setFilterMaximumDate(const QDate &date)
{
    m_dateMax = date;
    invalidateFilter();
}*/

void SortFilterMilkReceptionTable::setFilterDelivererId(const qlonglong &delivererId)
{
    m_delivererId = delivererId;
    invalidateFilter();
}

void SortFilterMilkReceptionTable::setFilterMilkPointId(const qlonglong &milkPointId)
{
    m_milkPointId = milkPointId;
    invalidateFilter();
}

bool SortFilterMilkReceptionTable::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    const auto mrIdDelivererCol = m_milkReceptionTable->getColumnPosition(m_milkReceptionTable->getNameColumnIdDeliverer(false)),
            mrIdMilkPointCol = m_milkReceptionTable->getColumnPosition(m_milkReceptionTable->getNameColumnMilkPointId(false)),
            mrDelivDateCol = m_milkReceptionTable->getColumnPosition(m_milkReceptionTable->getNameColumnDeliveryDate(false));

    const auto indexDelivererId = sourceModel()->index(sourceRow, mrIdDelivererCol, sourceParent),
            indexMilkPointId = sourceModel()->index(sourceRow, mrIdMilkPointCol, sourceParent),
            indexDeliveryDate = sourceModel()->index(sourceRow, mrDelivDateCol, sourceParent);

    const auto delivererId = sourceModel()->data(indexDelivererId).toLongLong(),
            milkPointId = sourceModel()->data(indexMilkPointId).toLongLong();
    const auto deliveryDate = sourceModel()->data(indexDeliveryDate).toDate();

    bool isDelivererAccepted = true, isMilkPointAccepted = true, isDateAccepted = true;
    if (isNeedFilterByDelivId())
        isDelivererAccepted = (m_delivererId == delivererId);
    if (utm::isAutoIncrIdIsValid(m_milkPointId))
        isMilkPointAccepted = (milkPointId == m_milkPointId);
    if (m_dateMin.isValid() && m_dateMax.isValid())
        isDateAccepted = (deliveryDate >= m_dateMin && deliveryDate <= m_dateMax);

    return isDelivererAccepted && isMilkPointAccepted && isDateAccepted;
}

bool SortFilterMilkReceptionTable::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    QVariant leftData = sourceModel()->data(source_left);
    QVariant rightData = sourceModel()->data(source_right);

    if (leftData.type() == QVariant::DateTime)
        return leftData.toDateTime() < rightData.toDateTime();

    return QSortFilterProxyModel::lessThan(source_left, source_right);
}

bool SortFilterMilkReceptionTable::dateBetween(const QDate &date) const
{
    return (!m_dateMin.isValid() || date >= m_dateMin)
            && (!m_dateMax.isValid() || date <= m_dateMax);
}

bool SortFilterMilkReceptionTable::isNeedFilterByDelivId() const
{
    return utm::isAutoIncrIdIsValid(m_delivererId);
}


void SortFilterMilkReceptionTable::setSourceModel(QAbstractItemModel *sourceModel)
{
    m_milkReceptionTable = qobject_cast<MilkReceptionTable *>(sourceModel);

    QSortFilterProxyModel::setSourceModel(sourceModel);
}

void SortFilterMilkReceptionTable::setDatesBetween(const QDate &dateFrom, const QDate &dateTo)
{
    m_dateMin = dateFrom;
    m_dateMax = dateTo;

    invalidateFilter();
}
