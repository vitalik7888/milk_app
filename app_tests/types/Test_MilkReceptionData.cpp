#include "Test_MilkReceptionData.h"

#include <TypesConstants.h>
#include <MilkReceptionData.h>
// Qt
#include <QSignalSpy>
#include <QTest>

using TC = TypesConstants;
using TCMR = TC::MilkReception;


Test_MilkReceptionData::Test_MilkReceptionData(QObject *parent) : QObject(parent)
{

}

void Test_MilkReceptionData::compare(const MilkReceptionData &mrd, const int id, const int delivererId, const int milkPointId,
                                 const QDate &deliveryDate, const double priceLiter, const double liters, const double fat)
{
    QCOMPARE(mrd.id(), id);
    QCOMPARE(mrd.delivererId(), delivererId);
    QCOMPARE(mrd.milkPointId(), milkPointId);
    QCOMPARE(mrd.deliveryDate(), deliveryDate);
    QCOMPARE(mrd.priceLiter(), priceLiter);
    QCOMPARE(mrd.liters(), liters);
    QCOMPARE(mrd.fat(), fat);
}

void Test_MilkReceptionData::compareDefault(const MilkReceptionData &mrd)
{
    compare(mrd, TCMR::DEF_ID, TCMR::DEF_ID_DELIVERER, TCMR::DEF_MILK_POINT_ID, TCMR::DEF_DELIVERY_DATE,
            TCMR::M_DEF_PRICE_LITER, TCMR::DEF_LITERS, TCMR::DEF_FAT);
}

void Test_MilkReceptionData::compare(const MilkReceptionData &left, const MilkReceptionData &right)
{
    compare(left, right.id(), right.delivererId(), right.milkPointId(),
            right.deliveryDate(), right.priceLiter(), right.liters(), right.fat());
}

void Test_MilkReceptionData::emptyConstructor()
{
    MilkReceptionData mrd;
    compareDefault(mrd);
}

void Test_MilkReceptionData::constructor()
{
    MilkReceptionData mrd(22, 2, 1, QDate(), 5.6, 112, 3.7);
    compare(mrd, 22, 2, 1, QDate(), 5.6, 112, 3.7);
}

void Test_MilkReceptionData::copyConstructor()
{
    MilkReceptionData mrdToCopy(22, 2, 1, QDate(), 5.6, 112, 3.7);
    MilkReceptionData mrd(mrdToCopy);
    compare(mrd, mrdToCopy);
}

void Test_MilkReceptionData::methods()
{
    MilkReceptionData mrd;
    mrd.setId(22);
    mrd.setDelivererId(2);
    mrd.setMilkPointId(1);
    mrd.setDeliveryDate(QDate());
    mrd.setPriceLiter(5.6);
    mrd.setLiters(112);
    mrd.setFat(3.7);
    compare(mrd, 22, 2, 1, QDate(), 5.6, 112, 3.7);
}

void Test_MilkReceptionData::storingInQVariant()
{
    MilkReceptionData mrdToCopy(22, 2, 1, QDate(), 5.6, 112, 3.7);
    compare(QVariant::fromValue(mrdToCopy).value<MilkReceptionData>(), mrdToCopy);
}
