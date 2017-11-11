#ifndef DELIVERERSDAO_H
#define DELIVERERSDAO_H

#include <base/dao.h>
#include "delivererdata.h"

DB_BEGIN_NAMESPACE

class DeliverersDao: public Dao {
public:
    DeliverersDao(const QSqlDatabase &db);

    DelivererData getDeliverer(const milk_id delivererId) const;
    void insert(const DelivererData &deliverer) const;
    void update(const DelivererData &deliverer) const;
};

DB_END_NAMESPACE

#endif // DELIVERERSDAO_H
