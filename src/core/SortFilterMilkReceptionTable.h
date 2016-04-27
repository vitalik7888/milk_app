#ifndef SORTFILTERMILKRECEPTIONTABLE_H
#define SORTFILTERMILKRECEPTIONTABLE_H

#include "QSortFilterProxyModel"

#include <QDate>

class MilkReceptionTable;


class SortFilterMilkReceptionTable : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    SortFilterMilkReceptionTable(QObject *parent = nullptr);

    void setSourceModel(QAbstractItemModel *sourceModel) Q_DECL_OVERRIDE;

    void setDatesBetween(const QDate &dateFrom, const QDate &dateTo);

    /*QDate filterMinimumDate() const { return m_dateMin; }
    void setFilterMinimumDate(const QDate &date);

    QDate filterMaximumDate() const { return m_dateMax; }
    void setFilterMaximumDate(const QDate &date);*/

    qlonglong filterDelivererId() const { return m_delivererId; }
    void setFilterDelivererId(const qlonglong &filterDelivererId);

    qlonglong filterMilkPointId() const { return m_milkPointId; }
    void setFilterMilkPointId(const qlonglong &filterMilkPointId);

private:
    MilkReceptionTable *m_milkReceptionTable;

    qlonglong m_delivererId;
    qlonglong m_milkPointId;
    QDate m_dateMin;
    QDate m_dateMax;

    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const Q_DECL_OVERRIDE;
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const Q_DECL_OVERRIDE;

    bool dateBetween(const QDate &date) const;
    bool isNeedFilterByDelivId() const;
};

#endif // SORTFILTERMILKRECEPTIONTABLE_H
