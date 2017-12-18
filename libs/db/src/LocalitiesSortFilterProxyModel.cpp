#include "LocalitiesSortFilterProxyModel.h"

USE_DB_NAMESPACE
using DC = DbConstants;


LocalitiesSortFilterProxyModel::LocalitiesSortFilterProxyModel(QObject *parent):
    MilkSortFilterProxyModel(parent)
{
    m_locality = new Locality();
}

void LocalitiesSortFilterProxyModel::invalidateTheFilter()
{
    invalidateFilter();
}

void LocalitiesSortFilterProxyModel::resetLocality()
{
    if (m_isLocalityDynamicFilterEnabled) localityDisconnect();

    m_locality->reset();

    if (m_isLocalityDynamicFilterEnabled) localityConnect();

    invalidateTheFilter();
}

void LocalitiesSortFilterProxyModel::setLocalityDynamicFilter(bool isEnable)
{
    if (m_isLocalityDynamicFilterEnabled == isEnable)
        return;

    m_isLocalityDynamicFilterEnabled = isEnable;
    m_isLocalityDynamicFilterEnabled ? localityConnect() : localityDisconnect();
    emit localityDynamicFilterChanged(m_isLocalityDynamicFilterEnabled);
}

void LocalitiesSortFilterProxyModel::localityConnect()
{
    connect(m_locality, &Locality::idChanged, this, &LocalitiesSortFilterProxyModel::invalidateTheFilter);
    connect(m_locality, &Locality::nameChanged, this, &LocalitiesSortFilterProxyModel::invalidateTheFilter);
    connect(m_locality, &Locality::descriptionChanged, this, &LocalitiesSortFilterProxyModel::invalidateTheFilter);
}

void LocalitiesSortFilterProxyModel::localityDisconnect()
{
    disconnect(m_locality, &Locality::idChanged, this, &LocalitiesSortFilterProxyModel::invalidateTheFilter);
    disconnect(m_locality, &Locality::nameChanged, this, &LocalitiesSortFilterProxyModel::invalidateTheFilter);
    disconnect(m_locality, &Locality::descriptionChanged, this, &LocalitiesSortFilterProxyModel::invalidateTheFilter);
}

LocalityData LocalitiesSortFilterProxyModel::getLocalityFromSourceModel(int sourceRow, const QModelIndex &sourceParent) const
{
    const QModelIndex indexId = sourceModel()->index(sourceRow, DC::TL_ID, sourceParent),
            indexName = sourceModel()->index(sourceRow, DC::TL_NAME, sourceParent),
            indexDescription = sourceModel()->index(sourceRow, DC::TL_DESCRIPTION, sourceParent);

    return LocalityData(
                sourceModel()->data(indexId).toInt(),
                sourceModel()->data(indexName).toString(),
                sourceModel()->data(indexDescription).toString()
                );
}

bool LocalitiesSortFilterProxyModel::isFilterAcceptRowById(const int id) const
{
    return m_locality->id() <= 0 ? true : m_locality->id() == id;
}

bool LocalitiesSortFilterProxyModel::isFilterAcceptRowByName(const QString &name) const
{
    return m_locality->name().isEmpty() ? true : name.contains(m_locality->name());
}

bool LocalitiesSortFilterProxyModel::isFilterAcceptRowByDescription(const QString &description) const
{
    return m_locality->description().isEmpty() ? true : description.contains(m_locality->description());
}

bool LocalitiesSortFilterProxyModel::isFilterAcceptRowByLocality(const LocalityData &data) const
{
    return isFilterAcceptRowById(data.id()) && isFilterAcceptRowByName(data.name())
            && isFilterAcceptRowByDescription(data.description());
}

bool LocalitiesSortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    const auto data = getLocalityFromSourceModel(source_row, source_parent);

    return isFilterAcceptRowByLocality(data);
}

bool LocalitiesSortFilterProxyModel::lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const
{
    QVariant leftData = sourceModel()->data(sourceLeft);
    QVariant rightData = sourceModel()->data(sourceRight);

    if (leftData.type() == QVariant::String){
        return leftData.toString() < rightData.toString();
    } else if (leftData.type() == QVariant::Int){
        return leftData.toInt() < rightData.toInt();
    }

    return QSortFilterProxyModel::lessThan(sourceLeft, sourceRight);
}