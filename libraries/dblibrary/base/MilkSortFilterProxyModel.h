#ifndef MILKSORTFILTERPROXYMODEL_H
#define MILKSORTFILTERPROXYMODEL_H

#include "DbConstants.h"
// Qt
#include <QSortFilterProxyModel>

DB_BEGIN_NAMESPACE

class DBLIBRARYSHARED_EXPORT MilkSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit MilkSortFilterProxyModel(QObject *parent = nullptr);

    Q_INVOKABLE int sourceRow(const int row) const;
    Q_INVOKABLE int findRowById(const int id) const;
};

DB_END_NAMESPACE

#endif // MILKSORTFILTERPROXYMODEL_H
