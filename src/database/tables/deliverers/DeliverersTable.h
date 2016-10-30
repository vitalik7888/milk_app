#ifndef DELIVERERS_TABLE_H
#define DELIVERERS_TABLE_H

#include <base/Table.h>
#include "Deliverer.h"

DB_BEGIN_NAMESPACE

class LocalitiesTable;
class DeliverersDao;

class DeliverersTable : public Table
{
    Q_OBJECT
public:
    DeliverersTable(LocalitiesTable *parent, QSqlDatabase db);
    ~DeliverersTable();

    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;

    QString tableName() const Q_DECL_OVERRIDE;
    int getColPosition(const QString &columnName) const Q_DECL_OVERRIDE;
    QString getColName(const int position, const bool withTableName = false) const Q_DECL_OVERRIDE;
    QString primaryField() const Q_DECL_OVERRIDE;

    LocalitiesTable *getLocalities() const;

    DelivererData getDeliverer(const milk_id delivererId) const;
    bool insert(const DelivererData &deliverer);
    bool update(const DelivererData &deliverer);
    bool setName(const milk_id delivererId, const QString &tableName) const;
    bool setLocalityId(const milk_id delivererId, const milk_id localityId) const;
    bool setInn(const milk_id delivererId, const milk_inn inn) const;
    bool setAddress(const milk_id delivererId, const QString &address) const;
    bool setPhoneNumber(const milk_id delivererId, const QString &phoneNumber) const;

private:
    LocalitiesTable *m_localities;

    DeliverersDao *dao() const;
};

DB_END_NAMESPACE

#endif // DELIVERERS_TABLE_H
