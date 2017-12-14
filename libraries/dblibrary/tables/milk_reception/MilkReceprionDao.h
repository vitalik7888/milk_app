#ifndef MILKRECEPRIONDAO_H
#define MILKRECEPRIONDAO_H

#include <base/Dao.h>

DB_BEGIN_NAMESPACE

class MilkReceptionTable;


class DBLIBRARYSHARED_EXPORT MilkReceptionDao: public Dao {
    enum class MinMax {
        Min,
        Max,
        Both
    };

public:
    MilkReceptionDao(MilkReceptionTable *table);

    bool insert(const QVariant &data) const;
    bool update(const QVariant &data) const;

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
