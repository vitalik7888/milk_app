#ifndef MILKSORTFILTERPROXYMODEL_H
#define MILKSORTFILTERPROXYMODEL_H

#include "DbConstants.h"
#include <MilkBaseItem.h>
#include <memory>
// Qt
#include <QSortFilterProxyModel>

class QDate;

DB_BEGIN_NAMESPACE


class DBLIBRARYSHARED_EXPORT MilkSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(MILK_ID milkId READ milkId WRITE setMilkId NOTIFY milkIdChanged)

public:
    explicit MilkSortFilterProxyModel(QObject *parent = nullptr);

    MILK_ID milkId() const;

public slots:
    void setMilkId(const MILK_ID id);
    virtual void resetFilter();

signals:
    void milkIdChanged(MILK_ID milkId);

protected:
    std::unique_ptr<MilkBaseItem> m_filterMilkData;

    bool isFilterAcceptRowById(const MILK_ID left, const MILK_ID right) const;
    bool isFilterAcceptRowByString(const QString &left, const QString &right) const;
    bool isFilterAcceptRowByDateInRange(const QDate &date, const QDate &min, const QDate &maxDate) const;
};

DB_END_NAMESPACE

#endif // MILKSORTFILTERPROXYMODEL_H
