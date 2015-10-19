#include "Database.h"

#include <QFile>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>


Database::Database(QObject *parent) :
    QObject(parent),
    m_db(QSqlDatabase::addDatabase("QSQLITE"))
{
    setObjectName("Database");
    qDebug() << "init " + this->objectName();
}

Database::~Database()
{
    qDebug() << "delete " + objectName();
}

bool Database::openDb(const QString &dbPath)
{
    m_db.close();

    m_db.setDatabaseName(dbPath);
    if (m_db.open()) {
        QSqlQuery query("PRAGMA foreign_keys = ON", m_db);
        if (!query.exec())
            qDebug() << "Не удалось включить поддержку внешнего ключа";

        /*if (isTablesCreated()) {
            clearTables();
            refreshTables();
        } else {
            createTables();
        }*/
        removeTables();
        createTables();

        return true;
    }

    return false;
}

QSqlError Database::lastError() const
{
    return m_db.lastError();
}

QString Database::choosenDatabase() const
{
    return m_db.databaseName();
}

LocalitiesTable *Database::localities() const
{
    return qobject_cast<LocalitiesTable *>(m_tables[(int)Tables::localities]);
}

DeliverersTable *Database::deliverers() const
{
    return qobject_cast<DeliverersTable *>(m_tables[(int)Tables::deliverers]);
}

MilkPointsTable *Database::milkPoints() const
{
    return qobject_cast<MilkPointsTable *>(m_tables[(int)Tables::milk_points]);
}

MilkReceptionTable *Database::milkReception() const
{
    return qobject_cast<MilkReceptionTable *>(m_tables[(int)Tables::milk_reception]);
}

QVector<Table *> Database::tables() const
{
    return m_tables;
}

bool Database::isTablesCreated() const
{
    return !m_tables.isEmpty();
}

void Database::removeTables()
{
    /*if (!m_tables.empty()) {
        qDeleteAll(m_tables);
        m_tables.clear();
    }*/
    for (Table *table : m_tables)
        table->deleteLater();
    m_tables.clear();
}

void Database::createTables()
{
    if (!m_tables.isEmpty())
        return;

    auto localities = new LocalitiesTable(this, m_db);
    auto deliverers = new DeliverersTable(localities, m_db);
    auto milkPoints = new MilkPointsTable(localities, m_db);
    auto milkReception = new MilkReceptionTable(deliverers, milkPoints, m_db);

    m_tables.append(localities);
    m_tables.append(deliverers);
    m_tables.append(milkPoints);
    m_tables.append(milkReception);
}

void Database::clearTables()
{
    for (auto table: m_tables) {
        table->clear();
        qDebug().nospace() << "clear table " << table->tableName();
    }
}

void Database::refreshTables()
{
    for (auto table: m_tables) {
        table->refresh();
        qDebug().nospace() << "refresh table " << table->tableName();
    }
}

