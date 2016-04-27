#ifndef MILKPOINTS_TABLE_H
#define MILKPOINTS_TABLE_H

#include "base/Table.h"
#include "MilkPoint.h"

class LocalitiesTable;


class MilkPointsTable: public Table
{
    Q_OBJECT
public:
    MilkPointsTable(LocalitiesTable *parent, QSqlDatabase db);

    QString tableName() const Q_DECL_OVERRIDE;
    QSqlField primaryField() const Q_DECL_OVERRIDE;

    QString getNameColumnId(const bool withTableName = false) const;
    QString getNameColumnLocalityId(const bool withTableName = false) const;
    QString getNameColumnName(const bool withTableName = false) const;
    QString getNameColumnDescription(const bool withTableName = false) const;

    QSqlField getFieldId() const;
    QSqlField getFieldLocalityId() const;
    QSqlField getFieldName() const;
    QSqlField getFieldDescription() const;

    MilkPoint getMilkPoint(const qint32 milkPointId) const;
    bool insert(const MilkPoint &milkPoint);
    bool update(const MilkPoint &milkPoint) const;
    bool setName(const qint32 milkPointId, const QString &milkPointName) const;
    bool setDescription(const qint32 milkPointId, const QString &description) const;

    LocalitiesTable *getLocalities() const;

private:
    LocalitiesTable *m_localities;

    void initColumns() Q_DECL_OVERRIDE;
};

#endif // MILKPOINTS_TABLE_H
