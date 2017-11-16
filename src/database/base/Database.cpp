#include "Database.h"

// Qt
#include <QFile>
#include <QSqlQuery>
#include <QDebug>

USE_DB_NAMESPACE


Database::Database(QObject *parent) :
    QObject(parent),
    m_db(QSqlDatabase::addDatabase("QSQLITE")),
    m_localities(Q_NULLPTR),
    m_deliverers(Q_NULLPTR),
    m_milkPoints(Q_NULLPTR),
    m_milkReception(Q_NULLPTR)
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

        removeTables();
        createTables();

        emit dbOpened();

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
    return m_localities;
}

DeliverersTable *Database::deliverers() const
{
    return m_deliverers;
}

MilkPointsTable *Database::milkPoints() const
{
    return m_milkPoints;
}

MilkReceptionTable *Database::milkReception() const
{
    return m_milkReception;
}

int Database::tablesCount() const
{
    return m_tables.size();
}

QQmlListProperty<Table> Database::tables()
{
    return QQmlListProperty<Table>(this, this, &Database::_tablesCount, &Database::_getTable);
}

bool Database::isTablesCreated() const
{
    return !m_tables.isEmpty();
}

void Database::removeTables()
{
    for (Table *table : m_tables)
        table->deleteLater();
    m_tables.clear();
}

void Database::createTables()
{
    if (!m_tables.isEmpty())
        return;

    m_localities = new LocalitiesTable(m_db, this);
    m_deliverers = new DeliverersTable(m_localities, m_db, this);
    m_milkPoints = new MilkPointsTable(m_localities, m_db, this);
    m_milkReception = new MilkReceptionTable(m_deliverers, m_milkPoints, m_db, this);

    m_tables.append({m_localities, m_deliverers, m_milkPoints, m_milkReception});

    emit localitiesChanged(m_localities);
    emit deliverersChanged(m_deliverers);
    emit milkPointsChanged(m_milkPoints);
    emit milkReceptionChanged(m_milkReception);
}

void Database::clearTables()
{
    for (auto table: m_tables) {
        table->clear();
        qDebug().nospace() << "clear table " << table->tableName();
    }
}

Table *Database::getTable(const int position) const
{
    return m_tables[position];
}

void Database::_appendTable(QQmlListProperty<Table> *list, Table *table)
{
    reinterpret_cast< Database* >(list->data)->appendTable(table);
}

int Database::_tablesCount(QQmlListProperty<Table> *list)
{
    return reinterpret_cast< Database* >(list->data)->tablesCount();
}

Table *Database::_getTable(QQmlListProperty<Table> *list, int position)
{
    return reinterpret_cast< Database* >(list->data)->getTable(position);
}

void Database::_removeTables(QQmlListProperty<Table> *list)
{
    reinterpret_cast< Database* >(list->data)->removeTables();
}

void Database::refreshTables()
{
    for (auto table: m_tables) {
        table->refresh();
        qDebug().nospace() << "refresh table " << table->tableName();
    }
}

void Database::appendTable(Table *table)
{
    m_tables.append(table);
}

