#include "types/Test_Locality.h"

#include <TypesConstants.h>
#include "Locality.h"
// Qt
#include <QTest>

using TC = TypesConstants;
using TCL = TC::Localities;


Test_Locality::Test_Locality(QObject *parent) : QObject(parent)
{

}

void Test_Locality::compare(const Locality *locality, const int id, const QString &name,
                            const QString &description)
{
    QCOMPARE(locality->milkId(), id);
    QCOMPARE(locality->name(), name);
    QCOMPARE(locality->description(), description);
}

void Test_Locality::compareDefault(const Locality *locality)
{
    compare(locality, TC::DEFAULT_ID, TCL::DEF_NAME, TCL::DEF_DESCRIPTION);
}

void Test_Locality::compare(const Locality *left, const Locality *right)
{
    compare(left, right->milkId(), right->name(), right->description());
}

void Test_Locality::emptyConstructor()
{
    Locality l;
    compareDefault(&l);
}

void Test_Locality::copyConstructor()
{
    Locality localityToCopy(42, "N", "Descr-");
    Locality l(localityToCopy);
    compare(&l, &localityToCopy);
}

void Test_Locality::constructor()
{
    Locality l{42, "N", "Descr-"};
    compare(&l, 42, "N", "Descr-");
}

void Test_Locality::methods()
{
    Locality l;
    l.setMilkId(123);
    l.setName("dd");
    l.setDescription("fff");
    compare(&l, 123, "dd", "fff");
}

void Test_Locality::reset()
{
    Locality l;
    l.setMilkId(126643);
    l.setName("dhtd");
    l.setDescription("ffaf");
    l.reset();
    compareDefault(&l);
}

void Test_Locality::storingInQVariant()
{
    Locality localityToCopy{42, "N", "Descr-"};
    auto locality = QVariant::fromValue(localityToCopy).value<Locality>();
    compare(&locality, &localityToCopy);
}
