#ifndef MILKRECEPTION_TABLE_H
#define MILKRECEPTION_TABLE_H

#include "base/Table.h"
#include "milkreception.h"
#include <src/core/Constants.h>
// Qt
#include <QDate>

DB_BEGIN_NAMESPACE
    class MilkReceptionDao;
    class DeliverersTable;
    class MilkPointsTable;


class MilkReceptionTable : public Table
{
    Q_OBJECT
public:
    MilkReceptionTable(QObject *parent = Q_NULLPTR);
    MilkReceptionTable(DeliverersTable *deliverers, MilkPointsTable *milkPoints,
                       QSqlDatabase db, QObject *parent = Q_NULLPTR);
    virtual ~MilkReceptionTable();

    QString tableName() const Q_DECL_OVERRIDE;
    QString primaryField() const Q_DECL_OVERRIDE;
    QString getColName(const int position, const bool withTableName = false) const Q_DECL_OVERRIDE;
    int getColPosition(const QString &columnName) const Q_DECL_OVERRIDE;

    QString selectAll() const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;

    MilkReceptionData getMilkReceptionData(const milk_id milkReceptionId) const;
    MilkReception *getMilkReception(const qlonglong milkReceptionId);
    QList<MilkReceptionData> getMilkReceptions(const QString &where = QString()) const;
    Q_INVOKABLE void insert(int index, MilkReception *milkReception);
    Q_INVOKABLE void append(MilkReception *milkReception);
    Q_INVOKABLE void update(MilkReception *milkReception) const;
    bool updatePriceLiters(const price price, const QDate &dateFrom, const QDate &dateTo) const;
    void setIdDeliverer(const milk_id milkReceptionId, const milk_id delivererId) const;
    void setIdMilkPoint(const milk_id milkReceptionId, const milk_id milkPointId) const;
    void setDeliveryDate(const milk_id milkReceptionId, const QDate &deliveryDate) const;
    void setPriceLiter(const milk_id milkReceptionId, const price priceLiter) const;
    void setLiters(const milk_id milkReceptionId, const double liters) const;
    void setFat(const milk_id milkReceptionId, const double fate) const;

    DeliverersTable *getDeliverers() const;
    MilkPointsTable *getMilkPoints() const;

    QPair<double, double> getMinMaxPriceLiter(const QDate &min, QDate max = QDate()) const;
    QDate getMinDeliveryDate() const;
    QDate getMaxDeliveryDate() const;

private:
    DeliverersTable *m_deliverers;
    MilkPointsTable *m_milkPoints;

    MilkReceptionDao *dao() const;
};

DB_END_NAMESPACE

#endif // MILKRECEPTION_TABLE_H
