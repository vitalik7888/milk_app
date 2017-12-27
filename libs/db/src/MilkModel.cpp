#include "MilkModel.h"

#include "DaoSql.h"
// Qt
#include <QDebug>

USE_DB_NAMESPACE


MilkModel::MilkModel(QObject *parent):
    QAbstractListModel(parent)
{

}

void MilkModel::setDao(DaoSql *dao)
{
    m_dao = dao;
}

DaoSql *MilkModel::dao() const
{
    return m_dao;
}

int db::MilkModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_repository.count();
}

void MilkModel::refresh()
{
    emit beginRefresh();
    clear();
    m_repository.setAll(m_dao->get());
    emit endRefresh();
}

void MilkModel::clear()
{
    m_repository.clear();
}

int MilkModel::getPositionById(const MILK_ID id) const
{
    return m_repository.getPosition(id);
}

const MilkBaseItem *MilkModel::getItemById(const MILK_ID milkId) const
{
    return m_repository.getById(milkId);
}

const QList<const MilkBaseItem *> MilkModel::getItemsByIds(const QList<MILK_ID> milkIds) const
{
    QList<const MilkBaseItem *> items;
    for (const auto milkId : milkIds)
        items.append(m_repository.getById(milkId));

    return items;
}

bool MilkModel::update(const MilkBaseItem *item)
{
    const int row = m_repository.getPosition(item->milkId());
    if (row < 0) {
        qWarning() << "There is no such item with the id for update";
        return false;
    }

    if (m_dao->update(item)) {
        copyItemValues(m_repository.getById(item->milkId()), item);
        emit dataChanged(this->index(row), index(row));
        return true;
    }

    return false;
}

bool MilkModel::removeById(const MILK_ID milkId)
{
    const int row = m_repository.getPosition(milkId);
    if (row < 0) {
        qWarning() << "There is no such item with the id for remove";
        return false;
    }

    return removeRow(row);
}

bool MilkModel::append(MilkBaseItem *item)
{
    const int _rowCount = rowCount();

    beginInsertRows({}, _rowCount, _rowCount);

    bool isOk = m_dao->insert(item);
    if (isOk) {
        appendToRepository(item);
    }

    endInsertRows();

    return isOk;
}

const MilkBaseItem *MilkModel::getItemByIndex(const int row) const
{
    return m_repository.get(row);
}

bool db::MilkModel::removeRows(int row, int count, const QModelIndex &parent)
{
    const int _rowCount = rowCount();
    if (row < 0 || row > _rowCount || count < 0 || (row + count) > _rowCount)
        return false;

    beginRemoveRows(parent, row, row + count - 1);
    for (int i = row; i < (row + count); ++i) {
        const MilkBaseItem& item = *m_repository.get(i);
        m_dao->removeById(item.milkId());
    }
    m_repository.remove(row, count);
    endRemoveRows();

    return true;
}
