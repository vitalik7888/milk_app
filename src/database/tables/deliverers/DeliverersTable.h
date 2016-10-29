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
    QSqlField primaryField() const Q_DECL_OVERRIDE;

    QString getNameColumnId(const bool withTableName = false) const;
    QString getNameColumnName(const bool withTableName = false) const;
    QString getNameColumnLocalityId(const bool withTableName = false) const;
    QString getNameColumnInn(const bool withTableName = false) const;
    QString getNameColumnAddress(const bool withTableName = false) const;
    QString getNameColumnPhoneNumber(const bool withTableName = false) const;

    QSqlField getFieldId() const;
    QSqlField getFieldName() const;
    QSqlField getFieldLocalityId() const;
    QSqlField getFieldInn() const;
    QSqlField getFieldAddress() const;
    QSqlField getFieldPhoneNumber() const;

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

    void initColumns() Q_DECL_OVERRIDE;

    DeliverersDao *dao() const;
};

DB_END_NAMESPACE

#endif // DELIVERERS_TABLE_H
