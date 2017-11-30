#include "MilkSortFilterProxyModel.h"

#include <base/Table.h>
// Qt
#include <QDebug>

USE_DB_NAMESPACE
using DC = DbConstants;


MilkSortFilterProxyModel::MilkSortFilterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{

}

int MilkSortFilterProxyModel::sourceRow(const int row) const
{
    Table *table = qobject_cast<Table *>(sourceModel());
    return mapToSource(index(row, table->getColPosition(table->primaryField()))).row();
}

int MilkSortFilterProxyModel::findRowById(const int id) const
{
    Table *table = qobject_cast<Table *>(sourceModel());

    for (int row = 0; row < rowCount(); ++row) {
        if (data(index(row, table->getColPosition(table->primaryField()))) == id)
            return row;
    }

    return -1;
}
