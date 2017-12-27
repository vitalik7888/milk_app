#ifndef MILK_POINT_DAO_H
#define MILK_POINT_DAO_H

#include "DaoSql.h"

DB_BEGIN_NAMESPACE

class MilkPointsModel;


class DBLIBRARYSHARED_EXPORT MilkPointDao: public DaoSql {
public:
    MilkPointDao(QObject *parent = Q_NULLPTR);

    QString getCreateTableStr() const Q_DECL_OVERRIDE;

private:
    QString _tableName() const Q_DECL_OVERRIDE;
    QString _primaryFieldName() const Q_DECL_OVERRIDE;
    QStringList _fieldsNames() const Q_DECL_OVERRIDE;


    virtual DaoItem fromRecord(const QSqlRecord &record) Q_DECL_OVERRIDE;
    virtual bool _insert(MilkBaseItem *item) Q_DECL_OVERRIDE;
    virtual bool _update(const MilkBaseItem *item) Q_DECL_OVERRIDE;
};

DB_END_NAMESPACE

#endif // MILKPOINTDAO_H
