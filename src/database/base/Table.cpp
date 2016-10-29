#include "Table.h"

#include "dao.h"
#include "Utils.h"
// Qt
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

USE_DB_NAMESPACE


Table::Table(Dao *dao, QObject *parent, QSqlDatabase db) :
    QSqlQueryModel(parent),
    m_db(db),
    m_dao(dao),
    m_isFetchOnRefresh(false)
{
    setObjectName("Table");
}

Table::~Table()
{
    qDebug() << "delete " + objectName();
}

QSqlDatabase Table::database() const
{
    return m_db;
}

QString Table::selectAll() const
{
    QStringList columns;
    for (int i = 0; i < getColumnsCount(); ++i)
        columns.append(tableName() + "." + getColumnById(i).name());

    return Utils::Main::getSelectStr(tableName(), columns);
}

bool Table::isEmpty() const
{
    return (rowCount() == 0);
}

bool Table::remove(const milk_id id) const
{
    QSqlQuery query;
    query.prepare(QString("DELETE FROM %1 where %2 = ?")
                  .arg(tableName())
                  .arg(primaryField().name()));
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

QSqlRecord Table::getColumns() const
{
    return m_columns;
}

int Table::getColumnsCount() const
{
    return m_columns.count();
}

int Table::getColumnPosition(const QString &name) const
{
    return m_columns.indexOf(name);
}

QString Table::getColumnNameById(const int column, const bool withTableName) const
{
    if (!withTableName)
        return getColumnById(column).name();

    return QString("%1.%2").arg(tableName()).arg(getColumnById(column).name());
}

QSqlField Table::getColumnById(const int column) const
{
    return getColumns().field(column);
}

QSqlField Table::getColumnByName(const QString &columnName) const
{
    return getColumns().field(columnName);
}

bool Table::updateValue(const int columnPosition, const milk_id id, const QVariant &value) const
{
    try {
        m_dao->updateValue(getColumnById(columnPosition).name(), id, value);
        return true;
    } catch (const QString &err) {
        emit error(err);
        return false;
    }
}

bool Table::getIsFetchOnRefresh() const
{
    return m_isFetchOnRefresh;
}

void Table::setIsFetchOnRefresh(const bool isFetchOnRefresh)
{
    m_isFetchOnRefresh = isFetchOnRefresh;
}

/*QString Deliverers::selectColumns(const int count, ...) const
{
    QString queryStr = "SELECT ";

    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; ++i) {
        queryStr += nameOfTheColumn(static_cast<Column>(va_arg(args, int))) + ", ";
    }

    va_end(args);

    return queryStr.replace(queryStr.length() - 2, 2, " FROM " + name());
}*/


bool Table::setData(const QModelIndex &_index, const QVariant &value, int role)
{
    Q_UNUSED(role);

    const auto idColumn = record().indexOf(primaryField().name());
    if (_index.column() == idColumn)
        return false;

    const auto primaryKeyIndex = index(_index.row(), idColumn);
    const auto id = data(primaryKeyIndex).toLongLong();

    if (updateValue(_index.column(), id, value)) {
        refresh();
        emit dataChanged(_index, _index);

        return true;
    }

    return false;
}

Qt::ItemFlags Table::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);

    const auto idColumn = record().indexOf(primaryField().name());
    if (index.column() != idColumn)
        flags |= Qt::ItemIsEditable;

    return flags;
}
