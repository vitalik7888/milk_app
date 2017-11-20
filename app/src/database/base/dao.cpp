#include "dao.h"

// Qt
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>

USE_DB_NAMESPACE


Dao::Dao(Table *table):
    m_table(table)
{

}

Dao::~Dao()
{

}

QVariant Dao::get(const DbConstants::milk_id id) const
{
    QSqlQuery query(m_table->database());
    query.prepare(QString("SELECT * FROM %1 WHERE %2 = ?")
                  .arg(m_table->tableName())
                  .arg(m_table->primaryField()));
    query.addBindValue(id);
    if (query.exec() && query.first()) {
        return QVariant::fromValue(query.record());
    } else
        _error(query.lastError().text());

    return {};
}

QVariant Dao::getAll(const QString &where) const
{
    QSqlQuery query(m_table->database());
    if (query.exec(QString("SELECT * FROM %1%2")
                   .arg(m_table->tableName())
                   .arg(where.isEmpty() ? "" : " WHERE " + where)))
    {
        QList<QSqlRecord> data;
        while (query.next()) {
            data.append(query.record());
        }
        return QVariant::fromValue(data);
    } else
        _error(query.lastError().text());

    return {};
}

bool Dao::remove(const QString &where) const
{
    QSqlQuery query(m_table->database());
    if (!query.exec(QString("DELETE FROM %1")
                    .arg(m_table->tableName())
                    .arg(where.isEmpty() ? "" : " WHERE " + where)))
    {
        _error(query.lastError().text());
        return false;
    }

    return true;
}

bool Dao::remove(const DbConstants::milk_id id) const
{
    return remove(QString("%1 = %2")
                  .arg(m_table->primaryField())
                  .arg(id));
}

bool Dao::updateValue(const QString &columnName, const DbConstants::milk_id id, const QVariant &value) const
{
    QSqlQuery query(m_table->database());
    query.prepare(QString("UPDATE %1 SET %2 = ? WHERE %3 = ?")
                  .arg(m_table->tableName())
                  .arg(columnName)
                  .arg(m_table->primaryField()));
    query.addBindValue(value);
    query.addBindValue(id);

    if (!query.exec()) {
        _error(query.lastError().text());
        return false;
    }

    return true;
}

void Dao::_error(const QString &error_description) const
{
    qDebug() << error_description;
    emit m_table->error(error_description);
}
