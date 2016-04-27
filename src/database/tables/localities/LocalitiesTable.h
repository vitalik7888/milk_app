#ifndef LOCALITY_TABLE_H
#define LOCALITY_TABLE_H

#include "base/Table.h"
#include "Locality.h"


class LocalitiesTable : public Table
{
    Q_OBJECT
public:
    LocalitiesTable(QObject *parent, QSqlDatabase db);

    QString tableName() const Q_DECL_OVERRIDE;
    QSqlField primaryField() const Q_DECL_OVERRIDE;

    QString getNameColumnId(const bool withTableName = false) const;
    QString getNameColumnName(const bool withTableName = false) const;
    QString getNameColumnDescription(const bool withTableName = false) const;

    QSqlField getFieldId() const;
    QSqlField getFieldName() const;
    QSqlField getFieldDescription() const;

    Locality getLocality(const qlonglong localityId) const;
    bool insert(const Locality &locality);
    bool update(const Locality &locality) const;
    bool setName(const qlonglong localityId, const QString &localityName) const;
    bool setDescription(const qlonglong localityId, const QString &description) const;


private:
    void initColumns() Q_DECL_OVERRIDE;
};

#endif // LOCALITY_TABLE_H
