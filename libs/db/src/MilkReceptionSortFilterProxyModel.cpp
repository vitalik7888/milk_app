#include "MilkReceptionSortFilterProxyModel.h"

#include <MilkModel.h>
#include <MilkReception.h>
#include <Deliverer.h>
#include <MilkPoint.h>
#include <TypesConstants.h>

USE_DB_NAMESPACE

using DC = DbConstants;
using TC = TypesConstants;


MilkReceptionSortFilterProxyModel::MilkReceptionSortFilterProxyModel(QObject *parent) :
    MilkSortFilterProxyModel(parent)
{
    m_filterMilkData = std::make_unique<MilkReceptionData>();
}

MILK_ID MilkReceptionSortFilterProxyModel::delivererId() const
{
    return filter()->delivererId();
}

MILK_ID MilkReceptionSortFilterProxyModel::milkPointId() const
{
    return filter()->milkPointId();
}

QDate MilkReceptionSortFilterProxyModel::minimumDate() const
{
    return m_minDate;
}

QDate MilkReceptionSortFilterProxyModel::maximumDate() const
{
    return m_maxDate;
}

bool MilkReceptionSortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    Q_UNUSED(sourceParent)
    const auto model = qobject_cast<const MilkModel *>(sourceModel());
    const auto sourceItem = static_cast<const MilkReception *>(model->getItemByIndex(sourceRow));
    const auto milkReception = static_cast<const MilkReceptionData *>(m_filterMilkData.get());

    return isFilterAcceptRowById(milkReception->milkId(), sourceItem->milkId()) &&
            isFilterAcceptRowById(milkReception->delivererId(),
                                  sourceItem->deliverer() ? sourceItem->deliverer()->milkId() : TC::DEFAULT_ID) &&
            isFilterAcceptRowById(milkReception->milkPointId(),
                                  sourceItem->milkPoint() ? sourceItem->milkPoint()->milkId() : TC::DEFAULT_ID) &&
            isFilterAcceptRowByDateInRange(sourceItem->deliveryDate(), m_minDate, m_maxDate);
}

bool MilkReceptionSortFilterProxyModel::lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const
{
    const auto leftData = sourceModel()->data(sourceLeft);
    const auto rightData = sourceModel()->data(sourceRight);

    if (leftData.type() == QVariant::String) {
        return leftData.toString() < rightData.toString();
    } else if (leftData.type() == QVariant::Int) {
        return leftData.toInt() < rightData.toInt();
    } else if (leftData.type() == QVariant::Date) {
        return leftData.toDate() < rightData.toDate();
    }

    return QSortFilterProxyModel::lessThan(sourceLeft, sourceRight);
}

MilkReceptionData *MilkReceptionSortFilterProxyModel::filter() const
{
    return static_cast<MilkReceptionData *>(m_filterMilkData.get());
}

void MilkReceptionSortFilterProxyModel::resetFilter()
{
    base::resetFilter();
    emit delivererIdChanged(delivererId());
    emit milkPointIdChanged(milkPointId());
}

void MilkReceptionSortFilterProxyModel::setMilkPointId(const MILK_ID milkPointId)
{
    if (this->milkPointId() == milkPointId)
        return;

    filter()->setMilkPointId(milkPointId);
    emit milkPointIdChanged(milkPointId);
    invalidateFilter();
}

void MilkReceptionSortFilterProxyModel::setDelivererId(const MILK_ID delivererId)
{
    if (this->delivererId() == delivererId)
        return;

    filter()->setDelivererId(delivererId);
    emit delivererIdChanged(delivererId);
    invalidateFilter();
}

void MilkReceptionSortFilterProxyModel::setMinimumDate(const QDate &date)
{
    if (m_minDate == date)
        return;

    m_minDate = date;
    invalidateFilter();
}

void MilkReceptionSortFilterProxyModel::setMaximumDate(const QDate &date)
{
    if (m_maxDate == date)
        return;

    m_maxDate = date;
    invalidateFilter();
}
