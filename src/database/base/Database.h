#ifndef DATABASE_H
#define DATABASE_H

#include "dbconstants.h"
#include "tables/localities/LocalitiesTable.h"
#include "tables/deliverers/DeliverersTable.h"
#include "tables/milk_points/MilkPointsTable.h"
#include "tables/milk_reception/MilkReceptionTable.h"
// Qt
#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QSqlError>
#include <QQmlListProperty>

DB_BEGIN_NAMESPACE


class Database : public QObject
{
    Q_OBJECT
    Q_PROPERTY(LocalitiesTable *localities READ localities)
    Q_PROPERTY(DeliverersTable *deliverers READ deliverers)
    Q_PROPERTY(MilkPointsTable *milkPoints READ milkPoints)
    Q_PROPERTY(MilkReceptionTable *milkReception READ milkReception)
    Q_PROPERTY(QQmlListProperty<Table> tables READ tables)

    enum class Tables: int {
        localities = 0,
        deliverers,
        milk_points,
        milk_reception
    };
public:
    explicit Database(QObject *parent = nullptr);
    virtual ~Database();

    Q_INVOKABLE bool openDb(const QString &dbPath);
    Q_INVOKABLE QSqlError lastError() const;
    Q_INVOKABLE QString choosenDatabase() const;

    QQmlListProperty<Table> tables();
    LocalitiesTable *localities() const;
    DeliverersTable *deliverers() const;
    MilkPointsTable *milkPoints() const;
    MilkReceptionTable *milkReception() const;

    Q_INVOKABLE bool isTablesCreated() const;

signals:
   void dbOpened();

private:
    QSqlDatabase m_db;
    QList<Table *> m_tables;

    void removeTables();
    void createTables();
    void clearTables();
    void refreshTables();
};

DB_END_NAMESPACE

#endif // DATABASE_H
