#ifndef MILKRECEPTION_TABLE_H
#define MILKRECEPTION_TABLE_H

#include "base/Table.h"
#include "MilkReception.h"
#include <QDate>

class DeliverersTable;
class MilkPointsTable;


class MilkReceptionTable : public Table
{
    Q_OBJECT
public:
    MilkReceptionTable(DeliverersTable *deliverers, MilkPointsTable *milkPoints, QSqlDatabase db);

    QString tableName() const Q_DECL_OVERRIDE;
    QSqlField primaryField() const Q_DECL_OVERRIDE;

    QString selectAll() const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;

    QString getNameColumnId(const bool withTableName = false) const;
    QString getNameColumnIdDeliverer(const bool withTableName = false) const;
    QString getNameColumnDelivererName(const bool withTableName = false) const;
    QString getNameColumnMilkPointId(const bool withTableName = false) const;
    QString getNameColumnMilkPointName(const bool withTableName = false) const;
    QString getNameColumnDeliveryDate(const bool withTableName = false) const;
    QString getNameColumnPriceLiter(const bool withTableName = false) const;
    QString getNameColumnLiters(const bool withTableName = false) const;
    QString getNameColumnFat(const bool withTableName = false) const;

    QSqlField getFieldId() const;
    QSqlField getFieldIdDeliverer() const;
    QSqlField getFieldMilkPointId() const;
    QSqlField getFieldDeliveryDate() const;
    QSqlField getFieldPriceLiter() const;
    QSqlField getFieldLiters() const;
    QSqlField getFieldFat() const;

    MilkReception getMilkReception(const qlonglong milkPointId) const;
    bool insert(const MilkReception &milkReception) const;
    bool update(const MilkReception &milkReception) const;
    bool setIdDeliverer(const qlonglong milkReceptionId, const qlonglong delivererId) const;
    bool setIdMilkPoint(const qlonglong milkReceptionId, const qlonglong milkPointId) const;
    bool setDeliveryDate(const qlonglong milkReceptionId, const QDate &deliveryDate) const;
    bool setPriceLiter(const qlonglong milkReceptionId, const float priceLiter) const;
    bool setLiters(const qlonglong milkReceptionId, const float liters) const;
    bool setFat(const qlonglong milkReceptionId, const float fate) const;

    bool updatePriceLiters(const double price, const QDate &dateFrom, const QDate &dateTo) const;

    DeliverersTable *getDeliverers() const;
    MilkPointsTable *getMilkPoints() const;

    QList<float> getMinMaxPriceLiter(const QDate &min, QDate max = QDate()) const;
    QDate getMinDeliveryDate() const;
    QDate getMaxDeliveryDate() const;

private:
    DeliverersTable *m_deliverers;
    MilkPointsTable *m_milkPoints;

    void initColumns() Q_DECL_OVERRIDE;
};

#endif // MILKRECEPTION_TABLE_H
