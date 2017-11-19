#ifndef DAO_H
#define DAO_H

#include "Table.h"
// Qt
#include <QVariant>

DB_BEGIN_NAMESPACE

class Dao
{
public:
    Dao(Table *table);
    virtual ~Dao();

    bool updateValue(const QString &columnName, const DbConstants::milk_id id, const QVariant &value) const;

protected:
    Table *m_table;

    void _error(const QString &error_description) const;
};

DB_END_NAMESPACE

#endif // DAO_H
