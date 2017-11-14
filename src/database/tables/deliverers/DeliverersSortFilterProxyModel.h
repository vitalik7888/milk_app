#ifndef DELIVERERSSORTFILTERPROXYMODEL_H
#define DELIVERERSSORTFILTERPROXYMODEL_H

#include "dbconstants.h"
#include "deliverer.h"
// Qt
#include <QSortFilterProxyModel>

DB_BEGIN_NAMESPACE


class DeliverersSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(Deliverer* deliverer READ deliverer CONSTANT RESET resetFilter)

public:
    DeliverersSortFilterProxyModel(QObject *parent = Q_NULLPTR);

    Deliverer* deliverer() const { return m_deliverer; }

public slots:
    void invalidateTheFilter();
    void enableDelivererDynamicFilter(bool isEnable);
    void resetFilter();

protected:
    virtual bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const Q_DECL_OVERRIDE;
    virtual bool lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const Q_DECL_OVERRIDE;

private:
    Deliverer* m_deliverer;
    bool m_isDelivererDynamicFilterEnabled;

    DelivererData getDelivererFromSourceModel(int sourceRow, const QModelIndex &sourceParent) const;

    void delivererConnect();
    void delivererDisconnect();

    bool isFilterAcceptRowById(const milk_id id) const;
    bool isFilterAcceptRowByName(const QString &name) const;
    bool isFilterAcceptRowByInn(const milk_id inn) const;
    bool isFilterAcceptRowByAddress(const QString &address) const;
    bool isFilterAcceptRowByPhoneNumber(const QString &phoneNumber) const;
    bool isFilterAcceptRowByLocalityId(const milk_id localityId) const;
    bool isFilterAcceptRowByDeliverer(const DelivererData &data) const;
};

DB_END_NAMESPACE

#endif // DELIVERERSSORTFILTERPROXYMODEL_H
