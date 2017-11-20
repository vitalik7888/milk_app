#ifndef MILKPOINTDAO_H
#define MILKPOINTDAO_H

#include <base/Dao.h>

DB_BEGIN_NAMESPACE

class MilkPointsTable;


class MilkPointDao: public Dao {
public:
    MilkPointDao(MilkPointsTable *table);

    virtual bool insert(const QVariant &data) const Q_DECL_OVERRIDE;
    virtual bool update(const QVariant &data) const Q_DECL_OVERRIDE;
};

DB_END_NAMESPACE

#endif // MILKPOINTDAO_H
