#include "Utils.h"

// Qt
#include <QList>


bool Utils::Main::isAutoIncrIdIsValid(const milk_id id)
{
    return id > 0;
}

QString Utils::Main::getSelectStr(const QString &tableName, const QStringList &columns)
{
    if (columns.empty())
        return QString();

    QString queryStr = "SELECT ";
    for(const auto &columnName: columns)
        queryStr.append(columnName + ", ");

    return queryStr.replace(queryStr.length() - 2, 2, " FROM " + tableName);
}

QString Utils::Main::getPrepUpdateStr(const QString &tableName, const QStringList &columns)
{
    if (columns.empty())
        return QString();

    QString queryStr = "UPDATE " + tableName + " SET ";
    for(const auto &columnName: columns)
        queryStr.append(columnName + " = ?, ");

    return queryStr.replace(queryStr.length() - 2, 2, " ");
}

QString Utils::Main::getPrepInsertStr(const QString &tableName, const QStringList &columns)
{
    if (columns.empty())
        return QString();

    QString queryStr = "INSERT INTO " + tableName + " (", values = "VALUES (";

    for(const auto &columnName: columns) {
        queryStr.append(columnName + ", ");
        values.append("?, ");
    }

    queryStr.replace(queryStr.length() - 2, 2, ") ");
    values.replace(values.length() - 2, 2, ")");

    return queryStr + values;
}
