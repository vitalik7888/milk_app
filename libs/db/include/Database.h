#ifndef DATABASE_H
#define DATABASE_H

#include "DbConstants.h"
#include "LocalitiesTable.h"
#include "DeliverersTable.h"
#include "MilkPointsTable.h"
#include "MilkReceptionTable.h"
// Qt
#include <QtSql/QSqlDatabase>
#include <QSqlError>
#include <QQmlListProperty>

DB_BEGIN_NAMESPACE


class DBLIBRARYSHARED_EXPORT Database : public QObject
{
    Q_OBJECT
    Q_PROPERTY(LocalitiesTable *localities READ localities NOTIFY localitiesChanged)
    Q_PROPERTY(DeliverersTable *deliverers READ deliverers NOTIFY deliverersChanged)
    Q_PROPERTY(MilkPointsTable *milkPoints READ milkPoints NOTIFY milkPointsChanged)
    Q_PROPERTY(MilkReceptionTable *milkReception READ milkReception NOTIFY milkReceptionChanged)
    Q_PROPERTY(QQmlListProperty<Table> tables READ tables)
    Q_PROPERTY(QString dbPath READ dbPath NOTIFY dbPathChanged)

public:
    explicit Database(QObject *parent = nullptr);
    virtual ~Database();

    Q_INVOKABLE bool openDb(const QString &dbPath = ":memory:");
    Q_INVOKABLE QSqlError lastError() const;
    Q_INVOKABLE QString choosenDatabase() const;

    QQmlListProperty<Table> tables();
    LocalitiesTable *localities() const;
    DeliverersTable *deliverers() const;
    MilkPointsTable *milkPoints() const;
    MilkReceptionTable *milkReception() const;
    int tablesCount() const;
    Q_INVOKABLE bool isTablesCreated() const;

    QString dbPath() const { return m_dbPath; }

    QSqlDatabase getSqlDb() const;

signals:
    void dbOpened();
    void localitiesChanged(LocalitiesTable * localities);
    void deliverersChanged(DeliverersTable * deliverers);
    void milkPointsChanged(MilkPointsTable * milkPoints);
    void milkReceptionChanged(MilkReceptionTable * milkReception);
    void tablesChanged(QQmlListProperty<Table> tables);
    void dbPathChanged(QString dbPath);

private:
    QSqlDatabase m_db;
    QString m_dbPath;
    QList<Table *> m_tables;
    LocalitiesTable *m_localities;
    DeliverersTable *m_deliverers;
    MilkPointsTable *m_milkPoints;
    MilkReceptionTable *m_milkReception;

    void createDb(const QString &filePath);

    void removeTables();
    void createTables();
    void refreshTables();

    void appendTable(Table *table);
    void clearTables();
    Table *getTable(const int position) const;

    static void _appendTable(QQmlListProperty<Table> *list, Table *table);
    static int _tablesCount(QQmlListProperty<Table> *list);
    static Table *_getTable(QQmlListProperty<Table> *list, int position);
    static void _removeTables(QQmlListProperty<Table> *list);

    void _error(const QString &errorDescription) const;
};

DB_END_NAMESPACE

#endif // DATABASE_H
