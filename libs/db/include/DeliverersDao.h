#ifndef DELIVERERS_DAO_H
#define DELIVERERS_DAO_H

#include "DaoSql.h"

DB_BEGIN_NAMESPACE
    class DeliverersModel;


class DBLIBRARYSHARED_EXPORT DeliverersDao: public DaoSql
{
    Q_OBJECT
public:
    explicit DeliverersDao(QObject *parent = Q_NULLPTR);

    QString getCreateTableStr() const Q_DECL_OVERRIDE;

protected:
    virtual DaoItem fromRecord(const QSqlRecord &record) Q_DECL_OVERRIDE;

private:
    QString _tableName() const Q_DECL_OVERRIDE;
    QString _primaryFieldName() const Q_DECL_OVERRIDE;
    QStringList _fieldsNames() const Q_DECL_OVERRIDE;

    bool _insert(MilkBaseItem *item);
    bool _update(const MilkBaseItem *data);
};

DB_END_NAMESPACE

#endif // DELIVERERSDAO_H
