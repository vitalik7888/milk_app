#ifndef MILK_TABLE
#define MILK_TABLE

#include "DbConstants.h"
// Qt
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlField>
#include <QVector>
#include <QString>

DB_BEGIN_NAMESPACE
    class Dao;

class Table : public QSqlQueryModel
{
    Q_OBJECT
    Q_PROPERTY(QString tableName READ tableName CONSTANT)
    Q_PROPERTY(QString primaryField READ primaryField CONSTANT)
    Q_PROPERTY(bool getIsFetchOnRefresh READ getIsFetchOnRefresh WRITE setIsFetchOnRefresh)

public:
    Table(Dao *dao, QSqlDatabase db = QSqlDatabase(), QObject *parent = Q_NULLPTR);
    virtual ~Table();

    QSqlDatabase database() const;

    virtual QString tableName() const = 0;
    Q_INVOKABLE virtual QString getColName(const int position, const bool withTableName = false) const = 0;
    Q_INVOKABLE virtual int getColPosition(const QString &columnName) const = 0;
    virtual QString primaryField() const = 0;

    Q_INVOKABLE virtual QString selectAll() const;
    Q_INVOKABLE bool isEmpty() const;

    virtual Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    virtual QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

    Q_INVOKABLE bool remove(const DbConstants::milk_id id) const;
    Q_INVOKABLE bool removeAll() const;

    Q_INVOKABLE virtual void refresh();

    bool getIsFetchOnRefresh() const;
    void setIsFetchOnRefresh(const bool isFetchOnRefresh);

protected:
    QSqlDatabase m_db;
    QScopedPointer<Dao> m_dao;

    bool m_isFetchOnRefresh;

signals:
    void error(const QString &error) const;
    void startRefresh();
    void refreshed();
};

DB_END_NAMESPACE

#endif // MILK_TABLE

