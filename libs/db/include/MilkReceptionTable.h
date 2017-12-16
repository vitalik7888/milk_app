#ifndef MILKRECEPTION_TABLE_H
#define MILKRECEPTION_TABLE_H

#include "Table.h"
#include "MilkReception.h"
// Qt
#include <QDate>

#include <experimental/optional>

DB_BEGIN_NAMESPACE
    class MilkReceptionDao;
    class DeliverersTable;
    class MilkPointsTable;


class DBLIBRARYSHARED_EXPORT MilkReceptionTable : public Table
{
    Q_OBJECT
    Q_PROPERTY(DeliverersTable* deliverers READ deliverers CONSTANT)
    Q_PROPERTY(MilkPointsTable* milkPoints READ milkPoints CONSTANT)

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

    std::experimental::optional<MilkReceptionData> getMilkReceptionData(const int milkReceptionId) const;
    MilkReception *getMilkReception(const int milkReceptionId);
    QList<MilkReceptionData> getMilkReceptionsData(const QString &where = QString()) const;
    Q_INVOKABLE bool insert(int index, MilkReception *milkReception);
    Q_INVOKABLE bool set(const int row, MilkReception *milkReception);
    Q_INVOKABLE bool append(MilkReception *milkReception);
    Q_INVOKABLE virtual QVariant get(const int row) Q_DECL_OVERRIDE;


    DeliverersTable *deliverers() const;
    MilkPointsTable *milkPoints() const;

    std::tuple<double, double> getMinMaxPriceLiter(const QDate &from, const QDate &to = QDate()) const;
    Q_INVOKABLE QDate getMinDeliveryDate() const;
    Q_INVOKABLE QDate getMaxDeliveryDate() const;

private:
    DeliverersTable *m_deliverers;
    MilkPointsTable *m_milkPoints;

    MilkReceptionDao *dao() const;

    static MilkReceptionData fromRecord(const QSqlRecord &record);
};

DB_END_NAMESPACE

#endif // MILKRECEPTION_TABLE_H
