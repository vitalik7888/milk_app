#include "db/Test_LocalitiesDao.h"

#include "types/Test_Locality.h"
#include <LocalitiesDao.h>
#include <memory>
// Qt
#include <QTest>
#include <QSqlQuery>
#include <QSqlError>

USE_DB_NAMESPACE
using DC = DbConstants;


Test_LocalitiesDao::Test_LocalitiesDao(QObject *parent):
    DbTests(parent)
{

}

void Test_LocalitiesDao::initTestCase()
{
    initDb();

    execVerifyQuery(DC::dropTableIfExistsSql(DC::TL_TABLE_NAME));

    m_dao = new LocalitiesDao(this);
    m_locality = std::make_unique<Locality>(-1, "name", "description");
}

void Test_LocalitiesDao::cleanupTestCase()
{
    m_db.close();
}

void Test_LocalitiesDao::tableName()
{
    QCOMPARE(m_dao->tableName(), DC::TL_TABLE_NAME);
}

void Test_LocalitiesDao::fieldsNames()
{
    QCOMPARE(m_dao->fieldsNames(), QStringList() << DC::TL_FN_ID << DC::TL_FN_NAME << DC::TL_FN_DESCRIPTION);
}

void Test_LocalitiesDao::primaryFieldName()
{
    QCOMPARE(m_dao->primaryFieldName(), DC::TL_FN_ID);
}

void Test_LocalitiesDao::getCreateTableStr()
{
    QCOMPARE(m_dao->getCreateTableStr(), DC::TL_CREATE_TABLE_SQL);
}

void Test_LocalitiesDao::getSetDb()
{
    m_dao->setDb(m_db);
    //    QVERIFY(m_dao->getDb() == m_db);
}

void Test_LocalitiesDao::createTable()
{
    QVERIFY(m_dao->createTable());
}

void Test_LocalitiesDao::insert()
{
    QCOMPARE(m_dao->insert(m_locality.get()), true);
    QCOMPARE(m_locality->milkId() > 0, true);
    Test_Locality::compare(m_locality.get(), m_locality->milkId(), "name", "description");
}

void Test_LocalitiesDao::getIds()
{
    const auto ids = m_dao->getIds();
    QCOMPARE(ids, {m_locality->milkId()});
}

void Test_LocalitiesDao::getItem()
{
    const auto items = m_dao->get(QString("%1 = %2").arg(m_dao->primaryFieldName())
                                  .arg(m_locality->milkId()));
    const auto item = dynamic_cast<const Locality *>(items.get()->at(0).get());
    Test_Locality::compare(m_locality.get(), item);
}

void Test_LocalitiesDao::update()
{
    m_locality->setName("newName");
    m_locality->setDescription("newDescr");
    QCOMPARE(m_dao->update(m_locality.get()), true);
    Test_Locality::compare(m_locality.get(), m_locality->milkId(), "newName", "newDescr");
}

void Test_LocalitiesDao::updateValues()
{
    QCOMPARE(m_dao->updateValue(DC::TL_NAME, m_locality->milkId(), "name"), true);
    QCOMPARE(m_dao->updateValue(DC::TL_DESCRIPTION, m_locality->milkId(), "descr"), true);
    m_locality.reset(dynamic_cast<Locality *>(m_dao->get(QString("%1 = %2")
                                                         .arg(m_dao->primaryFieldName())
                                                         .arg(m_locality->milkId()))
                                              .get()->at(0).release()));
    Test_Locality::compare(m_locality.get(), m_locality->milkId(), "name", "descr");
}

void Test_LocalitiesDao::remove()
{
    QCOMPARE(m_dao->remove(QString("%1 = %2").arg(m_dao->primaryFieldName()).arg(m_locality->milkId())),
             true);
    QCOMPARE(m_dao->get(QString("%1 = %2").arg(m_dao->primaryFieldName())
                        .arg(m_locality->milkId())).get()->size(), 0);
    //    m_locality.release();
}
