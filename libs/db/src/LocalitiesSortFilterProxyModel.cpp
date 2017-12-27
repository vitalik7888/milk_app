#include "LocalitiesSortFilterProxyModel.h"

#include <Locality.h>
#include <MilkModel.h>

USE_DB_NAMESPACE
using DC = DbConstants;


LocalitiesSortFilterProxyModel::LocalitiesSortFilterProxyModel(QObject *parent):
    MilkSortFilterProxyModel(parent)
{
    m_filterMilkData = std::make_unique<Locality>();
}

QString LocalitiesSortFilterProxyModel::name() const
{
    return filter()->name();
}

void LocalitiesSortFilterProxyModel::setName(const QString &name)
{
    if (this->name() == name)
        return;

    filter()->setName(name);
    emit nameChanged(name);
    invalidateFilter();
}

QString LocalitiesSortFilterProxyModel::description()
{
    return filter()->description();
}

void LocalitiesSortFilterProxyModel::setDescription(const QString &description)
{
    if (this->description() == description)
        return;

    filter()->setDescription(description);
    emit descriptionChanged(description);
    invalidateFilter();
}

bool LocalitiesSortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    Q_UNUSED(sourceParent)
    const auto model = qobject_cast<const MilkModel *>(sourceModel());
    const auto sourceItem = static_cast<const Locality &>(*model->getItemByIndex(sourceRow));
    const auto item = static_cast<const Locality &>(*m_filterMilkData.get());

    return isFilterAcceptRowById(item.milkId(), sourceItem.milkId()) &&
            isFilterAcceptRowByString(item.name(), sourceItem.name()) &&
            isFilterAcceptRowByString(item.description(), sourceItem.description());
}

bool LocalitiesSortFilterProxyModel::lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const
{
    const auto model = qobject_cast<const MilkModel *>(sourceModel());
    const auto leftItem = static_cast<const Locality *>(model->getItemByIndex(sourceLeft.row()));
    const auto rightItem = static_cast<const Locality *>(model->getItemByIndex(sourceRight.row()));

    const auto column = sourceLeft.column();
    switch(column) {
    case DC::TL_ID:
        return leftItem->milkId() < rightItem->milkId();
    case DC::TL_NAME:
        return leftItem->name() < rightItem->name();
    case DC::TL_DESCRIPTION:
        return leftItem->description() < rightItem->description();
    }

    return base::lessThan(sourceLeft, sourceRight);
}

Locality *LocalitiesSortFilterProxyModel::filter() const
{
    return static_cast<Locality *>(m_filterMilkData.get());
}

void LocalitiesSortFilterProxyModel::resetFilter()
{
    base::resetFilter();
    emit nameChanged(name());
    emit descriptionChanged(description());
}
