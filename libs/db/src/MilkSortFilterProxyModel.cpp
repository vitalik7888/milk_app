#include "MilkSortFilterProxyModel.h"

#include "MilkModel.h"
// Qt
#include <QDate>
#include <QDebug>

USE_DB_NAMESPACE
    using DC = DbConstants;


MilkSortFilterProxyModel::MilkSortFilterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent),
    m_filterMilkData(Q_NULLPTR)
{

}

MILK_ID MilkSortFilterProxyModel::milkId() const
{
    return m_filterMilkData->milkId();
}

void MilkSortFilterProxyModel::setMilkId(const MILK_ID id)
{
    if (milkId() == id)
        return;

    m_filterMilkData->setMilkId(id);
    emit milkIdChanged(id);
    invalidateFilter();
}

void MilkSortFilterProxyModel::resetFilter()
{
    m_filterMilkData->reset();
    emit milkIdChanged(milkId());
}

bool MilkSortFilterProxyModel::isFilterAcceptRowById(const MILK_ID left, const MILK_ID right) const
{
    return left <= 0 ? true : left == right;
}

bool MilkSortFilterProxyModel::isFilterAcceptRowByString(const QString &left, const QString &right) const
{
    return left.isEmpty() ? true : right.contains(left);
}

bool MilkSortFilterProxyModel::isFilterAcceptRowByDateInRange(const QDate &date, const QDate &minDate,
                                                              const QDate &maxDate) const
{
    return (!minDate.isValid() || date > minDate) && (!maxDate.isValid() || date < maxDate);
}
