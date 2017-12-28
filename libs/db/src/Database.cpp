#include "Database.h"

//#include "LocalitiesDao.h"
//#include "MilkpointsDao.h"
//#include "DeliverersDao.h"
//#include "MilkReceprionDao.h"
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
    createDaos();
}

Database::~Database()
{
    removeModels();
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
            qWarning() << "Не удалось включить поддержку внешнего ключа";

        removeModels();
        createModels();

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

LocalitiesModel *Database::localities() const
{
    return m_localities;
}

DeliverersModel *Database::deliverers() const
{
    return m_deliverers;
}

MilkPointsModel *Database::milkPoints() const
{
    return m_milkPoints;
}

MilkReceptionModel *Database::milkReception() const
{
    return m_milkReception;
}

int Database::modelsCount() const
{
    return m_models.size();
}

QQmlListProperty<MilkModel> Database::_models()
{
    return QQmlListProperty<MilkModel>(this, this, &Database::_modelsCount, &Database::_getModel);
}

bool Database::isModelsCreated() const
{
    return !m_models.isEmpty();
}

QSqlDatabase Database::getSqlDb() const
{
    return m_db;
}

void Database::createDb(const QString &filePath)
{
    m_db.setDatabaseName(filePath);
    if (m_db.open()) {
        qInfo() << "Creating milk database '" + filePath + "'...";

        QSqlQuery query(m_db);
        auto execQuery = [this, &query](const QString &_queryStr) {
            if (!query.exec(_queryStr))
                _error(query.lastError().text());
        };

        execQuery("PRAGMA foreign_keys = off;");
        execQuery("BEGIN TRANSACTION;");
        m_localitiesDao->createTable();
        m_milkPointsDao->createTable();
        m_deliverersDao->createTable();
        m_milkReceptionDao->createTable();
        execQuery(DC::dropIndexIfExistsSql(DC::INDEX_RECEPT_DELIV));
        execQuery(DC::CREATE_INDEX_RECEPT_DELIV_SQL);
        execQuery(DC::dropIndexIfExistsSql(DC::INDEX_RECEPT_POINT));
        execQuery(DC::CREATE_INDEX_RECEPT_POINT_SQL);
        execQuery("COMMIT TRANSACTION;");
        execQuery("PRAGMA foreign_keys = on;");

        qInfo() << "db created";
    } else {
        _error(m_db.lastError().text());
    }
}

void Database::createDaos()
{
    m_localitiesDao.reset(new LocalitiesDao());
    m_deliverersDao.reset(new DeliverersDao());
    m_milkPointsDao.reset(new MilkPointDao());
    m_milkReceptionDao.reset(new MilkReceptionDao());
    m_localitiesDao->setDb(m_db);
    m_deliverersDao->setDb(m_db);
    m_milkPointsDao->setDb(m_db);
    m_milkReceptionDao->setDb(m_db);
}

void Database::removeModels()
{
    if (!isModelsCreated())
        return;

    qInfo() << "Removing tables...";

    for (MilkModel *table : m_models)
        table->deleteLater();
    m_models.clear();

    qInfo() << "tables removed";
}

void Database::createModels()
{
    if (!m_models.isEmpty())
        return;

    qInfo() << "Creating tables...";

    m_localities = new LocalitiesModel(this);
    m_localities->setDao(m_localitiesDao.get());
    m_deliverers = new DeliverersModel(m_localities, this);
    m_deliverers->setDao(m_deliverersDao.get());
    m_milkPoints = new MilkPointsModel(m_localities, this);
    m_milkPoints->setDao(m_milkPointsDao.get());
    m_milkReception = new MilkReceptionModel(m_deliverers, m_milkPoints, this);
    m_milkReception->setDao(m_milkReceptionDao.get());

    m_models.append({m_localities, m_deliverers, m_milkPoints, m_milkReception});

    refreshModels();

    emit localitiesChanged(m_localities);
    emit deliverersChanged(m_deliverers);
    emit milkPointsChanged(m_milkPoints);
    emit milkReceptionChanged(m_milkReception);

    qInfo() << "tables created";
}

void Database::clearModels()
{
    qInfo() << "Clear models";

    for (auto model: m_models) {
        model->clear();
    }
}

MilkModel *Database::getModel(const int position) const
{
    return m_models[position];
}

void Database::_appendModel(QQmlListProperty<MilkModel> *list, MilkModel *table)
{
    reinterpret_cast< Database* >(list->data)->appendModel(table);
}

int Database::_modelsCount(QQmlListProperty<MilkModel> *list)
{
    return reinterpret_cast< Database* >(list->data)->modelsCount();
}

MilkModel *Database::_getModel(QQmlListProperty<MilkModel> *list, int position)
{
    return reinterpret_cast< Database* >(list->data)->getModel(position);
}

void Database::_removeModels(QQmlListProperty<MilkModel> *list)
{
    reinterpret_cast< Database* >(list->data)->removeModels();
}

void Database::_error(const QString &errorDescription) const
{
    qWarning() << errorDescription;
}

void Database::refreshModels()
{
    for (auto model: m_models) {
        model->refresh();
    }
    qInfo() << "Models are refreshed";
}

void Database::appendModel(MilkModel *table)
{
    m_models.append(table);
}

