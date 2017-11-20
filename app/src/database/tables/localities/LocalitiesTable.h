#ifndef LOCALITY_TABLE_H
#define LOCALITY_TABLE_H

#include "dbconstants.h"
#include "base/Table.h"
#include "locality.h"

#include <experimental/optional>

DB_BEGIN_NAMESPACE
    class LocalitiesDao;

class LocalitiesTable : public Table
{
    Q_OBJECT

public:
    LocalitiesTable(QObject *parent = Q_NULLPTR);
    LocalitiesTable(QSqlDatabase db, QObject *parent = Q_NULLPTR);
    virtual ~LocalitiesTable();

    QString tableName() const Q_DECL_OVERRIDE;
    QString primaryField() const Q_DECL_OVERRIDE;
    int getColPosition(const QString &columnName) const Q_DECL_OVERRIDE;
    QString getColName(const int position, const bool withTableName = false) const Q_DECL_OVERRIDE;

    std::experimental::optional<LocalityData> getLocalityData(const DbConstants::milk_id localityId) const;
    Q_INVOKABLE Locality *getLocality(const qlonglong localityId);
    Q_INVOKABLE bool insert(int position, Locality *locality);
    Q_INVOKABLE bool append(Locality *locality);
    Q_INVOKABLE bool update(Locality *locality) const;
    Q_INVOKABLE bool setName(const DbConstants::milk_id localityId, const QString &localityName) const;
    Q_INVOKABLE bool setDescription(const DbConstants::milk_id localityId, const QString &description) const;

private:
    LocalitiesDao *dao() const;

    static LocalityData fromRecord(const QSqlRecord &record);
};

DB_END_NAMESPACE

#endif // LOCALITY_TABLE_H
