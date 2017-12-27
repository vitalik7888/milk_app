#include "MilkPointsSortFilterProxyModel.h"

#include "MilkPoint.h"
#include <MilkPointsModel.h>
#include <Locality.h>
#include <TypesConstants.h>
// Qt
#include <QDebug>


USE_DB_NAMESPACE
using DC = DbConstants;
using TC = TypesConstants;


MilkPointsSortFilterProxyModel::MilkPointsSortFilterProxyModel(QObject *parent) :
    MilkSortFilterProxyModel(parent)
{
    m_filterMilkData = std::make_unique<MilkPointData>();
}

MILK_ID MilkPointsSortFilterProxyModel::localityId() const
{
    return filter()->localityId();
}

QString MilkPointsSortFilterProxyModel::name() const
{
    return filter()->name();
}

void MilkPointsSortFilterProxyModel::setName(const QString &name)
{
    if (this->name() == name)
        return;

    filter()->setName(name);
    emit nameChanged(name);
    invalidateFilter();
}

QString MilkPointsSortFilterProxyModel::description()
{
    return filter()->description();
}

void MilkPointsSortFilterProxyModel::setDescription(const QString &description)
{
    if (this->description() == description)
        return;

    filter()->setDescription(description);
    emit descriptionChanged(description);
    invalidateFilter();
}

void MilkPointsSortFilterProxyModel::setLocalityId(const MILK_ID localityId)
{
    if (this->localityId() == localityId)
        return;

    filter()->setLocalityId(localityId);
    emit localityIdChanged(localityId);
    invalidateFilter();
}

bool MilkPointsSortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    Q_UNUSED(sourceParent)
    const auto model = qobject_cast<const MilkPointsModel *>(sourceModel());
    const auto sourceItem = static_cast<const MilkPoint *>(model->getItemByIndex(sourceRow));
    const auto milkPoint = static_cast<const MilkPointData *>(m_filterMilkData.get());

    return isFilterAcceptRowById(milkPoint->milkId(), sourceItem->milkId()) &&
            isFilterAcceptRowById(milkPoint->localityId(),
                                  sourceItem->locality() ? sourceItem->locality()->milkId() : TC::DEFAULT_ID) &&
            isFilterAcceptRowByString(milkPoint->name(), sourceItem->name()) &&
            isFilterAcceptRowByString(milkPoint->description(), sourceItem->description());
}

bool MilkPointsSortFilterProxyModel::lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const
{
    const auto leftData = sourceModel()->data(sourceLeft);
    const auto rightData = sourceModel()->data(sourceRight);

    if (leftData.type() == QVariant::String) {
        return leftData.toString() < rightData.toString();
    } else if (leftData.type() == QVariant::Int) {
        return leftData.toInt() < rightData.toInt();
    }

    return QSortFilterProxyModel::lessThan(sourceLeft, sourceRight);
}

MilkPointData *MilkPointsSortFilterProxyModel::filter() const
{
    return static_cast<MilkPointData *>(m_filterMilkData.get());
}

void MilkPointsSortFilterProxyModel::resetFilter()
{
    base::resetFilter();
    emit localityIdChanged(localityId());
    emit nameChanged(name());
    emit descriptionChanged(description());
}
