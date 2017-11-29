#ifndef MILKPOINTSSORTFILTERPROXYMODEL_H
#define MILKPOINTSSORTFILTERPROXYMODEL_H

#include "DbConstants.h"
#include "MilkPoint.h"
// Qt
#include <QSortFilterProxyModel>

DB_BEGIN_NAMESPACE

class MilkPointsSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(MilkPoint* milkPoint READ milkPoint CONSTANT RESET resetMilkPoint)
    Q_PROPERTY(bool enableMilkPointDynamicFilter READ isMilkPointDynamicFilterEnabled WRITE setMilkPointDynamicFilter NOTIFY MilkPointDynamicFilterChanged)

public:
    explicit MilkPointsSortFilterProxyModel(QObject *parent = nullptr);

    MilkPoint* milkPoint() const { return m_milkPoint; }
    bool isMilkPointDynamicFilterEnabled() const { return m_isMilkPointDynamicFilterEnabled; }

    Q_INVOKABLE int sourceRow(const int row) const;

public slots:
    void invalidateTheFilter();
    void resetMilkPoint();

    void setMilkPointDynamicFilter(bool isEnable);

signals:
    void MilkPointDynamicFilterChanged(bool isEnabled);

protected:
    virtual bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const Q_DECL_OVERRIDE;
    virtual bool lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const Q_DECL_OVERRIDE;

private:
    MilkPoint* m_milkPoint;
    bool m_isMilkPointDynamicFilterEnabled;

    void milkPointConnect();
    void milkPointDisconnect();

    MilkPointData getMilkPointFromSourceModel(int sourceRow, const QModelIndex &sourceParent) const;

    bool isFilterAcceptRowById(const DbConstants::milk_id id) const;
    bool isFilterAcceptRowByLocalityId(const DbConstants::milk_id localityId) const;
    bool isFilterAcceptRowByName(const QString &name) const;
    bool isFilterAcceptRowByDescription(const QString &description) const;
    bool isFilterAcceptRowByMilkPoint(const MilkPointData &data) const;
};

DB_END_NAMESPACE

#endif // MILKPOINTSSORTFILTERPROXYMODEL_H
