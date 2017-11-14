#ifndef MILKPOINTDAO_H
#define MILKPOINTDAO_H

#include <base/dao.h>
#include "milkpointdata.h"
#include <experimental/optional>

DB_BEGIN_NAMESPACE

class MilkPointDao: public Dao {
public:
    MilkPointDao(const QSqlDatabase &db);

    std::experimental::optional<MilkPointData> get(const milk_id id) const;
    void insert(const MilkPointData &data) const;
    void update(const MilkPointData &data) const;
};

DB_END_NAMESPACE

#endif // MILKPOINTDAO_H
