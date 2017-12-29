#include "db/Test_LocalitiesTable.h"

#include <types/Test_Locality.h>
#include <DbConstants.h>
#include <LocalitiesModel.h>
#include <LocalitiesDao.h>
#include <Locality.h>
// Qt
#include <QTest>
#include <QSqlQuery>
#include <QSqlError>

using DC = DbConstants;


Test_LocalitiesModel::Test_LocalitiesModel(QObject *parent) : DbTests(parent)
{

}

void Test_LocalitiesModel::initTestCase()
{
    initDb();

    m_model = new DB_NAMESPACE::LocalitiesModel(this);
}

void Test_LocalitiesModel::cleanupTestCase()
{
    m_db.close();
}

void Test_LocalitiesModel::setGetDao()
{
    auto dao = new DB_NAMESPACE::LocalitiesDao(this);
    m_model->setDao(dao);
    QCOMPARE(m_model->dao(), dao);
}

void Test_LocalitiesModel::append_data()
{
    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("description");
    QTest::addColumn<int>("rowCount");

    QTest::newRow("case1") << "Name1" << "Description1" << 1;
    QTest::newRow("case2") << "Name2" << "Description2" << 2;
}

void Test_LocalitiesModel::append()
{
    QFETCH(QString, name);
    QFETCH(QString, description);
    QFETCH(int, rowCount);

    auto locality = std::make_unique<Locality>(-1, name, description);
    QCOMPARE(m_model->append(locality.get()), true);
    QCOMPARE(m_model->rowCount(), rowCount);
    auto result = dynamic_cast<const Locality *>(m_model->getItemById(locality->milkId()));
    QCOMPARE(result == Q_NULLPTR, false);
    Test_Locality::compare(result, locality->milkId(), name, description);
}

void Test_LocalitiesModel::getPositionById()
{
    QCOMPARE(m_model->getPositionById(1), 0);
    QCOMPARE(m_model->getPositionById(2), 1);
}

void Test_LocalitiesModel::getItemByIndex()
{
    QCOMPARE(m_model->getItemByIndex(0)->milkId(), 1);
    QCOMPARE(m_model->getItemByIndex(1)->milkId(), 2);
}

void Test_LocalitiesModel::getItemById()
{
    QCOMPARE(m_model->getItemById(1)->milkId(), 1);
    QCOMPARE(m_model->getItemById(2)->milkId(), 2);
}

void Test_LocalitiesModel::getItemsByIds()
{
    const auto items = m_model->getItemsByIds({1, 2});
    QCOMPARE(items.count(), 2);
    QCOMPARE(items.at(0)->milkId(), 1);
    QCOMPARE(items.at(1)->milkId(), 2);
}

void Test_LocalitiesModel::update()
{
    Locality locality(1, "newName", "newDescr");
    QCOMPARE(m_model->update(&locality), true);
    Test_Locality::compare(&locality, static_cast<const Locality *>(m_model->getItemById(1)));
}

void Test_LocalitiesModel::removeById()
{
    const auto rowsCount = m_model->rowCount();
    QCOMPARE(m_model->removeById(2), true);
    QCOMPARE(m_model->rowCount(), rowsCount - 1);
}

void Test_LocalitiesModel::refresh()
{
    const auto rowsCount = m_model->rowCount();
    Locality locality(-1, "nnn", "ddd");
    m_model->dao()->insert(&locality);
    m_model->refresh();
    QCOMPARE(m_model->rowCount(), rowsCount + 1);
}

void Test_LocalitiesModel::clear()
{
    m_model->clear();
    QCOMPARE(m_model->rowCount(), 0);
}
