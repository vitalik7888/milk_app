#ifndef MILKRECEPTIONSORTFILTERPROXYMODEL_H
#define MILKRECEPTIONSORTFILTERPROXYMODEL_H

#include "MilkSortFilterProxyModel.h"
#include "MilkReception.h"

DB_BEGIN_NAMESPACE


class DBLIBRARYSHARED_EXPORT MilkReceptionSortFilterProxyModel : public MilkSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(int milkReceptionId READ milkReceptionId WRITE setMilkReceptionId NOTIFY milkReceptionIdChanged)
    Q_PROPERTY(int delivererId READ delivererId WRITE setDelivererId NOTIFY delivererIdChanged)
    Q_PROPERTY(int milkPointId READ milkPointId WRITE setMilkPointId NOTIFY milkPointIdChanged)
    Q_PROPERTY(QDate minDate READ minimumDate WRITE setMinimumDate NOTIFY minimumDateChanged)
    Q_PROPERTY(QDate maxDate READ maximumDate WRITE setMaximumDate NOTIFY maximumDateChanged)

public:
    explicit MilkReceptionSortFilterProxyModel(QObject *parent = nullptr);

    int milkReceptionId() const { return m_milkReceptionId; }
    int delivererId() const { return m_delivererId; }
    int milkPointId() const { return m_milkPointId; }
    QDate minimumDate() const { return m_minDate; }
    QDate maximumDate() const { return m_maxDate; }

public slots:
    void setMilkReceptionId(int milkReceptionId);
    void setDelivererId(int delivererId);
    void setMilkPointId(int milkPointId);
    void setMinimumDate(const QDate &date);
    void setMaximumDate(const QDate &date);
    void reset();

signals:
    void milkReceptionIdChanged(int milkReceptionId);
    void delivererIdChanged(int delivererId);
    void milkPointIdChanged(int milkPointId);
    void minimumDateChanged(QDate minDate);
    void maximumDateChanged(QDate maxDate);

protected:
    virtual bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const Q_DECL_OVERRIDE;
    virtual bool lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const Q_DECL_OVERRIDE;

private:
    int m_milkReceptionId;
    int m_delivererId;
    int m_milkPointId;
    QDate m_minDate;
    QDate m_maxDate;

    bool isFilterAcceptRowById(const int id) const;
    bool isFilterAcceptRowByDelivererId(const int delivererId) const;
    bool isFilterAcceptRowByMilkPointId(const int milkPointId) const;
    bool dateInRange(const QDate &date) const;
};

DB_END_NAMESPACE

#endif // MILKRECEPTIONSORTFILTERPROXYMODEL_H
