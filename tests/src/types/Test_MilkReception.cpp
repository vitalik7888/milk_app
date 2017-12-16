#include "types/Test_MilkReception.h"

#include "types/Test_Deliverer.h"
#include "types/Test_MilkPoint.h"
#include <TypesConstants.h>
#include <MilkReception.h>
#include <Locality.h>
#include <MilkPoint.h>
#include <Deliverer.h>
// Qt
#include <QSignalSpy>
#include <QTest>

using TC = TypesConstants;
using TCMR = TC::MilkReception;


Test_MilkReception::Test_MilkReception(QObject *parent) : QObject(parent)
{

}

void Test_MilkReception::compare(MilkReception *mr, const int id, const QDate deliveryDate,
                                 const double priceLiter, const double liters, const double fat,
                                 Deliverer *deliverer, MilkPoint *milkPoint)
{
    QCOMPARE(mr->id(), id);
    QCOMPARE(mr->deliverer(), deliverer);
    if (deliverer) {
        Test_Deliverer::compare(mr->deliverer(), deliverer->id(), deliverer->firstName(), deliverer->lastName(),
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
    compare(mr, TCMR::DEF_ID, TCMR::DEF_DELIVERY_DATE, TCMR::M_DEF_PRICE_LITER, TCMR::DEF_LITERS,
            TCMR::DEF_FAT, Q_NULLPTR, Q_NULLPTR);
}

void Test_MilkReception::compare(MilkReception *left, MilkReception *right)
{
    compare(left, right->id(), right->deliveryDate(), right->priceLiter(), right->liters(),
            right->fat(), right->deliverer(), right->milkPoint());
}

void Test_MilkReception::emptyConstructor()
{
    MilkReception mr;
    compareDefault(&mr);
}

void Test_MilkReception::constructor()
{
    Deliverer d(1, "fname", "lname", "23", "address", "234");
    MilkPoint mp(42, "n", "d");

    MilkReception mr(22, QDate(), 5.6, 112, 3.7, &d, &mp);

    compare(&mr, 22, QDate(), 5.6, 112, 3.7, &d, &mp);
}

void Test_MilkReception::copyConstructor()
{
    MilkReception mrToCopy(22, QDate(), 5.6, 112, 3.7,
                     new Deliverer(1, "fname", "lname", "23", "address", "234"),
                     new MilkPoint(42, "n", "d"));
    MilkReception mr(mrToCopy);
    compare(&mr, &mrToCopy);
}

void Test_MilkReception::methods()
{
    Deliverer d(1, "fname", "lname", "23", "address", "234");
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

void Test_MilkReception::reset()
{
    Deliverer d(1, "fname", "lname", "23", "address", "234");
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

void Test_MilkReception::storingInQVariant()
{
    Deliverer d(1, "fname", "lname", "23", "address", "234");
    MilkPoint mp(42, "n", "d");
    MilkReception mr(22, QDate(), 5.6, 112, 3.7, &d, &mp);
    auto milkReception = QVariant::fromValue(mr).value<MilkReception>();
    compare(&milkReception, &mr);
}

void Test_MilkReception::signalIdChanged()
{
    MilkReception mr;
    const int data = 15;
    QSignalSpy signalSpy(&mr, &MilkReception::idChanged);
    mr.setId(data);
    mr.setId(data);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toLongLong(), data);
}

void Test_MilkReception::signalDeliveryDateChanged()
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

void Test_MilkReception::signalPriceLiterChanged()
{
    MilkReception mr;
    const double data = TCMR::M_DEF_PRICE_LITER + 2.7;
    QSignalSpy signalSpy(&mr, &MilkReception::priceLiterChanged);
    mr.setPriceLiter(data);
    mr.setPriceLiter(data);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toDouble(), data);
}

void Test_MilkReception::signalLitersChanged()
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

void Test_MilkReception::signalFatChanged()
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

void Test_MilkReception::signalDelivererChanged()
{
    Deliverer data(1, "fname", "lname", "23", "address", "234");

    MilkReception mr;
    QSignalSpy signalSpy(&mr, &MilkReception::delivererChanged);
    mr.setDeliverer(&data);
    mr.setDeliverer(&data);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    auto deliverer = qvariant_cast<Deliverer *>(arguments.first());
    QCOMPARE(deliverer, &data);
}

void Test_MilkReception::signalMilkPointChanged()
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
