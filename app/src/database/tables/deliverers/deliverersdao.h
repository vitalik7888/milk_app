#ifndef DELIVERERSDAO_H
#define DELIVERERSDAO_H

#include <base/dao.h>

DB_BEGIN_NAMESPACE

class DeliverersTable;


class DeliverersDao: public Dao {
public:
    explicit DeliverersDao(DeliverersTable *table);

    virtual bool insert(const QVariant &data) const Q_DECL_OVERRIDE;
    virtual bool update(const QVariant &data) const Q_DECL_OVERRIDE;
};

DB_END_NAMESPACE

#endif // DELIVERERSDAO_H
