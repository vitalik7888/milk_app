#ifndef DAO_H
#define DAO_H

#include "dbconstants.h"
// Qt
#include <QSqlDatabase>
#include <QVariant>

DB_BEGIN_NAMESPACE

class Dao
{
public:
    Dao(const QString &tableName, const QString &primeryFieldName, const QSqlDatabase &db = QSqlDatabase());
    virtual ~Dao();

    void updateValue(const QString &columnName, const milk_id id, const QVariant &value) const;

protected:
    const QString m_tableName;
    const QString m_primeryFieldName;

    QSqlDatabase m_db;
};

DB_END_NAMESPACE

#endif // DAO_H
