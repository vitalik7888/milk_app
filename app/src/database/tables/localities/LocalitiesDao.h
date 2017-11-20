#ifndef LOCALITIESDAO_H
#define LOCALITIESDAO_H

#include <base/Dao.h>

DB_BEGIN_NAMESPACE

class LocalitiesTable;


class LocalitiesDao: public Dao {
public:
    LocalitiesDao(LocalitiesTable *table);

    virtual bool insert(const QVariant &variant) const Q_DECL_OVERRIDE;
    virtual bool update(const QVariant &variant) const Q_DECL_OVERRIDE;
};

DB_END_NAMESPACE

#endif // LOCALITIESDAO_H
