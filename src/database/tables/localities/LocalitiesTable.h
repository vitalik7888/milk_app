#ifndef LOCALITY_TABLE_H
#define LOCALITY_TABLE_H

#include "dbconstants.h"
#include "base/Table.h"
#include "Locality.h"

DB_BEGIN_NAMESPACE
    class LocalitiesDao;

class LocalitiesTable : public Table
{
    Q_OBJECT
public:
    LocalitiesTable(QObject *parent, QSqlDatabase db);
    ~LocalitiesTable();

    QString tableName() const Q_DECL_OVERRIDE;
    QString primaryField() const Q_DECL_OVERRIDE;
    int getColPosition(const QString &columnName) const Q_DECL_OVERRIDE;
    QString getColName(const int position, const bool withTableName = false) const Q_DECL_OVERRIDE;


    Locality getLocality(const milk_id localityId) const;
    void insert(const Locality &locality);
    void update(const Locality &locality) const;
    void setName(const milk_id localityId, const QString &localityName) const;
    void setDescription(const milk_id localityId, const QString &description) const;

private:
    LocalitiesDao *dao() const;
};

DB_END_NAMESPACE

#endif // LOCALITY_TABLE_H
