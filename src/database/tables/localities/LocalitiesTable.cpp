#include "LocalitiesTable.h"

#include "localitiesdao.h"
#include "Utils.h"
// Qt
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>

USE_DB_NAMESPACE

static const char *TABLE_NAME = "localities";
static const char *FN_ID = "id";
static const char *FN_NAME = "name";
static const char *FN_DESCRIPTION = "description";

//--------------------------------------------------------------------------------------------------
LocalitiesDao::LocalitiesDao(const QSqlDatabase &db):
    Dao(TABLE_NAME, FN_ID, db) {}

Locality LocalitiesDao::get(const milk_id id) const {
    QSqlQuery query(m_db);
    query.prepare(QString("%1 WHERE %2 = ?")
                  .arg(Utils::Main::getSelectStr(TABLE_NAME, { FN_NAME, FN_DESCRIPTION })).arg(FN_ID));
    query.addBindValue(id);

    Locality data;
    if (query.exec() && query.first())
    {
        data.setId(id);
        data.setName(query.value(0).toString());
        data.setDescription(query.value(1).toString());
    } else {
        const auto err = QString("Отсутствует населенный пункт с id = %1").arg(id);
        qDebug() << err;
        throw err;
    }

    return data;
}

void LocalitiesDao::insert(const Locality &data) {
    QSqlQuery query(m_db);
    query.prepare(Utils::Main::getPrepInsertStr(TABLE_NAME, { FN_NAME, FN_DESCRIPTION }));
    query.addBindValue(data.name());
    query.addBindValue(data.description());

    if (!query.exec()) {
        const auto err = query.lastError().text();
        qDebug() << err;
        throw err;
    }
}

void LocalitiesDao::update(const Locality &data) {
    QSqlQuery query;
    query.prepare(QString("%1 WHERE %2 = ?")
                  .arg(Utils::Main::getPrepUpdateStr(TABLE_NAME, { FN_NAME, FN_DESCRIPTION }))
                  .arg(FN_ID));
    query.addBindValue(data.name());
    query.addBindValue(data.description());
    query.addBindValue(data.id());

    if (!query.exec()) {
        const auto err = query.lastError().text();
        qDebug() << err;
        throw err;
    }
}

//--------------------------------------------------------------------------------------------------
LocalitiesTable::LocalitiesTable(QObject *parent, QSqlDatabase db):
    Table(new LocalitiesDao(db), parent, db)
{
    setObjectName("LocalitiesTable");
    qDebug() << "init " + objectName();

    setQuery(QString("SELECT * FROM %1").arg(TABLE_NAME));
}

LocalitiesTable::~LocalitiesTable()
{
    qDebug() << "delete " + objectName();
}

QString LocalitiesTable::tableName() const
{
    return TABLE_NAME;
}

Locality LocalitiesTable::getLocality(const milk_id localityId) const
{
    return dao()->get(localityId);
}

void LocalitiesTable::insert(const Locality &locality)
{
    dao()->insert(locality);
}

void LocalitiesTable::update(const Locality &locality) const
{
    dao()->update(locality);
}

void LocalitiesTable::setName(const milk_id localityId, const QString &localityName) const
{
    m_dao->updateValue(FN_ID, localityId, localityName);
}

void LocalitiesTable::setDescription(const milk_id localityId, const QString &description) const
{
    m_dao->updateValue(FN_DESCRIPTION, localityId, description);
}

QString LocalitiesTable::primaryField() const
{
    return FN_ID;
}

QString LocalitiesTable::getColName(const int position, const bool withTableName) const
{
    QString columnName;
    switch (position) {
    case LocalityTableColumns::LT_ID:
        columnName = FN_ID;
        break;
    case LocalityTableColumns::LT_NAME:
        columnName = FN_NAME;
        break;
    case LocalityTableColumns::LT_DESCRIPTION:
        columnName = FN_DESCRIPTION;
        break;
    default:
        columnName = "";
        break;
    }

    return withTableName ? QString("%1.%2").arg(TABLE_NAME).arg(columnName) : columnName;
}

LocalitiesDao *LocalitiesTable::dao() const
{
    return dynamic_cast<LocalitiesDao *>(m_dao.data());
}

int db::LocalitiesTable::getColPosition(const QString &columnName) const
{
    if (columnName == FN_ID)
        return LocalityTableColumns::LT_ID;
    if (columnName == FN_NAME)
        return LocalityTableColumns::LT_NAME;
    if (columnName == FN_DESCRIPTION)
        return LocalityTableColumns::LT_DESCRIPTION;
    return -1;
}
