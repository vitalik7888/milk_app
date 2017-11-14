#ifndef MILKPOINTS_TABLE_H
#define MILKPOINTS_TABLE_H

#include "base/Table.h"
#include "milkpoint.h"

#include <experimental/optional>

DB_BEGIN_NAMESPACE
    class MilkPointDao;
    class LocalitiesTable;

class MilkPointsTable: public Table
{
    Q_OBJECT

public:
    MilkPointsTable(QObject *parent = Q_NULLPTR);
    MilkPointsTable(LocalitiesTable *localities, QSqlDatabase db, QObject *parent = Q_NULLPTR);
    virtual ~MilkPointsTable();

    QString tableName() const Q_DECL_OVERRIDE;
    QString primaryField() const Q_DECL_OVERRIDE;
    int getColPosition(const QString &columnName) const Q_DECL_OVERRIDE;
    QString getColName(const int position, const bool withTableName = false) const Q_DECL_OVERRIDE;

    std::experimental::optional<MilkPointData> getMilkPointData(const milk_id milkPointId) const;
    Q_INVOKABLE MilkPoint *getMilkPoint(const qlonglong milkPointId);
    Q_INVOKABLE void insert(int index, MilkPoint *milkPoint);
    Q_INVOKABLE void append(MilkPoint *milkPoint);
    Q_INVOKABLE void update(MilkPoint *milkPoint) const;
    void setName(const milk_id milkPointId, const QString &milkPointName) const;
    void setDescription(const milk_id milkPointId, const QString &description) const;

    LocalitiesTable *localities() const;

private:
    LocalitiesTable *m_localities;

    MilkPointDao *dao() const;
};

DB_END_NAMESPACE

#endif // MILKPOINTS_TABLE_H
