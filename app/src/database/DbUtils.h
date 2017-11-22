#ifndef DBUTILS_H
#define DBUTILS_H

#include "DbConstants.h"

class QStringList;
template<class T>
class QSet;


class DbUtils
{
public:
    static bool isAutoIncrIdIsValid(const DbConstants::milk_id id);

    static QString getSelectStr(const QString &tableName, const QStringList &columns);
    static QString getPrepUpdateStr(const QString &tableName, const QStringList &columns);
    static QString getPrepInsertStr(const QString &tableName, const QStringList &columns);

    static QString getStrDeliverersIn(const QSet<DbConstants::milk_id> &deliverersIds);
};

#endif // DBUTILS_H
