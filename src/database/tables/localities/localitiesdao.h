#ifndef LOCALITIESDAO_H
#define LOCALITIESDAO_H

#include <base/dao.h>
#include "localitydata.h"

DB_BEGIN_NAMESPACE

class LocalitiesDao: public Dao {
public:
    LocalitiesDao(const QSqlDatabase &db = QSqlDatabase());

    LocalityData get(const milk_id id) const;
    void insert(const LocalityData &data);
    void update(const LocalityData &data);
};

DB_END_NAMESPACE

#endif // LOCALITIESDAO_H
