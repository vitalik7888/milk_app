#include "Table.h"

#include "Dao.h"
#include <DbUtils.h>
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

void Table::refresh()
{
    emit startRefresh();

    const QString queryStr = query().executedQuery();
    clear();
    query().clear();
    setQuery(queryStr);

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

int Table::getIdByRow(const int row) const
{
    bool ok = false;
    const int _id = data(index(row, 0)).toInt(&ok);
    if (!ok)
        return -1;

    return _id;
}

QHash<int, QByteArray> Table::roleNames() const
{
    QHash<int, QByteArray> roles;

    for (int i = 0; i < this->record().count(); i ++) {
        roles.insert(Qt::UserRole + i + 1, "f_" + record().fieldName(i).toUtf8());
    }

    return roles;
}

bool Table::insert(int position, const QVariant &data)
{
    if(position < 0 || position > rowCount()) {
        return false;
    }

    emit beginInsertRows(QModelIndex(), position, position);
    const bool isOk = m_dao->insert(data);
    emit endInsertRows();

    if (isOk)
        refresh();

    return isOk;
}

bool Table::remove(const int row)
{
    return removeRow(row);
}

bool Table::append(const QVariant &data)
{
    return insert(rowCount(), data);
}

bool Table::removeAll()
{
    beginRemoveRows({}, 0, rowCount() - 1);
    bool isOk = m_dao->remove();
    endRemoveRows();

    if (isOk)
        refresh();

    return isOk;
}

bool Table::set(const int row, const QVariant &data)
{
    bool isOk = m_dao->update(data);
    if (isOk) {
        emit dataChanged(index(row, 0), index(rowCount(), columnCount()), roleNames().keys().toVector());
        refresh();
    }

    return isOk;
}

QVariant Table::getValue(const int row, const int column) const
{
    return data(index(row, column));
}

bool Table::setValue(const int row, const int column, const QVariant &value, const int role)
{
    return setData(index(row, column), value, role);
}

int Table::findRowById(const int id) const
{
    for (int row = 0; row < rowCount(); ++row) {
        if (getIdByRow(row) == id)
            return row;
    }

    return -1;
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

bool Table::setData(const QModelIndex &_index, const QVariant &value, int role)
{
    if (!_index.isValid())
        return false;

    const int _id = data(this->index(_index.row(), 0)).toInt();
    const int column =  role < Qt::UserRole ? _index.column() : role - Qt::UserRole - 1;
    const QString colName = getColName(column);
    if (m_dao->updateValue(colName, _id, value)) {
        emit dataChanged(_index, _index, {role});
        refresh();
        return true;
    }

    return false;
}

Qt::ItemFlags Table::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QSqlQueryModel::flags(index) | Qt::ItemIsEditable;
}


bool db::Table::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);

    const int columnId = getColPosition(primaryField());
    bool isOk = false;
    if (count == 1) {
        bool ok = false;
        const auto _id = data(index(row, columnId, parent)).toInt(&ok);
        if (ok)
            isOk = m_dao->remove(_id);
    } else {
        bool ok = false;
        QSet<int> _ids;
        for (int i = row; i < row + count; i++) {
            const auto _id = data(index(i, columnId, parent)).toInt(&ok);
            if (ok)
                _ids.insert(_id);
        }
        if (!_ids.isEmpty())
            isOk = m_dao->remove(DbUtils::getStrIdsIn(this, _ids));
    }

    endRemoveRows();

    if (isOk)
        refresh();

    return isOk;
}
