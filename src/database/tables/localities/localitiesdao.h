#ifndef LOCALITIESDAO_H
#define LOCALITIESDAO_H

#include <base/dao.h>
#include "Locality.h"

DB_BEGIN_NAMESPACE

class LocalitiesDao: public Dao {
public:
    LocalitiesDao(const QSqlDatabase &db);

    Locality get(const milk_id id) const;
    void insert(const Locality &data);
    void update(const Locality &data);
};

DB_END_NAMESPACE

#endif // LOCALITIESDAO_H
