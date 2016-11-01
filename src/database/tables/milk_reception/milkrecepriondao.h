#ifndef MILKRECEPRIONDAO_H
#define MILKRECEPRIONDAO_H

#include <base/dao.h>
#include "milkreceptiondata.h"

DB_BEGIN_NAMESPACE

class MilkReceptionDao: public Dao {
public:
    MilkReceptionDao(const QSqlDatabase &db);

    MilkReceptionData get(const milk_id id) const;
    QList<MilkReceptionData> get(const QString &where) const;
    void insert(const MilkReceptionData &data) const;
    void update(const MilkReceptionData &data) const;
};

DB_END_NAMESPACE

#endif // MILKRECEPRIONDAO_H
