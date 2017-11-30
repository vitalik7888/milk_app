#include "Test_DelivererData.h"

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

void Test_DelivererData::compare(DelivererData *deliverer, const int id, const QString &name, const int localityId,
                             const QString &inn, const QString &address, const QString &phoneNumber)
{
    QCOMPARE(deliverer->id(), id);
    QCOMPARE(deliverer->name(), name);
    QCOMPARE(deliverer->localityId(), localityId);
    QCOMPARE(deliverer->inn(), inn);
    QCOMPARE(deliverer->address(), address);
    QCOMPARE(deliverer->phoneNumber(), phoneNumber);
}

void Test_DelivererData::compareDefault(DelivererData *deliverer)
{
    compare(deliverer, TCD::DEF_ID, TCD::DEF_NAME, TCD::DEF_LOCALITY_ID, TCD::DEF_INN,
            TCD::DEF_ADDRESS, TCD::DEF_PHONE_NUMBER);
}

void Test_DelivererData::compare(DelivererData *left, DelivererData *right)
{
    compare(left, right->id(), right->name(), right->localityId(), right->inn(),
            right->address(), right->phoneNumber());
}

void Test_DelivererData::emptyConstructor()
{
    DelivererData dd;
    compareDefault(&dd);
}

void Test_DelivererData::constructor()
{
    DelivererData dd{1, "name", 23, "164", "address", "234"};
    compare(&dd, 1, "name", 23, "164", "address", "234");
}

void Test_DelivererData::copyConstructor()
{
    DelivererData ddToCopy{1, "name", 23, "164", "address", "234"};
    DelivererData dd(ddToCopy);
    compare(&dd, &ddToCopy);
}

void Test_DelivererData::methods()
{
    DelivererData dd;
    dd.setId(1);
    dd.setName("name");
    dd.setLocalityId(23);
    dd.setInn("164");
    dd.setAddress("address");
    dd.setPhoneNumber("345");
    compare(&dd, 1, "name", 23, "164", "address", "345");
}

void Test_DelivererData::storingInQVariant()
{
    DelivererData ddToCopy(1, "name", 23, "164", "address", "234");

    QVariant variant;
    variant.setValue(ddToCopy);
    auto deliverer = variant.value<DelivererData>();
    compare(&deliverer, &ddToCopy);
}
