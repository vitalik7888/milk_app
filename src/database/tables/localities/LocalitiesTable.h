#ifndef LOCALITY_TABLE_H
#define LOCALITY_TABLE_H

#include "dbconstants.h"
#include "base/Table.h"
#include "locality.h"

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

    LocalityData getLocality(const milk_id localityId) const;
    Q_INVOKABLE void insert(int index, Locality *locality);
    Q_INVOKABLE void append(Locality *locality);
    Q_INVOKABLE void update(Locality *locality) const;
    void setName(const milk_id localityId, const QString &localityName) const;
    void setDescription(const milk_id localityId, const QString &description) const;

private:
    LocalitiesDao *dao() const;
};

DB_END_NAMESPACE

#endif // LOCALITY_TABLE_H
