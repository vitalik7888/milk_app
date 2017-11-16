#ifndef LOCALITIESDAO_H
#define LOCALITIESDAO_H

#include <base/dao.h>
#include "localitydata.h"
#include <experimental/optional>

DB_BEGIN_NAMESPACE

class LocalitiesTable;


class LocalitiesDao: public Dao {
public:
    LocalitiesDao(LocalitiesTable *table);

    std::experimental::optional<LocalityData> get(const milk_id id) const;
    bool insert(const LocalityData &data) const;
    bool update(const LocalityData &data) const;
};

DB_END_NAMESPACE

#endif // LOCALITIESDAO_H
