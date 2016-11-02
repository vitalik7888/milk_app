#ifndef MILKRECEPTION_TABLE_H
#define MILKRECEPTION_TABLE_H

#include "base/Table.h"
#include "milkreceptiondata.h"
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
    MilkReceptionTable(DeliverersTable *deliverers, MilkPointsTable *milkPoints, QSqlDatabase db);
    ~MilkReceptionTable();

    QString tableName() const Q_DECL_OVERRIDE;
    QString primaryField() const Q_DECL_OVERRIDE;
    QString getColName(const int position, const bool withTableName = false) const Q_DECL_OVERRIDE;
    int getColPosition(const QString &columnName) const Q_DECL_OVERRIDE;

    QString selectAll() const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;

    MilkReceptionData getMilkReception(const milk_id milkPointId) const;
    QList<MilkReceptionData> getMilkReceptions(const QString &where = QString()) const;
    void insert(const MilkReceptionData &milkReception) const;
    void update(const MilkReceptionData &milkReception) const;
    bool updatePriceLiters(const double price, const QDate &dateFrom, const QDate &dateTo) const;
    void setIdDeliverer(const milk_id milkReceptionId, const milk_id delivererId) const;
    void setIdMilkPoint(const milk_id milkReceptionId, const milk_id milkPointId) const;
    void setDeliveryDate(const milk_id milkReceptionId, const QDate &deliveryDate) const;
    void setPriceLiter(const milk_id milkReceptionId, const float priceLiter) const;
    void setLiters(const milk_id milkReceptionId, const float liters) const;
    void setFat(const milk_id milkReceptionId, const float fate) const;

    DeliverersTable *getDeliverers() const;
    MilkPointsTable *getMilkPoints() const;

    QList<float> getMinMaxPriceLiter(const QDate &min, QDate max = QDate()) const;
    QDate getMinDeliveryDate() const;
    QDate getMaxDeliveryDate() const;

private:
    DeliverersTable *m_deliverers;
    MilkPointsTable *m_milkPoints;

    MilkReceptionDao *dao() const;
};

DB_END_NAMESPACE

#endif // MILKRECEPTION_TABLE_H
