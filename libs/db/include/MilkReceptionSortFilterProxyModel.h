#ifndef MILKRECEPTIONSORTFILTERPROXYMODEL_H
#define MILKRECEPTIONSORTFILTERPROXYMODEL_H

#include "MilkSortFilterProxyModel.h"
// Qt
#include <QDate>

class MilkReceptionData;
DB_BEGIN_NAMESPACE

class DBLIBRARYSHARED_EXPORT MilkReceptionSortFilterProxyModel : public MilkSortFilterProxyModel
{
    using base = MilkSortFilterProxyModel;
    Q_OBJECT
    Q_PROPERTY(int delivererId READ delivererId WRITE setDelivererId NOTIFY delivererIdChanged)
    Q_PROPERTY(int milkPointId READ milkPointId WRITE setMilkPointId NOTIFY milkPointIdChanged)
    Q_PROPERTY(QDate minDate READ minimumDate WRITE setMinimumDate NOTIFY minimumDateChanged)
    Q_PROPERTY(QDate maxDate READ maximumDate WRITE setMaximumDate NOTIFY maximumDateChanged)

public:
    explicit MilkReceptionSortFilterProxyModel(QObject *parent = nullptr);

    MILK_ID delivererId() const;
    MILK_ID milkPointId() const;
    QDate minimumDate() const;
    QDate maximumDate() const;

public slots:
    void setDelivererId(const MILK_ID delivererId);
    void setMilkPointId(const MILK_ID milkPointId);
    void setMinimumDate(const QDate &minDate);
    void setMaximumDate(const QDate &maxDate);
    void resetFilter() Q_DECL_OVERRIDE;

signals:
    void delivererIdChanged(const MILK_ID delivererId);
    void milkPointIdChanged(const MILK_ID milkPointId);
    void minimumDateChanged(const QDate &minDate);
    void maximumDateChanged(const QDate &maxDate);

protected:
    virtual bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const Q_DECL_OVERRIDE;
    virtual bool lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const Q_DECL_OVERRIDE;

private:
    QDate m_minDate;
    QDate m_maxDate;

    MilkReceptionData *filter() const;
};

DB_END_NAMESPACE

#endif // MILKRECEPTIONSORTFILTERPROXYMODEL_H
