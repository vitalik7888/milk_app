#ifndef DAO_H
#define DAO_H

#include "Table.h"
// Qt
#include <QVariant>

Q_DECLARE_METATYPE(QSqlRecord)

DB_BEGIN_NAMESPACE

class Dao
{
public:
    Dao(Table *table);
    virtual ~Dao();

    QVariant get(const DbConstants::milk_id id) const;
    virtual QVariant getAll(const QString &where = {}) const;
    virtual bool insert(const QVariant &data) const = 0;
    virtual bool remove(const QString &where = "") const;
    bool remove(const DbConstants::milk_id id) const;
    virtual bool update(const QVariant &data) const = 0;
    bool updateValue(const QString &columnName, const DbConstants::milk_id id, const QVariant &value) const;

protected:
    Table *m_table;

    void _error(const QString &error_description) const;
};

DB_END_NAMESPACE

#endif // DAO_H
