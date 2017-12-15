#ifndef DBUTILS_H
#define DBUTILS_H

#include "dblibrary_global.h"
#include "DbConstants.h"

class QStringList;
template<class T>
class QSet;
DB_BEGIN_NAMESPACE
class Table;
DB_END_NAMESPACE


class DBLIBRARYSHARED_EXPORT DbUtils
{
public:
    static bool isAutoIncrIdIsValid(const int id);

    static QString getSelectStr(const QString &tableName, const QStringList &columns);
    static QString getPrepUpdateStr(const QString &tableName, const QStringList &columns);
    static QString getPrepInsertStr(const QString &tableName, const QStringList &columns);

    static QString getStrIdsIn(DB_NAMESPACE::Table *table, const QSet<int> &ids);
};

#endif // DBUTILS_H