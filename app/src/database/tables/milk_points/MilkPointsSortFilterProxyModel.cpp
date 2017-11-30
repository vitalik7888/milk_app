#include "MilkPointsSortFilterProxyModel.h"

#include "Locality.h"
// Qt
#include <QDebug>


USE_DB_NAMESPACE
using DC = DbConstants;


MilkPointsSortFilterProxyModel::MilkPointsSortFilterProxyModel(QObject *parent) :
    MilkSortFilterProxyModel(parent)
{
    m_milkPoint = new MilkPoint(this);
    m_milkPoint->setLocality(new Locality(m_milkPoint));
}

void MilkPointsSortFilterProxyModel::invalidateTheFilter()
{
    invalidateFilter();
}

void MilkPointsSortFilterProxyModel::resetMilkPoint()
{
    if (m_isMilkPointDynamicFilterEnabled) milkPointConnect();
    auto locality = m_milkPoint->locality();
    locality->reset();
    m_milkPoint->reset();
    m_milkPoint->setLocality(locality);
    if (m_isMilkPointDynamicFilterEnabled) milkPointDisconnect();

    invalidateTheFilter();
}

void MilkPointsSortFilterProxyModel::setMilkPointDynamicFilter(bool isEnable)
{
    if (m_isMilkPointDynamicFilterEnabled == isEnable)
        return;

    m_isMilkPointDynamicFilterEnabled = isEnable;
    m_isMilkPointDynamicFilterEnabled ? milkPointConnect() : milkPointDisconnect();
    emit MilkPointDynamicFilterChanged(m_isMilkPointDynamicFilterEnabled);
}

void MilkPointsSortFilterProxyModel::milkPointConnect()
{
    connect(m_milkPoint, &MilkPoint::idChanged, this, &MilkPointsSortFilterProxyModel::invalidateTheFilter);
    connect(m_milkPoint, &MilkPoint::nameChanged, this, &MilkPointsSortFilterProxyModel::invalidateTheFilter);
    connect(m_milkPoint, &MilkPoint::descriptionChanged, this, &MilkPointsSortFilterProxyModel::invalidateTheFilter);
    connect(m_milkPoint->locality(), &Locality::idChanged, this, &MilkPointsSortFilterProxyModel::invalidateTheFilter);
}

void MilkPointsSortFilterProxyModel::milkPointDisconnect()
{
    disconnect(m_milkPoint, &MilkPoint::idChanged, this, &MilkPointsSortFilterProxyModel::invalidateTheFilter);
    disconnect(m_milkPoint, &MilkPoint::nameChanged, this, &MilkPointsSortFilterProxyModel::invalidateTheFilter);
    disconnect(m_milkPoint, &MilkPoint::descriptionChanged, this, &MilkPointsSortFilterProxyModel::invalidateTheFilter);
    disconnect(m_milkPoint->locality(), &Locality::idChanged, this, &MilkPointsSortFilterProxyModel::invalidateTheFilter);
}

MilkPointData MilkPointsSortFilterProxyModel::getMilkPointFromSourceModel(int sourceRow, const QModelIndex &sourceParent) const
{
    const QModelIndex indexId = sourceModel()->index(sourceRow, DC::TMP_ID, sourceParent),
            indexLocalityId = sourceModel()->index(sourceRow, DC::TMP_LOCALITY_ID, sourceParent),
            indexName = sourceModel()->index(sourceRow, DC::TMP_NAME, sourceParent),
            indexDescription = sourceModel()->index(sourceRow, DC::TMP_DESCRIPTION, sourceParent);

    return MilkPointData(
                sourceModel()->data(indexId).toLongLong(),
                sourceModel()->data(indexLocalityId).toLongLong(),
                sourceModel()->data(indexName).toString(),
                sourceModel()->data(indexDescription).toString()
                );
}

bool MilkPointsSortFilterProxyModel::isFilterAcceptRowById(const DbConstants::milk_id id) const
{
    return m_milkPoint->id() <= 0 ? true : m_milkPoint->id() == id;
}

bool MilkPointsSortFilterProxyModel::isFilterAcceptRowByLocalityId(const DbConstants::milk_id localityId) const
{
    if (!m_milkPoint->locality())
        return true;

    return m_milkPoint->locality()->id() <= 0 ? true : m_milkPoint->locality()->id() == localityId;
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
    return isFilterAcceptRowById(data.id()) && isFilterAcceptRowByLocalityId(data.localityId()) &&
            isFilterAcceptRowByName(data.name()) && isFilterAcceptRowByDescription(data.description());
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
