#ifndef DELIVERERS_TABLE_H
#define DELIVERERS_TABLE_H

#include <base/Table.h>
#include "Deliverer.h"
#include <experimental/optional>

DB_BEGIN_NAMESPACE

class LocalitiesTable;
class DeliverersDao;

class DBLIBRARYSHARED_EXPORT DeliverersTable : public Table
{
    Q_OBJECT
    Q_PROPERTY(LocalitiesTable* localities READ localities CONSTANT)

public:
    DeliverersTable(QObject *parent = Q_NULLPTR);
    DeliverersTable(LocalitiesTable *localities, QSqlDatabase db, QObject *parent = Q_NULLPTR);
    virtual ~DeliverersTable();

    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;

    virtual QString selectAll() const Q_DECL_OVERRIDE;
    QString tableName() const Q_DECL_OVERRIDE;
    int getColPosition(const QString &columnName) const Q_DECL_OVERRIDE;
    QString getColName(const int position, const bool withTableName = false) const Q_DECL_OVERRIDE;
    QString primaryField() const Q_DECL_OVERRIDE;

    LocalitiesTable *localities() const;

    std::experimental::optional<DelivererData> getDelivererData(const int delivererId) const;
    QList<DelivererData> getDeliverersData(const QString &where) const;
    Q_INVOKABLE Deliverer *getDeliverer(const int delivererId);
    Q_INVOKABLE bool insert(int index, Deliverer *deliverer);
    Q_INVOKABLE bool append(Deliverer *deliverer);
    Q_INVOKABLE virtual QVariant get(const int row) Q_DECL_OVERRIDE;
    Q_INVOKABLE bool set(const int row, Deliverer *deliverer);

private:
    LocalitiesTable *m_localities;

    DeliverersDao *dao() const;

    static DelivererData fromRecord(const QSqlRecord &record);
};

DB_END_NAMESPACE

#endif // DELIVERERS_TABLE_H
