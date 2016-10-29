#ifndef LOCALITY_TABLE_H
#define LOCALITY_TABLE_H

#include "dbconstants.h"
#include "base/Table.h"
#include "Locality.h"

DB_BEGIN_NAMESPACE

class LocalitiesTable : public Table
{
    Q_OBJECT
public:
    LocalitiesTable(QObject *parent, QSqlDatabase db);
    ~LocalitiesTable();

    QString tableName() const Q_DECL_OVERRIDE;
    QSqlField primaryField() const Q_DECL_OVERRIDE;

    QString getNameColumnId(const bool withTableName = false) const;
    QString getNameColumnName(const bool withTableName = false) const;
    QString getNameColumnDescription(const bool withTableName = false) const;

    QSqlField getFieldId() const;
    QSqlField getFieldName() const;
    QSqlField getFieldDescription() const;

    Locality getLocality(const milk_id localityId) const;
    bool insert(const Locality &locality);
    bool update(const Locality &locality) const;
    bool setName(const milk_id localityId, const QString &localityName) const;
    bool setDescription(const milk_id localityId, const QString &description) const;


private:
    void initColumns() Q_DECL_OVERRIDE;
};

DB_END_NAMESPACE

#endif // LOCALITY_TABLE_H
