#include "DeliverersSortFilterProxyModel.h"

#include <MilkModel.h>
#include <Locality.h>
#include <TypesConstants.h>
// Qt
#include <QDebug>

USE_DB_NAMESPACE
using DC = DbConstants;
using TC = TypesConstants;


DeliverersSortFilterProxyModel::DeliverersSortFilterProxyModel(QObject *parent):
    MilkSortFilterProxyModel(parent)
{
    m_filterMilkData = std::make_unique<DelivererData>();
}

QString DeliverersSortFilterProxyModel::firstName() const
{
    return filter()->firstName();
}

void DeliverersSortFilterProxyModel::setFirstName(const QString &firstName)
{
    if (this->firstName() == firstName)
        return;

    filter()->setFirstName(firstName);
    emit firstNameChanged(firstName);
    invalidateFilter();
}

QString DeliverersSortFilterProxyModel::lastName() const
{
    return filter()->lastName();
}

void DeliverersSortFilterProxyModel::setLastName(const QString &lastName)
{
    if (this->lastName() == lastName)
        return;

    filter()->setLastName(lastName);
    emit lastNameChanged(lastName);
    invalidateFilter();
}

QString DeliverersSortFilterProxyModel::inn() const
{
    return filter()->inn();
}

void DeliverersSortFilterProxyModel::setInn(const QString &inn)
{
    if (this->inn() == inn)
        return;

    filter()->setInn(inn);
    emit innChanged(inn);
    invalidateFilter();
}

MILK_ID DeliverersSortFilterProxyModel::localityId() const { return filter()->localityId(); }

void DeliverersSortFilterProxyModel::setLocalityId(const MILK_ID localityId)
{
    if (this->localityId() == localityId)
        return;

    filter()->setLocalityId(localityId);
    emit localityIdChanged(localityId);
    invalidateFilter();
}

QString DeliverersSortFilterProxyModel::address() const { return filter()->address(); }

void DeliverersSortFilterProxyModel::setAddress(const QString &address)
{
    if (this->address() == address)
        return;

    filter()->setAddress(address);
    emit addressChanged(address);
    invalidateFilter();
}

QString DeliverersSortFilterProxyModel::phoneNumber() const { return filter()->phoneNumber(); }

void DeliverersSortFilterProxyModel::setPhoneNumber(const QString &phoneNumber)
{
    if (this->phoneNumber() == phoneNumber)
        return;

    filter()->setPhoneNumber(phoneNumber);
    emit phoneNumberChanged(phoneNumber);
    invalidateFilter();
}

bool DeliverersSortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    Q_UNUSED(sourceParent)
    const auto model = qobject_cast<const MilkModel *>(sourceModel());
    const auto sourceItem = static_cast<const Deliverer *>(model->getItemByIndex(sourceRow));
    const auto deliverer = static_cast<const DelivererData *>(m_filterMilkData.get());

    return isFilterAcceptRowById(deliverer->milkId(), sourceItem->milkId()) &&
           isFilterAcceptRowByString(deliverer->firstName(), sourceItem->firstName()) &&
           isFilterAcceptRowByString(deliverer->lastName(), sourceItem->lastName()) &&
           isFilterAcceptRowById(deliverer->localityId(),
                                 sourceItem->locality() ? sourceItem->locality()->milkId() : TC::DEFAULT_ID) &&
           isFilterAcceptRowByString(deliverer->inn(), sourceItem->inn()) &&
           isFilterAcceptRowByString(deliverer->address(), sourceItem->address()) &&
           isFilterAcceptRowByString(deliverer->phoneNumber(), sourceItem->phoneNumber());
}

bool DeliverersSortFilterProxyModel::lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const
{
    QVariant leftData = sourceModel()->data(sourceLeft);
    QVariant rightData = sourceModel()->data(sourceRight);

    if (leftData.type() == QVariant::String) {
        return leftData.toString() < rightData.toString();
    } else if (leftData.type() == QVariant::Int) {
        return leftData.toInt() < rightData.toInt();
    }

    return QSortFilterProxyModel::lessThan(sourceLeft, sourceRight);
}

DelivererData *DeliverersSortFilterProxyModel::filter() const
{
    return static_cast<DelivererData *>(m_filterMilkData.get());
}

void DeliverersSortFilterProxyModel::resetFilter()
{
    base::resetFilter();
    emit firstNameChanged(firstName());
    emit lastNameChanged(lastName());
    emit innChanged(inn());
    emit localityIdChanged(localityId());
    emit addressChanged(address());
    emit phoneNumberChanged(phoneNumber());
}
