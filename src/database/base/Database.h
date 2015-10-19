#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql/QSqlDatabase>

#include "tables/localities/LocalitiesTable.h"
#include "tables/deliverers/DeliverersTable.h"
#include "tables/milk_points/MilkPointsTable.h"
#include "tables/milk_reception/MilkReceptionTable.h"


class Database : public QObject
{
    Q_OBJECT

    enum class Tables: int {
        localities = 0,
        deliverers,
        milk_points,
        milk_reception
    };
public:
    explicit Database(QObject *parent = nullptr);
    ~Database();

    bool openDb(const QString &dbPath);
    QSqlError lastError() const;
    QString choosenDatabase() const;

    QVector<Table *> tables() const;
    LocalitiesTable *localities() const;
    DeliverersTable *deliverers() const;
    MilkPointsTable *milkPoints() const;
    MilkReceptionTable *milkReception() const;

    bool isTablesCreated() const;

private:
    QSqlDatabase m_db;
    QVector<Table *> m_tables;

    void removeTables();
    void createTables();
    void clearTables();
    void refreshTables();
};

#endif // DATABASE_H
