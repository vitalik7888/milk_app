#include "Test_Deliverer.h"

#include <deliverer.h>
#include "locality.h"
// Qt
#include <QSignalSpy>
#include <QTest>

using TC = TypesConstants;
using TCD = TC::Deliverers;


Test_Deliverer::Test_Deliverer(QObject *parent) : QObject(parent)
{
}

void Test_Deliverer::compare(Deliverer *deliverer, const TypesConstants::milk_id id,
                             const QString &name, Locality *locality, const TypesConstants::milk_inn inn,
                             const QString &address, const QString &phoneNumber)
{
    QCOMPARE(deliverer->id(), id);
    QCOMPARE(deliverer->name(), name);
    QCOMPARE(deliverer->locality(), locality);
    if (locality) {
        QCOMPARE(deliverer->locality()->id(), locality->id());
        QCOMPARE(deliverer->locality()->name(), locality->name());
        QCOMPARE(deliverer->locality()->description(), locality->description());
    }
    QCOMPARE(deliverer->inn(), inn);
    QCOMPARE(deliverer->address(), address);
    QCOMPARE(deliverer->phoneNumber(), phoneNumber);
}

void Test_Deliverer::compareDefault(Deliverer *deliverer)
{
    compare(deliverer, TCD::DEF_ID, TCD::DEF_NAME, Q_NULLPTR, TCD::DEF_INN,
            TCD::DEF_ADDRESS, TCD::DEF_PHONE_NUMBER);
}

void Test_Deliverer::compare(Deliverer *left, Deliverer *right)
{
    compare(left, right->id(), right->name(), right->locality(), right->inn(), right->address(), right->phoneNumber());
}

void Test_Deliverer::emptyConstructor()
{
    Deliverer dd;
    compareDefault(&dd);
}

void Test_Deliverer::copyConstructor()
{
    auto locality = new Locality({1, "n", "d"}, this);
    Deliverer delivererToCopy{1, "name", 164, "address", "123", locality};
    Deliverer deliverer(delivererToCopy);
    compare(&deliverer, &delivererToCopy);
}

void Test_Deliverer::constructor()
{
    auto locality = new Locality({1, "n", "d"}, this);
    Deliverer dd{1, "name", 164, "address", "123", locality};
    compare(&dd, 1, "name", locality, 164, "address", "123");
}

void Test_Deliverer::methods()
{
    auto locality = new Locality({1, "n", "d"}, this);
    Deliverer dd;
    dd.setId(1);
    dd.setName("name");
    dd.setLocality(locality);
    dd.setInn(164);
    dd.setAddress("address");
    dd.setPhoneNumber("345");
    compare(&dd, 1, "name", locality, 164, "address", "345");
}

void Test_Deliverer::storingInQVariant()
{
    Deliverer delivererToCopy{1, "name", 164, "address", "123", new Locality({1, "n", "d"}, this)};

    QVariant variant;
    variant.setValue(delivererToCopy);
    auto deliverer = variant.value<Deliverer>();

    compare(&deliverer, &delivererToCopy);
}

void Test_Deliverer::reset()
{
    Deliverer dd;
    dd.setId(1);
    dd.setName("name");
    dd.setLocality(new Locality(this));
    dd.setInn(164);
    dd.setAddress("address");
    dd.setPhoneNumber("123");
    dd.reset();
    compareDefault(&dd);
}

void Test_Deliverer::signalIdChanged()
{
    Deliverer deliverer;
    const TC::milk_id data = 15;
    QSignalSpy signalSpy(&deliverer, &Deliverer::idChanged);
    deliverer.setId(data);
    deliverer.setId(data);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toLongLong(), data);
}

void Test_Deliverer::signalLocalityChanged()
{
    Deliverer deliverer;
    Locality data({16, "_n", "d_"});
    QSignalSpy signalSpy(&deliverer, &Deliverer::localityChanged);
    deliverer.setLocality(&data);
    deliverer.setLocality(&data);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    Locality *locality = qvariant_cast<Locality *>(arguments.at(0));
    QCOMPARE((bool)locality, true);
    QCOMPARE(locality->id(), data.id());
    QCOMPARE(locality->name(), data.name());
    QCOMPARE(locality->description(), data.description());

}

void Test_Deliverer::signalNameChanged()
{
    Deliverer deliverer;
    const QString data = "15";
    QSignalSpy signalSpy(&deliverer, &Deliverer::nameChanged);
    deliverer.setName(data);
    deliverer.setName(data);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toString(), data);
}

void Test_Deliverer::signalInnChanged()
{
    Deliverer deliverer;
    const TC::milk_id data = 15;
    QSignalSpy signalSpy(&deliverer, &Deliverer::innChanged);
    deliverer.setInn(data);
    deliverer.setInn(data);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toLongLong(), data);
}

void Test_Deliverer::signalAddressChanged()
{
    Deliverer deliverer;
    const QString data = "a";
    QSignalSpy signalSpy(&deliverer, &Deliverer::addressChanged);
    deliverer.setAddress(data);
    deliverer.setAddress(data);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toString(), data);
}

void Test_Deliverer::signalPhoneNumberChanged()
{
    Deliverer deliverer;
    const QString data = "13336";
    QSignalSpy signalSpy(&deliverer, &Deliverer::phoneNumberChanged);
    deliverer.setPhoneNumber(data);
    deliverer.setPhoneNumber(data);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toString(), data);
}
