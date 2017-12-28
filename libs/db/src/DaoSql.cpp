#include "DaoSql.h"

#include "MilkModel.h"
// Qt
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include <DbUtils.h>

USE_DB_NAMESPACE


DaoSql::DaoSql(QObject *parent):
    QObject(parent)
{

}

DaoSql::~DaoSql()
{

}

DaoItems DaoSql::get(const QString &where, const QString &orderBy)
{
    return fromRecords(getRecords(where, orderBy));
}

bool DaoSql::removeById(const MILK_ID id)
{
    return remove(QString("%1 = %2").arg(primaryFieldName()).arg(id));
}

bool DaoSql::remove(const QString &where)
{
    QSqlQuery query(m_db);
    if (!query.exec(QString("DELETE FROM %1%2")
                    .arg(tableName())
                    .arg(where.isEmpty() ? "" : " WHERE " + where)))
    {
        _error(query.lastError().text());
        return false;
    }

    return true;
}

bool DaoSql::insert(MilkBaseItem *data)
{
    return _insert(data);
}

bool DaoSql::update(const MilkBaseItem *data)
{
    return _update(data);
}

bool DaoSql::updateValue(const int fieldPosition, const MILK_ID id, const QVariant &value)
{
    QSqlQuery query(m_db);
    query.prepare(QString("UPDATE %1 SET %2 = ? WHERE %3 = ?")
                  .arg(tableName())
                  .arg(fieldsNames().at(fieldPosition))
                  .arg(primaryFieldName()));
    query.addBindValue(value);
    query.addBindValue(id);

    if (!query.exec()) {
        _error(query.lastError().text());
        return false;
    }

    return true;
}

void DaoSql::setDb(const QSqlDatabase &db)
{
    m_db = db;
}

bool DaoSql::createTable()
{
    QSqlQuery query(getCreateTableStr());
    if (!query.exec()) {
        _error(query.lastError().text());
        return true;
    }

    return false;
}

void DaoSql::_error(const QString &error_description)
{
    qWarning() << error_description;
    emit sqlError(error_description);
}

QList<MILK_ID> DaoSql::getIds(const QString &where, const QString &orderBy)
{
    QList<MILK_ID> ids;

    QSqlQuery query(QString("SELECT %1 FROM %2%3%4")
                    .arg(primaryFieldName())
                    .arg(tableName())
                    .arg(where.isEmpty() ? "" : " WHERE " + where)
                    .arg(orderBy.isEmpty() ? "" : " ORDER BY " + orderBy),
                    m_db);

    if (query.exec()) {
        while(query.next())
            ids.append(query.value(0).toInt());
    } else
        _error(query.lastError().text());

    return ids;
}

QList<QSqlRecord> DaoSql::getRecords(const QString &where, const QString &orderBy)
{
    QSqlQuery query(QString("SELECT * FROM %1%2%3")
                    .arg(tableName())
                    .arg(where.isEmpty() ? "" : " WHERE " + where)
                    .arg(orderBy.isEmpty() ? "" : " ORDER BY " + orderBy),
                    m_db);

    if (query.exec()) {
        QList<QSqlRecord> records;
        while(query.next())
            records.append(query.record());

        return records;
    } else
        _error(query.lastError().text());

    return {};
}

DaoItems DaoSql::fromRecords(const QList<QSqlRecord> &records)
{
    DaoItems items(new std::vector<DaoItem>());
    for (const auto &record : records)
        items->push_back(std::move(fromRecord(record)));

    return items;
}

QString DaoSql::fieldNameByPosition(const int position, bool withTableName) const
{
    auto fieldName = fieldsNames().at(position);
    if (withTableName)
        fieldName = tableName() + "." + fieldName;

    return fieldName;
}
