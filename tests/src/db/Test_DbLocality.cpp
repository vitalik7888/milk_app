#include "db/Test_DbLocality.h"

#include <DbLocality.h>
#include <LocalitiesModel.h>
#include <LocalitiesDao.h>
#include <types/Test_Locality.h>
#include <TypesConstants.h>
// Qt
#include <QtTest>
#include <QSignalSpy>

USE_DB_NAMESPACE
using TC = TypesConstants;
using DC = DbConstants;


Test_DbLocality::Test_DbLocality(QObject *parent) : DbTests(parent)
{

}

void Test_DbLocality::initTestCase()
{
    initDb();

    m_model = new LocalitiesModel(this);
    m_model->setDao(new LocalitiesDao(this));
    m_dbItem = new DbLocality(this);

    m_model->append((std::make_unique<Locality>(-1, "name1", "descr1")).get());
}

void Test_DbLocality::cleanupTestCase()
{
    m_db.close();
}

void Test_DbLocality::setGetModel()
{
    QSignalSpy signalSpy(m_dbItem, &DbLocality::modelChanged);
    m_dbItem->setModel(m_model);
    m_dbItem->setModel(m_model);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    auto model = qvariant_cast<LocalitiesModel *>(arguments.first());
    QCOMPARE(m_dbItem->model(), model);
}

void Test_DbLocality::setItem()
{
    const auto item = dynamic_cast<const Locality *>(m_model->getItemByIndex(0));
    m_dbItem->setItem(item);
    Test_Locality::compare(item, m_dbItem->milkId(), m_dbItem->name(), m_dbItem->description());
}

void Test_DbLocality::loadData()
{
    const auto item = dynamic_cast<const Locality *>(m_model->getItemByIndex(0));
    QSignalSpy signalSpy(m_dbItem, &DbLocality::dataLoaded);
    QCOMPARE(m_dbItem->loadData(item->milkId()), true);
    QCOMPARE(signalSpy.count(), 1);
    Test_Locality::compare(item, m_dbItem->milkId(), m_dbItem->name(), m_dbItem->description());
}

void Test_DbLocality::getPositionInModel()
{
    QCOMPARE(m_dbItem->getPositionInModel(), 0);
}

void Test_DbLocality::setMilkId()
{
    const MILK_ID data = 1124;
    QSignalSpy signalSpy(m_dbItem, &DbLocality::milkIdChanged);
    m_dbItem->setMilkId(data);
    m_dbItem->setMilkId(data);
    QCOMPARE(m_dbItem->milkId(), data);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toInt(), data);
}

void Test_DbLocality::setName()
{
    const QString data = "someName";
    QSignalSpy signalSpy(m_dbItem, &DbLocality::nameChanged);
    m_dbItem->setName(data);
    m_dbItem->setName(data);
    QCOMPARE(m_dbItem->name(), data);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toString(), data);
}

void Test_DbLocality::setDescription()
{
    const QString data = "someDescription";
    QSignalSpy signalSpy(m_dbItem, &DbLocality::descriptionChanged);
    m_dbItem->setDescription(data);
    m_dbItem->setDescription(data);
    QCOMPARE(m_dbItem->description(), data);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toString(), data);
}

void Test_DbLocality::reset()
{
    m_dbItem->reset();
    QCOMPARE(m_dbItem->milkId(), TC::DEFAULT_ID);
    QCOMPARE(m_dbItem->name(), TC::Localities::DEF_NAME);
    QCOMPARE(m_dbItem->description(), TC::Localities::DEF_DESCRIPTION);
}

void Test_DbLocality::save()
{
    const auto item = dynamic_cast<const Locality *>(m_model->getItemByIndex(0));
    m_dbItem->setItem(item);
    m_dbItem->setName("nnew");
    m_dbItem->setDescription("ddescr");
    m_dbItem->save();
    QCOMPARE(m_dbItem->milkId(), item->milkId());
    QCOMPARE(m_dbItem->name(), item->name());
    QCOMPARE(m_dbItem->description(), item->description());
}

void Test_DbLocality::saveValues()
{
    const auto item = dynamic_cast<const Locality *>(m_model->getItemByIndex(0));
    m_dbItem->setItem(item);

    m_dbItem->saveValue("_new", static_cast<int>(DC::LocalitiesRoles::NameRole));
    QCOMPARE(m_dbItem->name(), item->name());
    m_dbItem->saveValue("_descr", static_cast<int>(DC::LocalitiesRoles::DescriptionRole));
    QCOMPARE(m_dbItem->description(), item->description());
}

void Test_DbLocality::remove()
{
    m_dbItem->setItem(m_model->getItemByIndex(0));
    const auto milkId = m_dbItem->milkId();
    QCOMPARE(m_dbItem->remove(), true);
    QCOMPARE(m_model->getItemById(milkId) == Q_NULLPTR, true);
}

void Test_DbLocality::append()
{
    m_dbItem->reset();
    m_dbItem->setName("__name");
    m_dbItem->setDescription("_description_");
    QCOMPARE(m_dbItem->append(), true);
    QCOMPARE(m_dbItem->milkId() > 0, true);
}
