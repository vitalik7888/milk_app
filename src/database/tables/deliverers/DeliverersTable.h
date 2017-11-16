#ifndef DELIVERERS_TABLE_H
#define DELIVERERS_TABLE_H

#include <base/Table.h>
#include "deliverer.h"
#include <experimental/optional>

DB_BEGIN_NAMESPACE

class LocalitiesTable;
class DeliverersDao;

class DeliverersTable : public Table
{
    Q_OBJECT
public:
    DeliverersTable(QObject *parent = Q_NULLPTR);
    DeliverersTable(LocalitiesTable *localities, QSqlDatabase db, QObject *parent = Q_NULLPTR);
    virtual ~DeliverersTable();

    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;

    QString tableName() const Q_DECL_OVERRIDE;
    int getColPosition(const QString &columnName) const Q_DECL_OVERRIDE;
    QString getColName(const int position, const bool withTableName = false) const Q_DECL_OVERRIDE;
    QString primaryField() const Q_DECL_OVERRIDE;

    LocalitiesTable *getLocalities() const;

    std::experimental::optional<DelivererData> getDelivererData(const milk_id delivererId) const;
    Q_INVOKABLE Deliverer *getDeliverer(const qlonglong delivererId);
    Q_INVOKABLE bool insert(int index, Deliverer *deliverer);
    Q_INVOKABLE bool append(Deliverer *deliverer);
    Q_INVOKABLE bool update(Deliverer *deliverer) const;
    Q_INVOKABLE bool setName(const milk_id delivererId, const QString &tableName) const;
    Q_INVOKABLE bool setLocalityId(const milk_id delivererId, const milk_id localityId) const;
    Q_INVOKABLE bool setInn(const milk_id delivererId, const milk_inn inn) const;
    Q_INVOKABLE bool setAddress(const milk_id delivererId, const QString &address) const;
    Q_INVOKABLE bool setPhoneNumber(const milk_id delivererId, const QString &phoneNumber) const;

private:
    LocalitiesTable *m_localities;

    DeliverersDao *dao() const;
};

DB_END_NAMESPACE

#endif // DELIVERERS_TABLE_H
