#ifndef MILKRECEPRIONDAO_H
#define MILKRECEPRIONDAO_H

#include <base/dao.h>
#include "milkreceptiondata.h"
#include <experimental/optional>

DB_BEGIN_NAMESPACE

class MilkReceptionTable;


class MilkReceptionDao: public Dao {
    enum class MinMax {
        Min,
        Max,
        Both
    };

public:
    MilkReceptionDao(MilkReceptionTable *table);

    std::experimental::optional<MilkReceptionData> get(const DbConstants::milk_id id) const;
    QList<MilkReceptionData> get(const QString &where = QString()) const;
    bool insert(const MilkReceptionData &data) const;
    bool update(const MilkReceptionData &data) const;

    bool updatePriceLiter(const double price, const QDate &dateFrom, const QDate &dateTo) const;
    double getMinPriceLiter(const QDate &from, const QDate &to) const;
    double getMaxPriceLiter(const QDate &from, const QDate &to) const;
    std::tuple<double, double> getMinMaxPriceLiter(const QDate &from, const QDate &to) const;

    QDate getMinDeliveryDate() const;
    QDate getMaxDeliveryDate() const;

private:
    QSqlQuery getMinAndOrMaxPriceLiter(const QDate &from, const QDate &to, const MinMax minMax) const;
    QDate getMinMaxDeliveryDate(bool isMin) const;
};

DB_END_NAMESPACE

#endif // MILKRECEPRIONDAO_H
