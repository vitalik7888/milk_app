#ifndef LOCALITIES_DAO_H
#define LOCALITIES_DAO_H

#include "DaoSql.h"

DB_BEGIN_NAMESPACE

class LocalitiesModel;


class DBLIBRARYSHARED_EXPORT LocalitiesDao: public DaoSql
{
    Q_OBJECT
public:
    LocalitiesDao(QObject *parent = Q_NULLPTR);

    QString getCreateTableStr() const Q_DECL_OVERRIDE;

private:
    DaoItem fromRecord(const QSqlRecord &record);

private:
    QString _tableName() const Q_DECL_OVERRIDE;
    QString _primaryFieldName() const Q_DECL_OVERRIDE;
    QStringList _fieldsNames() const Q_DECL_OVERRIDE;

    bool _insert(MilkBaseItem *item) Q_DECL_OVERRIDE;
    bool _update(const MilkBaseItem *item) Q_DECL_OVERRIDE;
};

DB_END_NAMESPACE

#endif // LOCALITIESDAO_H
