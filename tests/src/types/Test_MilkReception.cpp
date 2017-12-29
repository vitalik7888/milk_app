#include "types/Test_MilkReception.h"

#include "types/Test_Deliverer.h"
#include "types/Test_MilkPoint.h"
#include <TypesConstants.h>
#include <MilkReception.h>
#include <Locality.h>
#include <MilkPoint.h>
#include <Deliverer.h>
// Qt
#include <QTest>

using TC = TypesConstants;
using TCMR = TC::MilkReception;


Test_MilkReception::Test_MilkReception(QObject *parent) : QObject(parent)
{

}

void Test_MilkReception::compare(const MilkReception *mr, const int id, const QDate deliveryDate,
                                 const double priceLiter, const double liters, const double fat,
                                 const Deliverer *deliverer, const MilkPoint *milkPoint)
{
    QCOMPARE(mr->milkId(), id);
    if (deliverer) {
        Test_Deliverer::compare(mr->deliverer(), deliverer->milkId(), deliverer->firstName(),
                                deliverer->lastName(), deliverer->locality(), deliverer->inn(),
                                deliverer->address(), deliverer->phoneNumber());
    }
    if (milkPoint) {
        Test_MilkPoint::compare(mr->milkPoint(), milkPoint->milkId(), milkPoint->name(),
                                milkPoint->description(), milkPoint->locality());
    }
    QCOMPARE(mr->deliveryDate(), deliveryDate);
    QCOMPARE(mr->priceLiter(), priceLiter);
    QCOMPARE(mr->liters(), liters);
    QCOMPARE(mr->fat(), fat);
}

void Test_MilkReception::compareDefault(const MilkReception *mr)
{
    compare(mr, TC::DEFAULT_ID, TCMR::DEF_DELIVERY_DATE, TCMR::DEF_PRICE_LITER, TCMR::DEF_LITERS,
            TCMR::DEF_FAT, Q_NULLPTR, Q_NULLPTR);
}

void Test_MilkReception::compare(const MilkReception *left, const MilkReception *right)
{
    compare(left, right->milkId(), right->deliveryDate(), right->priceLiter(), right->liters(),
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
    Deliverer d(1, "fname", "lname", "23", "address", "234");
    MilkPoint mp(42, "n", "d");
    MilkReception mrToCopy(22, QDate(), 5.6, 112, 3.7, &d, &mp);
    MilkReception mr(mrToCopy);
    compare(&mr, &mrToCopy);
}

void Test_MilkReception::methods()
{
    Deliverer d(1, "fname", "lname", "23", "address", "234");
    MilkPoint mp(42, "n", "d");

    MilkReception mr;
    mr.setMilkId(22);
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
    mr.setMilkId(22);
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
