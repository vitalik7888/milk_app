#ifndef DBUTILS_H
#define DBUTILS_H

#include "dbconstants.h"

class QStringList;


class DbUtils
{
public:
    static bool isAutoIncrIdIsValid(const DbConstants::milk_id id);

    static QString getSelectStr(const QString &tableName, const QStringList &columns);
    static QString getPrepUpdateStr(const QString &tableName, const QStringList &columns);
    static QString getPrepInsertStr(const QString &tableName, const QStringList &columns);

};

#endif // DBUTILS_H
