#include "Database.h"

// Qt
#include <QFile>
#include <QSqlQuery>
#include <QDebug>

USE_DB_NAMESPACE
using DC = DbConstants;


Database::Database(QObject *parent) :
    QObject(parent),
    m_db(QSqlDatabase::addDatabase("QSQLITE")),
    m_localities(Q_NULLPTR),
    m_deliverers(Q_NULLPTR),
    m_milkPoints(Q_NULLPTR),
    m_milkReception(Q_NULLPTR)
{
    setObjectName("Database");
}

Database::~Database()
{
    removeTables();
}

bool Database::openDb(const QString &dbPath)
{
    m_db.close();

    // !!!! If using sqlite !!!
    const bool isFileDbExists = QFile::exists(dbPath);
    if (!isFileDbExists)
        createDb(dbPath);
    else {
        m_db.setDatabaseName(dbPath);
        m_db.open();
    }

    if (m_db.isOpen()) {
        m_dbPath = dbPath;
        emit dbPathChanged(m_dbPath);

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

void Database::createDb(const QString &filePath)
{
    m_db.setDatabaseName(filePath);
    if (m_db.open()) {
        qDebug() << "Creating milk database '" + filePath + "'...";

        QSqlQuery query(m_db);
        auto execQuery = [this, &query](const QString &_queryStr) {
            if (!query.exec(_queryStr))
                _error(query.lastError().text());
        };

        execQuery("PRAGMA foreign_keys = off;");
        execQuery("BEGIN TRANSACTION;");
        execQuery(DC::TL_CREATE_TABLE_SQL);
        execQuery(DC::TMP_CREATE_TABLE_SQL);
        execQuery(DC::TD_CREATE_TABLE_SQL);
        execQuery(DC::TMR_CREATE_TABLE_SQL);
        execQuery(DC::dropIndexIfExistsSql(DC::INDEX_RECEPT_DELIV));
        execQuery(DC::CREATE_INDEX_RECEPT_DELIV_SQL);
        execQuery(DC::dropIndexIfExistsSql(DC::INDEX_RECEPT_POINT));
        execQuery(DC::CREATE_INDEX_RECEPT_POINT_SQL);
        execQuery("COMMIT TRANSACTION;");
        execQuery("PRAGMA foreign_keys = on;");

        qDebug() << "db created";
    } else {
        _error(m_db.lastError().text());
    }
}

void Database::removeTables()
{
    if (!isTablesCreated())
        return;

    qDebug() << "Removing tables...";

    for (Table *table : m_tables)
        table->deleteLater();
    m_tables.clear();

    qDebug() << "tables removed";
}

void Database::createTables()
{
    if (!m_tables.isEmpty())
        return;

    qDebug() << "Creating tables...";

    m_localities = new LocalitiesTable(m_db, this);
    m_deliverers = new DeliverersTable(m_localities, m_db, this);
    m_milkPoints = new MilkPointsTable(m_localities, m_db, this);
    m_milkReception = new MilkReceptionTable(m_deliverers, m_milkPoints, m_db, this);

    m_tables.append({m_localities, m_deliverers, m_milkPoints, m_milkReception});

    emit localitiesChanged(m_localities);
    emit deliverersChanged(m_deliverers);
    emit milkPointsChanged(m_milkPoints);
    emit milkReceptionChanged(m_milkReception);

    qDebug() << "tables created";
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

void Database::_error(const QString &errorDescription) const
{
    qDebug() << errorDescription;
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

