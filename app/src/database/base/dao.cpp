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

bool Dao::updateValue(const QString &columnName, const milk_id id, const QVariant &value) const
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
