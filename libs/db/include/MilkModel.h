#ifndef _MILK_MODEL_H_
#define _MILK_MODEL_H_

#include "DbConstants.h"
#include <MilkBaseItem.h>
#include <memory>
// Qt
#include <QAbstractListModel>

DB_BEGIN_NAMESPACE
class DaoSql;

template<typename T>
class DBLIBRARYSHARED_EXPORT Repository
{
public:
    Repository() {
        m_items = std::make_unique<std::vector<std::unique_ptr<T>>>();
    }

    template<class M>
    void append(const T *item)
    {
        m_items->push_back(std::make_unique<M>(*static_cast<const M*>(item)));
    }

    void setAll(std::unique_ptr<std::vector<std::unique_ptr<T>>> items)
    {
        m_items = std::move(items);
    }

    void remove(const int position, const int count = 1)
    {
        m_items->erase(m_items->begin() + position, m_items->begin() + position + count);
    }

    T *get(const int position) const
    {
        return m_items->at(position).get();
    }

    T *getById(const MILK_ID milkId) const
    {
        for (const auto &item : *m_items.get()) {
            if (item->milkId() == milkId)
                return item.get();
        }
        return Q_NULLPTR;
    }

    int getPosition(const MILK_ID milkId) const
    {
        int row = 0;
        for (const auto &item : *m_items.get()) {
            if (item->milkId() == milkId)
                return row;
            ++row;
        }
        return -1;
    }

    void clear()
    {
        m_items->clear();
    }

    int count() const
    {
        return m_items->size();
    }

private:
    std::unique_ptr<std::vector<std::unique_ptr<T>>> m_items;
};

class DBLIBRARYSHARED_EXPORT MilkModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(DaoSql* dao READ dao WRITE setDao NOTIFY daoChanged)
public:
    MilkModel(QObject *parent = Q_NULLPTR);

    void setDao(DaoSql *dao);
    DaoSql *dao() const;

    int rowCount(const QModelIndex &parent = {}) const Q_DECL_OVERRIDE;
    bool removeRows(int row, int count, const QModelIndex &parent = {}) Q_DECL_OVERRIDE;


    Q_INVOKABLE int getPositionById(const MILK_ID id) const;
    const MilkBaseItem *getItemByIndex(const int row) const;
    const MilkBaseItem *getItemById(const MILK_ID milkId) const;
    const QList<const MilkBaseItem *> getItemsByIds(const QList<MILK_ID> milkIds) const;
    bool update(const MilkBaseItem *item);
    bool removeById(const MILK_ID milkId);
    bool append(MilkBaseItem *item);

public slots:
    virtual void refresh();
    void clear();

signals:
    void beginRefresh();
    void endRefresh();
    void daoChanged(DaoSql *dao);

protected:
    DaoSql *m_dao;
    Repository<MilkBaseItem> m_repository;

    virtual void copyItemValues(MilkBaseItem *left, const MilkBaseItem *right) = 0;
    virtual void appendToRepository(const MilkBaseItem *item) = 0;
};

DB_END_NAMESPACE

#endif // MILK_TABLE

