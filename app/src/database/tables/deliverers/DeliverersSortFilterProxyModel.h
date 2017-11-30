#ifndef DELIVERERSSORTFILTERPROXYMODEL_H
#define DELIVERERSSORTFILTERPROXYMODEL_H

#include "Deliverer.h"
#include "base/MilkSortFilterProxyModel.h"

DB_BEGIN_NAMESPACE


class DeliverersSortFilterProxyModel : public MilkSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(Deliverer* deliverer READ deliverer CONSTANT RESET resetFilter)
    Q_PROPERTY(bool enableDelivererDynamicFilter READ isDelivererDynamicFilterEnabled WRITE setDelivererDynamicFilter NOTIFY delivererDynamicFilterChanged)

public:
    DeliverersSortFilterProxyModel(QObject *parent = Q_NULLPTR);

    Deliverer* deliverer() const { return m_deliverer; }
    bool isDelivererDynamicFilterEnabled() const { return m_isDelivererDynamicFilterEnabled; }

public slots:
    void invalidateTheFilter();
    void resetFilter();
    void setDelivererDynamicFilter(bool isEnable);

signals:
    void delivererDynamicFilterChanged(bool enableDelivererDynamicFilter);

protected:
    virtual bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const Q_DECL_OVERRIDE;
    virtual bool lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const Q_DECL_OVERRIDE;

private:
    Deliverer* m_deliverer;
    bool m_isDelivererDynamicFilterEnabled;

    DelivererData getDelivererFromSourceModel(int sourceRow, const QModelIndex &sourceParent) const;

    void delivererConnect();
    void delivererDisconnect();

    bool isFilterAcceptRowById(const int id) const;
    bool isFilterAcceptRowByName(const QString &name) const;
    bool isFilterAcceptRowByInn(const QString &inn) const;
    bool isFilterAcceptRowByAddress(const QString &address) const;
    bool isFilterAcceptRowByPhoneNumber(const QString &phoneNumber) const;
    bool isFilterAcceptRowByLocalityId(const int localityId) const;
    bool isFilterAcceptRowByDeliverer(const DelivererData &data) const;
};

DB_END_NAMESPACE

#endif // DELIVERERSSORTFILTERPROXYMODEL_H
