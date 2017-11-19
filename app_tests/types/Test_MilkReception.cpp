#include "Test_MilkReception.h"

#include <milkreception.h>
#include <locality.h>
#include <milkpoint.h>
#include "Test_Deliverer.h"
#include "Test_MilkPoint.h"
// Qt
#include <QSignalSpy>
#include <QTest>
#include <deliverer.h>

using TC = TypesConstants;
using TCMR = TC::MilkReception;


Test_MilkReception::Test_MilkReception(QObject *parent) : QObject(parent)
{

}

void Test_MilkReception::compare(MilkReceptionData *mrd, const TC::milk_id id,
                                 const TC::milk_id delivererId, const TC::milk_id milkPointId,
                                 const QDate &deliveryDate, const double priceLiter,
                                 const double liters, const double fat)
{
    QCOMPARE(mrd->id(), id);
    QCOMPARE(mrd->delivererId(), delivererId);
    QCOMPARE(mrd->milkPointId(), milkPointId);
    QCOMPARE(mrd->deliveryDate(), deliveryDate);
    QCOMPARE(mrd->priceLiter(), priceLiter);
    QCOMPARE(mrd->liters(), liters);
    QCOMPARE(mrd->fat(), fat);
}

void Test_MilkReception::compareDefault(MilkReceptionData *mrd)
{
    compare(mrd, TCMR::DEF_ID, TCMR::DEF_ID_DELIVERER, TCMR::DEF_MILK_POINT_ID, TCMR::DEF_DELIVERY_DATE,
            TCMR::DEF_PRICE_LITER, TCMR::DEF_LITERS, TCMR::DEF_FAT);
}

void Test_MilkReception::compare(MilkReception *mr, const TC::milk_id id, const QDate deliveryDate,
                                 const double priceLiter, const double liters, const double fat,
                                 Deliverer *deliverer, MilkPoint *milkPoint)
{
    QCOMPARE(mr->id(), id);
    QCOMPARE(mr->deliverer(), deliverer);
    if (deliverer) {
        Test_Deliverer::compare(mr->deliverer(), deliverer->id(), deliverer->name(),
                                deliverer->locality(), deliverer->inn(), deliverer->address(),
                                deliverer->phoneNumber());
    }
    QCOMPARE(mr->milkPoint(), milkPoint);
    if (milkPoint) {
        Test_MilkPoint::compare(mr->milkPoint(), milkPoint->id(), milkPoint->name(),
                                milkPoint->description(), milkPoint->locality());
    }
    QCOMPARE(mr->deliveryDate(), deliveryDate);
    QCOMPARE(mr->priceLiter(), priceLiter);
    QCOMPARE(mr->liters(), liters);
    QCOMPARE(mr->fat(), fat);
}

void Test_MilkReception::compareDefault(MilkReception *mr)
{
    compare(mr, TCMR::DEF_ID, TCMR::DEF_DELIVERY_DATE, TCMR::DEF_PRICE_LITER, TCMR::DEF_LITERS,
            TCMR::DEF_FAT, Q_NULLPTR, Q_NULLPTR);
}

void Test_MilkReception::testEmptyDataConstructor()
{
    MilkReceptionData mrd;
    compareDefault(&mrd);
}

void Test_MilkReception::testDataConstructor()
{
    MilkReceptionData mrd(22, 2, 1, QDate(), 5.6, 112, 3.7);
    compare(&mrd, 22, 2, 1, QDate(), 5.6, 112, 3.7);
}

void Test_MilkReception::testDataMethods()
{
    MilkReceptionData mrd;
    mrd.setId(22);
    mrd.setDelivererId(2);
    mrd.setMilkPointId(1);
    mrd.setDeliveryDate(QDate());
    mrd.setPriceLiter(5.6);
    mrd.setLiters(112);
    mrd.setFat(3.7);
    compare(&mrd, 22, 2, 1, QDate(), 5.6, 112, 3.7);
}

void Test_MilkReception::testEmptyConstructor()
{
    MilkReception mr;
    compareDefault(&mr);
}

void Test_MilkReception::testConstructor()
{
    Deliverer d(1, "name", 23, "address", "234");
    MilkPoint mp(42, "n", "d");

    MilkReception mr(22, QDate(), 5.6, 112, 3.7, &d, &mp);

    compare(&mr, 22, QDate(), 5.6, 112, 3.7, &d, &mp);
}

void Test_MilkReception::testMethods()
{
    Deliverer d(1, "name", 23, "address", "234");
    MilkPoint mp(42, "n", "d");

    MilkReception mr;
    mr.setId(22);
    mr.setDeliverer(&d);
    mr.setMilkPoint(&mp);
    mr.setDeliveryDate(QDate());
    mr.setPriceLiter(5.6);
    mr.setLiters(112);
    mr.setFat(3.7);

    compare(&mr, 22, QDate(), 5.6, 112, 3.7, &d, &mp);
}

void Test_MilkReception::testReset()
{
    Deliverer d(1, "name", 23, "address", "234");
    MilkPoint mp(42, "n", "d");

    MilkReception mr;
    mr.setId(22);
    mr.setDeliverer(&d);
    mr.setMilkPoint(&mp);
    mr.setDeliveryDate(QDate());
    mr.setPriceLiter(5.6);
    mr.setLiters(112);
    mr.setFat(3.7);
    mr.reset();

    compareDefault(&mr);
}

void Test_MilkReception::testSignalId()
{
    MilkReception mr;
    const TC::milk_id data = 15;
    QSignalSpy signalSpy(&mr, &MilkReception::idChanged);
    mr.setId(data);
    mr.setId(data);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toLongLong(), data);
}

void Test_MilkReception::testSignalDeliveryDate()
{
    MilkReception mr;
    const QDate data(10, 10, 10);
    QSignalSpy signalSpy(&mr, &MilkReception::deliveryDateChanged);
    mr.setDeliveryDate(data);
    mr.setDeliveryDate(data);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toDate(), data);
}

void Test_MilkReception::testSignalPriceLiter()
{
    MilkReception mr;
    const double data = TCMR::DEF_PRICE_LITER + 2.7;
    QSignalSpy signalSpy(&mr, &MilkReception::priceLiterChanged);
    mr.setPriceLiter(data);
    mr.setPriceLiter(data);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toDouble(), data);
}

void Test_MilkReception::testSignalLiters()
{
    MilkReception mr;
    const double data = TCMR::DEF_LITERS + 3.6;
    QSignalSpy signalSpy(&mr, &MilkReception::litersChanged);
    mr.setLiters(data);
    mr.setLiters(data);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toDouble(), data);
}

void Test_MilkReception::testSignalFat()
{
    MilkReception mr;
    const double data = TCMR::DEF_FAT + 1.6;
    QSignalSpy signalSpy(&mr, &MilkReception::fatChanged);
    mr.setFat(data);
    mr.setFat(data);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toDouble(), data);
}

void Test_MilkReception::testSignalDeliverer()
{
    Deliverer data(1, "name", 23, "address", "234");

    MilkReception mr;
    QSignalSpy signalSpy(&mr, &MilkReception::delivererChanged);
    mr.setDeliverer(&data);
    mr.setDeliverer(&data);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    auto deliverer = qvariant_cast<Deliverer *>(arguments.first());
    QCOMPARE(deliverer, &data);
}

void Test_MilkReception::testSignalMilkPoint()
{
    MilkPoint data(42, "n", "d");

    MilkReception mr;
    QSignalSpy signalSpy(&mr, &MilkReception::milkPointChanged);
    mr.setMilkPoint(&data);
    mr.setMilkPoint(&data);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    auto deliverer = qvariant_cast<MilkPoint *>(arguments.first());
    QCOMPARE(deliverer, &data);
}
