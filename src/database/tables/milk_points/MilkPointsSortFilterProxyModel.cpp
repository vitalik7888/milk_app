#include "MilkPointsSortFilterProxyModel.h"

USE_DB_NAMESPACE

using COLUMNS = MilkPointsTableColumns;


MilkPointsSortFilterProxyModel::MilkPointsSortFilterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
    m_milkPoint = new MilkPoint(this);
}

void MilkPointsSortFilterProxyModel::invalidateTheFilter()
{
    invalidateFilter();
}

void MilkPointsSortFilterProxyModel::enableMilkPointDynamicFilter(bool isEnable)
{
    m_isMilkPointDynamicFilterEnabled = isEnable;
    m_isMilkPointDynamicFilterEnabled ? milkPointConnect() : milkPointDisconnect();
}

void MilkPointsSortFilterProxyModel::resetMilkPoint()
{
    if (m_isMilkPointDynamicFilterEnabled) milkPointConnect();
    m_milkPoint->reset();
    if (m_isMilkPointDynamicFilterEnabled) milkPointDisconnect();

    invalidateTheFilter();
}

void MilkPointsSortFilterProxyModel::milkPointConnect()
{
    connect(m_milkPoint, &MilkPoint::idChanged, this, &MilkPointsSortFilterProxyModel::invalidateTheFilter);
    connect(m_milkPoint, &MilkPoint::nameChanged, this, &MilkPointsSortFilterProxyModel::invalidateTheFilter);
    connect(m_milkPoint, &MilkPoint::descriptionChanged, this, &MilkPointsSortFilterProxyModel::invalidateTheFilter);
}

void MilkPointsSortFilterProxyModel::milkPointDisconnect()
{
    disconnect(m_milkPoint, &MilkPoint::idChanged, this, &MilkPointsSortFilterProxyModel::invalidateTheFilter);
    disconnect(m_milkPoint, &MilkPoint::nameChanged, this, &MilkPointsSortFilterProxyModel::invalidateTheFilter);
    disconnect(m_milkPoint, &MilkPoint::descriptionChanged, this, &MilkPointsSortFilterProxyModel::invalidateTheFilter);
}

MilkPointData MilkPointsSortFilterProxyModel::getMilkPointFromSourceModel(int sourceRow, const QModelIndex &sourceParent) const
{
    const QModelIndex indexId = sourceModel()->index(sourceRow, COLUMNS::MPT_ID, sourceParent),
            indexName = sourceModel()->index(sourceRow, COLUMNS::MPT_NAME, sourceParent),
            indexDescription = sourceModel()->index(sourceRow, COLUMNS::MPT_DESCRIPTION, sourceParent);

    return MilkPointData(
                sourceModel()->data(indexId).toLongLong(),
                -1,
                sourceModel()->data(indexName).toString(),
                sourceModel()->data(indexDescription).toString()
                );
}

bool MilkPointsSortFilterProxyModel::isFilterAcceptRowById(const milk_id id) const
{
    return m_milkPoint->id() <= 0 ? true : m_milkPoint->id() == id;
}

bool MilkPointsSortFilterProxyModel::isFilterAcceptRowByName(const QString &name) const
{
    return m_milkPoint->name().isEmpty() ? true : name.contains(m_milkPoint->name());
}

bool MilkPointsSortFilterProxyModel::isFilterAcceptRowByDescription(const QString &description) const
{
    return m_milkPoint->description().isEmpty() ? true : description.contains(m_milkPoint->description());
}

bool MilkPointsSortFilterProxyModel::isFilterAcceptRowByMilkPoint(const MilkPointData &data) const
{
    return isFilterAcceptRowById(data.id()) && isFilterAcceptRowByName(data.name())
            && isFilterAcceptRowByDescription(data.description());
}

bool MilkPointsSortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    const auto data = getMilkPointFromSourceModel(source_row, source_parent);

    return isFilterAcceptRowByMilkPoint(data);
}

bool MilkPointsSortFilterProxyModel::lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const
{
    QVariant leftData = sourceModel()->data(sourceLeft);
    QVariant rightData = sourceModel()->data(sourceRight);

    if (leftData.type() == QVariant::LongLong){
        return leftData.toLongLong() < rightData.toLongLong();
    } else if (leftData.type() == QVariant::String){
        return leftData.toString() < rightData.toString();
    }

    return QSortFilterProxyModel::lessThan(sourceLeft, sourceRight);
}
