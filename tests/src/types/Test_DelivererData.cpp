#include "types/Test_DelivererData.h"

#include <TypesConstants.h>
#include <DelivererData.h>
// Qt
#include <QSignalSpy>
#include <QTest>

using TC = TypesConstants;
using TCD = TC::Deliverers;


Test_DelivererData::Test_DelivererData(QObject *parent) : QObject(parent)
{

}

void Test_DelivererData::compare(const DelivererData *deliverer, const int id,
                                 const QString &firstName, const QString &lastName, const int localityId,
                             const QString &inn, const QString &address, const QString &phoneNumber)
{
    QCOMPARE(deliverer->milkId(), id);
    QCOMPARE(deliverer->firstName(), firstName);
    QCOMPARE(deliverer->lastName(), lastName);
    QCOMPARE(deliverer->localityId(), localityId);
    QCOMPARE(deliverer->inn(), inn);
    QCOMPARE(deliverer->address(), address);
    QCOMPARE(deliverer->phoneNumber(), phoneNumber);
}

void Test_DelivererData::compareDefault(const DelivererData *deliverer)
{
    compare(deliverer, TC::DEFAULT_ID, TCD::DEF_FIRST_NAME, TCD::DEF_LAST_NAME, TC::DEFAULT_ID,
            TCD::DEF_INN, TCD::DEF_ADDRESS, TCD::DEF_PHONE_NUMBER);
}

void Test_DelivererData::compare(const DelivererData *left, const DelivererData *right)
{
    compare(left, right->milkId(), right->firstName(), right->lastName(), right->localityId(),
            right->inn(), right->address(), right->phoneNumber());
}

void Test_DelivererData::emptyConstructor()
{
    DelivererData dd;
    compareDefault(&dd);
}

void Test_DelivererData::constructor()
{
    DelivererData dd{1, "fname", "lname", 23, "164", "address", "234"};
    compare(&dd, 1, "fname", "lname", 23, "164", "address", "234");
}

void Test_DelivererData::copyConstructor()
{
    DelivererData ddToCopy{1, "fname", "lname", 23, "164", "address", "234"};
    DelivererData dd(ddToCopy);
    compare(&dd, &ddToCopy);
}

void Test_DelivererData::methods()
{
    DelivererData dd;
    dd.setMilkId(1);
    dd.setFirstName("fname");
    dd.setLastName("lname");
    dd.setLocalityId(23);
    dd.setInn("164");
    dd.setAddress("address");
    dd.setPhoneNumber("345");
    compare(&dd, 1, "fname", "lname", 23, "164", "address", "345");
}

void Test_DelivererData::storingInQVariant()
{
    DelivererData ddToCopy(1, "fname", "lname", 23, "164", "address", "234");

    QVariant variant;
    variant.setValue(ddToCopy);
    auto deliverer = variant.value<DelivererData>();
    compare(&deliverer, &ddToCopy);
}
