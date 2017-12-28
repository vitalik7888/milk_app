#ifndef MILK_DAO_H_
#define MILK_DAO_H_

#include "DbConstants.h"
#include <MilkBaseItem.h>
#include <bits/unique_ptr.h>
// Qt
#include <QSqlDatabase>
#include <QSqlRecord>


DB_BEGIN_NAMESPACE

using DaoItem = std::unique_ptr<MilkBaseItem>;
using DaoItems = std::unique_ptr<std::vector<DaoItem>>;

class DBLIBRARYSHARED_EXPORT DaoSql : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString tableName READ tableName CONSTANT)
    Q_PROPERTY(QStringList fieldsNames READ fieldsNames CONSTANT)
    Q_PROPERTY(QString primaryFieldName READ primaryFieldName CONSTANT)

public:
    DaoSql(QObject *parent = Q_NULLPTR);
    virtual ~DaoSql();

    QString tableName() const { return _tableName(); }
    virtual QStringList fieldsNames() const { return _fieldsNames(); }
    virtual QString primaryFieldName() const { return _primaryFieldName(); }
    virtual QString getCreateTableStr() const = 0;

    QSqlDatabase getDb() const { return m_db; }
    void setDb(const QSqlDatabase &db);

    bool createTable();

    QList<MILK_ID> getIds(const QString &where, const QString &orderBy = {});
    DaoItems get(const QString &where = {}, const QString &orderBy = {});
    bool removeById(const MILK_ID id);
    bool remove(const QString &where = {});
    bool insert(MilkBaseItem *data);
    bool update(const MilkBaseItem *data);
    bool updateValue(const int fieldPosition, const MILK_ID id, const QVariant &value);

signals:
    void sqlError(const QString &errorDescription);

protected:
    QSqlDatabase m_db;

    void _error(const QString &error_description);

    QList<QSqlRecord> getRecords(const QString &where, const QString &orderBy = {});
    DaoItems fromRecords(const QList<QSqlRecord> &records);
    virtual DaoItem fromRecord(const QSqlRecord &record) = 0;

    QString fieldNameByPosition(const int position, bool withTableName) const;

private:
    virtual QString _tableName() const = 0;
    virtual QString _primaryFieldName() const = 0;
    virtual QStringList _fieldsNames() const = 0;

    virtual bool _insert(MilkBaseItem *data) = 0;
    virtual bool _update(const MilkBaseItem *data) = 0;
};

DB_END_NAMESPACE

#endif // DAO_H
