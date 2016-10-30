#ifndef MILKPOINTDAO_H
#define MILKPOINTDAO_H

#include <base/dao.h>
#include "milkpointdata.h"

DB_BEGIN_NAMESPACE

class MilkPointDao: public Dao {
public:
    MilkPointDao(const QSqlDatabase &db);

    MilkPointData get(const milk_id id) const;
    void insert(const MilkPointData &data) const;
    void update(const MilkPointData &data) const;
};

DB_END_NAMESPACE

#endif // MILKPOINTDAO_H
