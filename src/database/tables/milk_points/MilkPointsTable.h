#ifndef MILKPOINTS_TABLE_H
#define MILKPOINTS_TABLE_H
#include "dbconstants.h"
#include "base/Table.h"
#include "MilkPoint.h"

DB_BEGIN_NAMESPACE
    class MilkPointDao;
    class LocalitiesTable;

class MilkPointsTable: public Table
{
    Q_OBJECT
public:
    MilkPointsTable(LocalitiesTable *parent, QSqlDatabase db);
    ~MilkPointsTable();

    QString tableName() const Q_DECL_OVERRIDE;
    QSqlField primaryField() const Q_DECL_OVERRIDE;

    QString getColName(const int position, const bool withTableName = false) const Q_DECL_OVERRIDE;

    MilkPointData getMilkPoint(const milk_id milkPointId) const;
    void insert(const MilkPointData &milkPoint);
    void update(const MilkPointData &milkPoint) const;
    bool setName(const milk_id milkPointId, const QString &milkPointName) const;
    bool setDescription(const milk_id milkPointId, const QString &description) const;

    LocalitiesTable *getLocalities() const;

private:
    LocalitiesTable *m_localities;

    void initColumns() Q_DECL_OVERRIDE;

    MilkPointDao *dao() const;
};

DB_END_NAMESPACE

#endif // MILKPOINTS_TABLE_H
