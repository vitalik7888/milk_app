#include "types/Test_Deliverer.h"

#include <TypesConstants.h>
#include <Deliverer.h>
#include "Locality.h"
// Qt
#include <QTest>

using TC = TypesConstants;
using TCD = TC::Deliverers;


Test_Deliverer::Test_Deliverer(QObject *parent) : QObject(parent)
{
}

void Test_Deliverer::compare(const Deliverer *deliverer, const int id, const QString &firstName,
                             const QString &lastName, const Locality *locality,
                             const QString &inn, const QString &address, const QString &phoneNumber)
{
    QCOMPARE(deliverer->milkId(), id);
    QCOMPARE(deliverer->firstName(), firstName);
    QCOMPARE(deliverer->lastName(), lastName);
    if (locality) {
        QCOMPARE(deliverer->locality()->milkId(), locality->milkId());
        QCOMPARE(deliverer->locality()->name(), locality->name());
        QCOMPARE(deliverer->locality()->description(), locality->description());
    }
    QCOMPARE(deliverer->inn(), inn);
    QCOMPARE(deliverer->address(), address);
    QCOMPARE(deliverer->phoneNumber(), phoneNumber);
}

void Test_Deliverer::compareDefault(const Deliverer *deliverer)
{
    compare(deliverer, TC::DEFAULT_ID, TCD::DEF_FIRST_NAME, TCD::DEF_LAST_NAME, Q_NULLPTR, TCD::DEF_INN,
            TCD::DEF_ADDRESS, TCD::DEF_PHONE_NUMBER);
}

void Test_Deliverer::compare(const Deliverer *left, const Deliverer *right)
{
    compare(left, right->milkId(), right->firstName(), right->lastName(),
            right->locality(), right->inn(), right->address(), right->phoneNumber());
}

void Test_Deliverer::emptyConstructor()
{
    Deliverer dd;
    compareDefault(&dd);
}

void Test_Deliverer::copyConstructor()
{
    Locality locality(1, "n", "d");
    Deliverer delivererToCopy(1, "fname", "lname", "164", "address", "123", &locality);
    Deliverer deliverer(delivererToCopy);
    compare(&deliverer, &delivererToCopy);
}

void Test_Deliverer::constructor()
{
    Locality locality(1, "n", "d");
    Deliverer dd{1, "fname", "lname", "164", "address", "123", &locality};
    compare(&dd, 1, "fname", "lname", &locality, "164", "address", "123");
}

void Test_Deliverer::methods()
{
    Locality locality{1, "n", "d"};
    Deliverer dd;
    dd.setMilkId(1);
    dd.setFirstName("fname");
    dd.setLastName("lname");
    dd.setLocality(&locality);
    dd.setInn("164");
    dd.setAddress("address");
    dd.setPhoneNumber("345");
    compare(&dd, 1, "fname", "lname", &locality, "164", "address", "345");
}

void Test_Deliverer::storingInQVariant()
{
    QScopedPointer<Locality> locality(new Locality(1, "n", "d"));
    Deliverer delivererToCopy{1, "fname", "lname", "164", "address", "123", locality.data()};

    QVariant variant;
    variant.setValue(delivererToCopy);
    auto deliverer = variant.value<Deliverer>();

    compare(&deliverer, &delivererToCopy);
}

void Test_Deliverer::reset()
{
    QScopedPointer<Locality> locality(new Locality());
    Deliverer dd;
    dd.setMilkId(1);
    dd.setFirstName("fname");
    dd.setLastName("lname");
    dd.setLocality(locality.data());
    dd.setInn("164");
    dd.setAddress("address");
    dd.setPhoneNumber("123");
    dd.reset();
    compareDefault(&dd);
}
