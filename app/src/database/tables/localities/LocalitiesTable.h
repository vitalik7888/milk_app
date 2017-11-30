#ifndef LOCALITY_TABLE_H
#define LOCALITY_TABLE_H

#include "DbConstants.h"
#include "base/Table.h"
#include "Locality.h"

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

    std::experimental::optional<LocalityData> getLocalityData(const int localityId) const;
    Q_INVOKABLE Locality *getLocality(const int localityId);
    Q_INVOKABLE bool insert(int position, Locality *locality);
    Q_INVOKABLE bool append(Locality *locality);
    Q_INVOKABLE virtual QVariant get(const int row) Q_DECL_OVERRIDE;
    Q_INVOKABLE bool set(const int row, Locality *locality);

private:
    LocalitiesDao *dao() const;

    static LocalityData fromRecord(const QSqlRecord &record);
};

DB_END_NAMESPACE

#endif // LOCALITY_TABLE_H
