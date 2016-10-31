#ifndef MILK_TABLE
#define MILK_TABLE

#include "dbconstants.h"
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
public:
    Table(Dao *dao, QObject *parent = Q_NULLPTR, QSqlDatabase db = QSqlDatabase());
    virtual ~Table();

    QSqlDatabase database() const;

    virtual QString tableName() const = 0;
    virtual QString getColName(const int position, const bool withTableName = false) const = 0;
    virtual int getColPosition(const QString &columnName) const = 0;
    virtual QString primaryField() const = 0;

    virtual QString selectAll() const;
    bool isEmpty() const;

    virtual Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;

    bool remove(const milk_id id) const;
    bool removeAll() const;

    virtual void refresh();

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

