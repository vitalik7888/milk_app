#ifndef DELIVERERSDAO_H
#define DELIVERERSDAO_H

#include <base/dao.h>
#include "delivererdata.h"
#include <experimental/optional>

DB_BEGIN_NAMESPACE

class DeliverersTable;


class DeliverersDao: public Dao {
public:
    explicit DeliverersDao(DeliverersTable *table);

    std::experimental::optional<DelivererData> getDeliverer(const milk_id delivererId) const;
    bool insert(const DelivererData &deliverer) const;
    bool update(const DelivererData &deliverer) const;
};

DB_END_NAMESPACE

#endif // DELIVERERSDAO_H
