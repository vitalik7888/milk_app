#ifndef DELIVERERS_TABLE_H
#define DELIVERERS_TABLE_H

#include "base/Table.h"
#include "Deliverer.h"

class LocalitiesTable;


class DeliverersTable : public Table
{
    Q_OBJECT
public:
    DeliverersTable(LocalitiesTable *parent, QSqlDatabase db);

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

    Deliverer getDeliverer(const qlonglong delivererId) const;
    bool insert(const Deliverer &deliverer);
    bool update(const Deliverer &deliverer);
    bool setName(const qlonglong delivererId, const QString &tableName) const;
    bool setLocalityId(const qlonglong delivererId, const qlonglong localityId) const;
    bool setInn(const qlonglong delivererId, const qlonglong inn) const;
    bool setAddress(const qlonglong delivererId, const QString &address) const;
    bool setPhoneNumber(const qlonglong delivererId, const QString &phoneNumber) const;

private:
    LocalitiesTable *m_localities;

    void initColumns() Q_DECL_OVERRIDE;
};


#endif // DELIVERERS_TABLE_H
