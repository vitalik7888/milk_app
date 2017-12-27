#ifndef MILK_RECEPRION_DAO_H_
#define MILK_RECEPRION_DAO_H_

#include "DaoSql.h"
// Qt
#include <QSqlQuery>

DB_BEGIN_NAMESPACE

class MilkReceptionModel;


class DBLIBRARYSHARED_EXPORT MilkReceptionDao: public DaoSql {
    enum class MinMax {
        Min,
        Max,
        Both
    };

public:
    MilkReceptionDao(QObject *parent = Q_NULLPTR);

    QString getCreateTableStr() const Q_DECL_OVERRIDE;

    bool updatePriceLiter(const double price, const QDate &dateFrom, const QDate &dateTo);
    double getMinPriceLiter(const QDate &from, const QDate &to);
    double getMaxPriceLiter(const QDate &from, const QDate &to);
    std::tuple<double, double> getMinMaxPriceLiter(const QDate &from, const QDate &to);

    QDate getMinDeliveryDate();
    QDate getMaxDeliveryDate();

private:
    QString _tableName() const Q_DECL_OVERRIDE;
    QString _primaryFieldName() const Q_DECL_OVERRIDE;
    QStringList _fieldsNames() const Q_DECL_OVERRIDE;

    virtual DaoItem fromRecord(const QSqlRecord &record) Q_DECL_OVERRIDE;
    bool _insert(MilkBaseItem *item) Q_DECL_OVERRIDE;
    bool _update(const MilkBaseItem *item) Q_DECL_OVERRIDE;

    QSqlQuery getMinAndOrMaxPriceLiter(const QDate &from, const QDate &to, const MinMax minMax);
    QDate getMinMaxDeliveryDate(bool isMin);
};

DB_END_NAMESPACE

#endif // MILKRECEPRIONDAO_H
