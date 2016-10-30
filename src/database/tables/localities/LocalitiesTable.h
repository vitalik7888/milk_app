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
    QSqlField primaryField() const Q_DECL_OVERRIDE;

    QString getColName(const LocalityTableColumns position, const bool withTableName = false) const;

    Locality getLocality(const milk_id localityId) const;
    void insert(const Locality &locality);
    void update(const Locality &locality) const;
    bool setName(const milk_id localityId, const QString &localityName) const;
    bool setDescription(const milk_id localityId, const QString &description) const;

private:
    LocalitiesDao *dao() const;
};

DB_END_NAMESPACE

#endif // LOCALITY_TABLE_H
