#include "DeliverersSortFilterProxyModel.h"

#include "Locality.h"
// Qt
#include <QDebug>

USE_DB_NAMESPACE
using DC = DbConstants;


DeliverersSortFilterProxyModel::DeliverersSortFilterProxyModel(QObject *parent):
    MilkSortFilterProxyModel(parent)
{
    m_deliverer = new Deliverer(this);
    m_deliverer->setLocality(new Locality(m_deliverer));
}

void DeliverersSortFilterProxyModel::resetFilter()
{
    if (m_isDelivererDynamicFilterEnabled) delivererDisconnect();
    auto locality = m_deliverer->locality();
    locality->reset();
    m_deliverer->reset();
    m_deliverer->setLocality(locality);
    if (m_isDelivererDynamicFilterEnabled) delivererConnect();

    invalidateTheFilter();
}

void DeliverersSortFilterProxyModel::setDelivererDynamicFilter(bool isEnable)
{
    if (m_isDelivererDynamicFilterEnabled == isEnable)
        return;

    m_isDelivererDynamicFilterEnabled = isEnable;
    m_isDelivererDynamicFilterEnabled ? delivererConnect() : delivererDisconnect();
    emit delivererDynamicFilterChanged(m_isDelivererDynamicFilterEnabled);
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

    if (leftData.type() == QVariant::String){
        return leftData.toString() < rightData.toString();
    } else if (leftData.type() == QVariant::Int){
        return leftData.toInt() < rightData.toInt();
    }

    return QSortFilterProxyModel::lessThan(sourceLeft, sourceRight);
}

DelivererData DeliverersSortFilterProxyModel::getDelivererFromSourceModel(int sourceRow, const QModelIndex &sourceParent) const
{
    const QModelIndex indexId = sourceModel()->index(sourceRow, DC::TD_ID, sourceParent),
            indexFirstName = sourceModel()->index(sourceRow, DC::TD_FIRST_NAME, sourceParent),
            indexLastName = sourceModel()->index(sourceRow, DC::TD_LAST_NAME, sourceParent),
            indexInn = sourceModel()->index(sourceRow, DC::TD_INN, sourceParent),
            indexAddress = sourceModel()->index(sourceRow, DC::TD_ADDRESS, sourceParent),
            indexLocalityId = sourceModel()->index(sourceRow, DC::TD_LOCALITY_ID, sourceParent),
            indexPhoneNumber = sourceModel()->index(sourceRow, DC::TD_PHONE_NUMBER, sourceParent);

    return {
        sourceModel()->data(indexId).toInt(),
                sourceModel()->data(indexFirstName).toString(),
                sourceModel()->data(indexLastName).toString(),
                sourceModel()->data(indexLocalityId).toInt(),
                sourceModel()->data(indexInn).toString(),
                sourceModel()->data(indexAddress).toString(),
                sourceModel()->data(indexPhoneNumber).toString()
    };
}

void DeliverersSortFilterProxyModel::delivererConnect()
{
    connect(m_deliverer, &Deliverer::idChanged, this, &DeliverersSortFilterProxyModel::invalidateTheFilter);
    connect(m_deliverer, &Deliverer::firstNameChanged, this, &DeliverersSortFilterProxyModel::invalidateTheFilter);
    connect(m_deliverer, &Deliverer::lastNameChanged, this, &DeliverersSortFilterProxyModel::invalidateTheFilter);
    connect(m_deliverer, &Deliverer::innChanged, this, &DeliverersSortFilterProxyModel::invalidateTheFilter);
    connect(m_deliverer, &Deliverer::addressChanged, this, &DeliverersSortFilterProxyModel::invalidateTheFilter);
    connect(m_deliverer, &Deliverer::phoneNumberChanged, this, &DeliverersSortFilterProxyModel::invalidateTheFilter);
    connect(m_deliverer->locality(), &Locality::idChanged, this, &DeliverersSortFilterProxyModel::invalidateTheFilter);
}

void DeliverersSortFilterProxyModel::delivererDisconnect()
{
    disconnect(m_deliverer, &Deliverer::idChanged, this, &DeliverersSortFilterProxyModel::invalidateTheFilter);
    disconnect(m_deliverer, &Deliverer::firstNameChanged, this, &DeliverersSortFilterProxyModel::invalidateTheFilter);
    disconnect(m_deliverer, &Deliverer::lastNameChanged, this, &DeliverersSortFilterProxyModel::invalidateTheFilter);
    disconnect(m_deliverer, &Deliverer::innChanged, this, &DeliverersSortFilterProxyModel::invalidateTheFilter);
    disconnect(m_deliverer, &Deliverer::addressChanged, this, &DeliverersSortFilterProxyModel::invalidateTheFilter);
    disconnect(m_deliverer, &Deliverer::phoneNumberChanged, this, &DeliverersSortFilterProxyModel::invalidateTheFilter);
    disconnect(m_deliverer->locality(), &Locality::idChanged, this, &DeliverersSortFilterProxyModel::invalidateTheFilter);
}

bool DeliverersSortFilterProxyModel::isFilterAcceptRowById(const int id) const
{
    return m_deliverer->id() <= 0 ? true : m_deliverer->id() == id;
}

bool DeliverersSortFilterProxyModel::isFilterAcceptRowByFName(const QString &name) const
{
    return m_deliverer->firstName().isEmpty() ? true : name.contains(m_deliverer->firstName());
}

bool DeliverersSortFilterProxyModel::isFilterAcceptRowByLName(const QString &name) const
{
    return m_deliverer->lastName().isEmpty() ? true : name.contains(m_deliverer->lastName());
}

bool DeliverersSortFilterProxyModel::isFilterAcceptRowByInn(const QString &inn) const
{
    return m_deliverer->inn().isEmpty() ? true : inn.contains(m_deliverer->inn());
}

bool DeliverersSortFilterProxyModel::isFilterAcceptRowByAddress(const QString &address) const
{
    return m_deliverer->address().isEmpty() ? true : address.contains(m_deliverer->address());
}

bool DeliverersSortFilterProxyModel::isFilterAcceptRowByPhoneNumber(const QString &phoneNumber) const
{
    return m_deliverer->phoneNumber().isEmpty() ? true : phoneNumber.contains(m_deliverer->phoneNumber());
}

bool DeliverersSortFilterProxyModel::isFilterAcceptRowByLocalityId(const int localityId) const
{
    if (!m_deliverer->locality())
        return true;

    return m_deliverer->locality()->id() <= 0 ? true : m_deliverer->locality()->id() == localityId;
}

bool DeliverersSortFilterProxyModel::isFilterAcceptRowByDeliverer(const DelivererData &data) const
{
    return isFilterAcceptRowById(data.id()) && isFilterAcceptRowByFName(data.firstName()) &&
            isFilterAcceptRowByLName(data.lastName()) && isFilterAcceptRowByInn(data.inn()) &&
            isFilterAcceptRowByAddress(data.address()) && isFilterAcceptRowByPhoneNumber(data.phoneNumber()) &&
            isFilterAcceptRowByLocalityId(data.localityId());
}

void DeliverersSortFilterProxyModel::invalidateTheFilter()
{
    invalidateFilter();
}
