#include "Table.h"

#include "dao.h"
// Qt
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

USE_DB_NAMESPACE


Table::Table(Dao *dao, QSqlDatabase db, QObject *parent) :
    QSqlQueryModel(parent),
    m_db(db),
    m_dao(dao),
    m_isFetchOnRefresh(false)
{
    setObjectName("Table");
}

Table::~Table()
{
}

QSqlDatabase Table::database() const
{
    return m_db;
}

QString Table::selectAll() const
{
    return QString("SELECT * FROM %1").arg(tableName());
}

bool Table::isEmpty() const
{
    return (rowCount() == 0);
}

bool Table::remove(const DbConstants::milk_id id) const
{
    QSqlQuery query;
    query.prepare(QString("DELETE FROM %1 WHERE %2 = ?").arg(tableName()).arg(primaryField()));
    query.addBindValue(id);

    if (!query.exec()) {
        emit error(query.lastError().text());
        return false;
    }

    return true;
}

bool Table::removeAll() const
{
    QSqlQuery query;
    query.prepare("DELETE FROM " + tableName());

    if (!query.exec()) {
        emit error(query.lastError().text());
        return false;
    }
    return true;
}

void Table::refresh()
{
    emit startRefresh();

    setQuery(query().lastQuery());

    if (m_isFetchOnRefresh)
    {
        while (canFetchMore())
            fetchMore();
    }

    emit refreshed();
}

bool Table::getIsFetchOnRefresh() const
{
    return m_isFetchOnRefresh;
}

void Table::setIsFetchOnRefresh(const bool isFetchOnRefresh)
{
    m_isFetchOnRefresh = isFetchOnRefresh;
}

bool Table::setData(const QModelIndex &_index, const QVariant &value, int role)
{
    Q_UNUSED(role);

    const auto idColumn = record().indexOf(primaryField());
    if (_index.column() == idColumn)
        return false;

    const auto primaryKeyIndex = index(_index.row(), idColumn);
    const auto id = data(primaryKeyIndex).toLongLong();

    try {
        m_dao->updateValue(getColName(_index.column()), id, value);
        refresh();
        emit dataChanged(_index, _index);
    } catch (const QString &) {
        return false;
    }

    return true;
}

QHash<int, QByteArray> Table::roleNames() const
{
    QHash<int, QByteArray> roles;

    for (int i = 0; i < this->record().count(); i ++) {
        roles.insert(Qt::UserRole + i + 1, "f_" + record().fieldName(i).toUtf8());
    }

    return roles;
}

QVariant Table::data(const QModelIndex &_index, int role) const
{
    QVariant value;

    if (_index.isValid()) {
        if (role < Qt::UserRole) {
            value = QSqlQueryModel::data(_index, role);
        } else {
            const int columnIdx = role - Qt::UserRole - 1;
            QModelIndex modelIndex = this->index(_index.row(), columnIdx);
            value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
        }
    }
    return value;
}

Qt::ItemFlags Table::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);

    const auto idColumn = record().indexOf(primaryField());
    if (index.column() != idColumn)
        flags |= Qt::ItemIsEditable;

    return flags;
}
