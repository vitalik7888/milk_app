#include "dao.h"

// Qt
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>

USE_DB_NAMESPACE


Dao::Dao(const QString &tableName, const QString &primeryFieldName, const QSqlDatabase db):
    m_tableName(tableName),
    m_primeryFieldName(primeryFieldName),
    m_db(db)
{

}

Dao::~Dao()
{

}

void Dao::updateValue(const QString &columnName, const milk_id id, const QVariant &value) const
{
    QSqlQuery query(m_db);
    query.prepare(QString("UPDATE %1 SET %2 = ? WHERE %3 = ?")
                  .arg(m_tableName)
                  .arg(columnName)
                  .arg(m_primeryFieldName));
    query.addBindValue(value);
    query.addBindValue(id);

    if (!query.exec()) {
        const auto errDescr = query.lastError().text();
        qDebug() << errDescr;
        throw errDescr;
    }
}
