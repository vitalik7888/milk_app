#include "DbUtils.h"

// Qt
#include <QSet>
#include <QStringList>



bool DbUtils::isAutoIncrIdIsValid(const DbConstants::milk_id id)
{
    return id > 0;
}

QString DbUtils::getSelectStr(const QString &tableName, const QStringList &columns)
{
    if (columns.empty())
        return QString();

    QString queryStr = "SELECT ";
    for(const auto &columnName: columns)
        queryStr.append(columnName + ", ");

    return queryStr.replace(queryStr.length() - 2, 2, " FROM " + tableName);
}

QString DbUtils::getPrepUpdateStr(const QString &tableName, const QStringList &columns)
{
    if (columns.empty())
        return QString();

    QString queryStr = "UPDATE " + tableName + " SET ";
    for(const auto &columnName: columns)
        queryStr.append(columnName + " = ?, ");

    return queryStr.replace(queryStr.length() - 2, 2, " ");
}

QString DbUtils::getPrepInsertStr(const QString &tableName, const QStringList &columns)
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

QString DbUtils::getStrDeliverersIn(const QSet<DbConstants::milk_id> &deliverersIds)
{
    QString deliverersIn;
    if (!deliverersIds.isEmpty()) {
        deliverersIn = DbConstants::Deliverers::FN_ID + " IN (";
        for (const auto _id : deliverersIds)
            deliverersIn.append(QString("%1, ").arg(_id));
        deliverersIn.replace(deliverersIn.size() - 2, 2, ")");
    }

    return deliverersIn;
}
