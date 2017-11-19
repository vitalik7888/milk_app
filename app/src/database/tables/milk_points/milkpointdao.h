#ifndef MILKPOINTDAO_H
#define MILKPOINTDAO_H

#include <base/dao.h>
#include "milkpointdata.h"
#include <experimental/optional>

DB_BEGIN_NAMESPACE

class MilkPointsTable;


class MilkPointDao: public Dao {
public:
    MilkPointDao(MilkPointsTable *table);

    std::experimental::optional<MilkPointData> get(const DbConstants::milk_id id) const;
    bool insert(const MilkPointData &data) const;
    bool update(const MilkPointData &data) const;
};

DB_END_NAMESPACE

#endif // MILKPOINTDAO_H
