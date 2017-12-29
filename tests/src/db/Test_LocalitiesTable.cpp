#include "db/Test_LocalitiesTable.h"

#include <DbConstants.h>
// Qt
#include <QTest>
#include <QSqlQuery>
#include <QSqlError>

using DC = DbConstants;


Test_LocalitiesTable::Test_LocalitiesTable(QObject *parent) : DbTests(parent)
{

}

void Test_LocalitiesTable::initTestCase()
{
    initDb();
}

void Test_LocalitiesTable::cleanupTestCase()
{
    m_db.close();
}
