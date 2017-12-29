#include "include/db/DbTests.h"

#include <DbConstants.h>
// Qt
#include <QTest>
#include <QSqlQuery>
#include <QSqlError>

using DC = DbConstants;


DbTests::DbTests(QObject *parent) : QObject(parent)
{

}

void DbTests::initDb()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("t.db");
    QVERIFY2(m_db.open(), m_db.lastError().text().toStdString().data());
}

void DbTests::execVerifyQuery(const QString &_query) const
{
    QSqlQuery query(_query, m_db);
    QVERIFY2(query.exec(), query.lastError().text().toStdString().data());
}
