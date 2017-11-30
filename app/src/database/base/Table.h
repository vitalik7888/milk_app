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
    virtual QString getColName(const int position, const bool withTableName = false) const = 0;
    virtual int getColPosition(const QString &columnName) const = 0;
    virtual QString primaryField() const = 0;

    virtual QString selectAll() const;
    bool isEmpty() const;

    virtual Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    virtual QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;
    virtual bool removeRows(int row, int count, const QModelIndex &parent) Q_DECL_OVERRIDE;

    Q_INVOKABLE bool append(const QVariant &data);
    Q_INVOKABLE bool removeAll();
    Q_INVOKABLE virtual QVariant get(const int row) = 0;
    Q_INVOKABLE bool insert(int position, const QVariant &data);
    Q_INVOKABLE bool remove(const int row);
    Q_INVOKABLE virtual bool set(const int row, const QVariant &data);
    Q_INVOKABLE QVariant getValue(const int row, const int column) const;
    Q_INVOKABLE bool setValue(const int row, const int column, const QVariant &value, const int role = Qt::EditRole);

    bool getIsFetchOnRefresh() const;
    void setIsFetchOnRefresh(const bool isFetchOnRefresh);

public slots:
    virtual void refresh();

protected:
    QSqlDatabase m_db;
    QScopedPointer<Dao> m_dao;

    bool m_isFetchOnRefresh;

    DbConstants::milk_id getIdByRow(const int row) const;

signals:
    void error(const QString &error) const;
    void startRefresh();
    void refreshed();
};

DB_END_NAMESPACE

#endif // MILK_TABLE

