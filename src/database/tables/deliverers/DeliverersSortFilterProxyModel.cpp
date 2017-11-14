#include "DeliverersSortFilterProxyModel.h"

#include "locality.h"
// Qt
#include <QDebug>

USE_DB_NAMESPACE

using Columns = DeliverersTableColumns;


DeliverersSortFilterProxyModel::DeliverersSortFilterProxyModel(QObject *parent):
    QSortFilterProxyModel(parent)
{
    m_deliverer = new Deliverer(this);
}

void DeliverersSortFilterProxyModel::enableDelivererDynamicFilter(bool isEnable)
{
    m_isDelivererDynamicFilterEnabled = isEnable;
    m_isDelivererDynamicFilterEnabled ? delivererConnect() : delivererDisconnect();
}

void DeliverersSortFilterProxyModel::resetFilter()
{
    if (m_isDelivererDynamicFilterEnabled)
        delivererDisconnect();

    m_deliverer->setId(-1);
    m_deliverer->setName({});
    m_deliverer->setInn(-1);
    m_deliverer->setAddress({});
    m_deliverer->setPhoneNumber({});
    m_deliverer->setLocality(Q_NULLPTR);

    if (m_isDelivererDynamicFilterEnabled)
        delivererConnect();

    invalidateTheFilter();
}

bool DeliverersSortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    const auto deliverer = getDelivererFromSourceModel(sourceRow, sourceParent);

    return isFilterAcceptRowByDeliverer(deliverer);
}

bool DeliverersSortFilterProxyModel::lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const
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

DelivererData DeliverersSortFilterProxyModel::getDelivererFromSourceModel(int sourceRow, const QModelIndex &sourceParent) const
{
    const QModelIndex indexId = sourceModel()->index(sourceRow, Columns::DT_ID, sourceParent),
            indexName = sourceModel()->index(sourceRow, Columns::DT_NAME, sourceParent),
            indexInn = sourceModel()->index(sourceRow, Columns::DT_INN, sourceParent),
            indexAddress = sourceModel()->index(sourceRow, Columns::DT_ADDRESS, sourceParent),
            indexLocalityId = sourceModel()->index(sourceRow, Columns::DT_LOCALITY_ID, sourceParent),
            indexPhoneNumber = sourceModel()->index(sourceRow, Columns::DT_PHONE_NUMBER, sourceParent);

    return {
        sourceModel()->data(indexId).toLongLong(),
                sourceModel()->data(indexName).toString(),
                sourceModel()->data(indexLocalityId).toLongLong(),
                sourceModel()->data(indexInn).toLongLong(),
                sourceModel()->data(indexAddress).toString(),
                sourceModel()->data(indexPhoneNumber).toString()
    };
}

void DeliverersSortFilterProxyModel::delivererConnect()
{
    connect(m_deliverer, &Deliverer::idChanged, this, &DeliverersSortFilterProxyModel::invalidateTheFilter);
    connect(m_deliverer, &Deliverer::nameChanged, this, &DeliverersSortFilterProxyModel::invalidateTheFilter);
    connect(m_deliverer, &Deliverer::innChanged, this, &DeliverersSortFilterProxyModel::invalidateTheFilter);
    connect(m_deliverer, &Deliverer::addressChanged, this, &DeliverersSortFilterProxyModel::invalidateTheFilter);
    connect(m_deliverer, &Deliverer::phoneNumberChanged, this, &DeliverersSortFilterProxyModel::invalidateTheFilter);
    connect(m_deliverer, &Deliverer::localityChanged, this, &DeliverersSortFilterProxyModel::invalidateTheFilter);
}

void DeliverersSortFilterProxyModel::delivererDisconnect()
{
    disconnect(m_deliverer, &Deliverer::idChanged, this, &DeliverersSortFilterProxyModel::invalidateTheFilter);
    disconnect(m_deliverer, &Deliverer::nameChanged, this, &DeliverersSortFilterProxyModel::invalidateTheFilter);
    disconnect(m_deliverer, &Deliverer::innChanged, this, &DeliverersSortFilterProxyModel::invalidateTheFilter);
    disconnect(m_deliverer, &Deliverer::addressChanged, this, &DeliverersSortFilterProxyModel::invalidateTheFilter);
    disconnect(m_deliverer, &Deliverer::phoneNumberChanged, this, &DeliverersSortFilterProxyModel::invalidateTheFilter);
    disconnect(m_deliverer, &Deliverer::localityChanged, this, &DeliverersSortFilterProxyModel::invalidateTheFilter);
}

bool DeliverersSortFilterProxyModel::isFilterAcceptRowById(const milk_id id) const
{
    return m_deliverer->id() <= 0 ? true : m_deliverer->id() == id;
}

bool DeliverersSortFilterProxyModel::isFilterAcceptRowByName(const QString &name) const
{
    return m_deliverer->name().isEmpty() ? true : name.contains(m_deliverer->name());
}

bool DeliverersSortFilterProxyModel::isFilterAcceptRowByInn(const milk_id inn) const
{
    return m_deliverer->inn() == -1 ? true : m_deliverer->inn() == inn;
}

bool DeliverersSortFilterProxyModel::isFilterAcceptRowByAddress(const QString &address) const
{
    return m_deliverer->address().isEmpty() ? true : address.contains(m_deliverer->address());
}

bool DeliverersSortFilterProxyModel::isFilterAcceptRowByPhoneNumber(const QString &phoneNumber) const
{
    return m_deliverer->phoneNumber().isEmpty() ? true : phoneNumber.contains(m_deliverer->phoneNumber());
}

bool DeliverersSortFilterProxyModel::isFilterAcceptRowByLocalityId(const milk_id localityId) const
{
    return m_deliverer->locality() == Q_NULLPTR ? true : m_deliverer->locality()->id() == localityId;
}

bool DeliverersSortFilterProxyModel::isFilterAcceptRowByDeliverer(const DelivererData &data) const
{
    return isFilterAcceptRowById(data.id()) && isFilterAcceptRowByName(data.name()) &&
            isFilterAcceptRowByInn(data.inn()) && isFilterAcceptRowByAddress(data.address()) &&
            isFilterAcceptRowByPhoneNumber(data.phoneNumber()) && isFilterAcceptRowByLocalityId(data.localityId());
}

void DeliverersSortFilterProxyModel::invalidateTheFilter()
{
    invalidateFilter();
}
