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
LocalitiesDao::LocalitiesDao(LocalitiesTable *table):
    Dao(table) {}

std::experimental::optional<LocalityData> LocalitiesDao::get(const milk_id id) const {
    QSqlQuery query(m_table->database());
    query.prepare(QString("%1 WHERE %2 = ?")
                  .arg(Utils::Main::getSelectStr(TABLE_NAME, { FN_NAME, FN_DESCRIPTION })).arg(FN_ID));
    query.addBindValue(id);

    if (query.exec() && query.first())
    {
        return LocalityData(id,
                            query.value(FN_NAME).toString(),
                            query.value(FN_DESCRIPTION).toString()
                            );
    } else
        _error(QString("Отсутствует населенный пункт с id = %1").arg(id));

    return {};
}

bool LocalitiesDao::insert(const LocalityData &data) const{
    QSqlQuery query(m_table->database());
    query.prepare(Utils::Main::getPrepInsertStr(TABLE_NAME, { FN_NAME, FN_DESCRIPTION }));
    query.addBindValue(data.name());
    query.addBindValue(data.description());

    if (!query.exec()) {
        _error(query.lastError().text());
        return false;
    }

    return true;
}

bool LocalitiesDao::update(const LocalityData &data) const{
    QSqlQuery query(m_table->database());
    query.prepare(QString("%1 WHERE %2 = ?")
                  .arg(Utils::Main::getPrepUpdateStr(TABLE_NAME, { FN_NAME, FN_DESCRIPTION }))
                  .arg(FN_ID));
    query.addBindValue(data.name());
    query.addBindValue(data.description());
    query.addBindValue(data.id());

    if (!query.exec()) {
        _error(query.lastError().text());
        return false;
    }

    return true;
}

//--------------------------------------------------------------------------------------------------
LocalitiesTable::LocalitiesTable(QObject *parent) : LocalitiesTable(QSqlDatabase(), parent) {}

LocalitiesTable::LocalitiesTable(QSqlDatabase db, QObject *parent):
    Table(new LocalitiesDao(this), db, parent)
{
    setObjectName("LocalitiesTable");
    qDebug() << "init " + objectName();

    setQuery(selectAll());
}

LocalitiesTable::~LocalitiesTable()
{
    qDebug() << "delete " + objectName();
}

QString LocalitiesTable::tableName() const
{
    return TABLE_NAME;
}

std::experimental::optional<LocalityData> LocalitiesTable::getLocalityData(const milk_id localityId) const
{
    const auto data = dao()->get(localityId);
    if (!data)
        emit error(QString("Отсутствует населенный пункт с id = %1").arg(localityId));

    return data;
}

Locality *LocalitiesTable::getLocality(const qlonglong localityId)
{
    const auto data = dao()->get(localityId);
    if (!data)
        return Q_NULLPTR;

    return new Locality(data.value(), this);
}

bool LocalitiesTable::insert(int position, Locality *locality)
{
    if(position < 0 || position > rowCount()) {
        return false;
    }

    emit beginInsertRows(QModelIndex(), position, position);
    const bool isOk = dao()->insert(locality->data());
    emit endInsertRows();

    return isOk;
}

bool LocalitiesTable::append(Locality *locality)
{
    return insert(rowCount(), locality);
}

bool LocalitiesTable::update(Locality *locality) const
{
    return dao()->update(locality->data());
}

bool LocalitiesTable::setName(const milk_id localityId, const QString &localityName) const
{
    return m_dao->updateValue(FN_ID, localityId, localityName);
}

bool LocalitiesTable::setDescription(const milk_id localityId, const QString &description) const
{
    return m_dao->updateValue(FN_DESCRIPTION, localityId, description);
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
