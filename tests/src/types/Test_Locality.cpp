#include "types/Test_Locality.h"

#include <TypesConstants.h>
#include "LocalityData.h"
// Qt
#include <QSignalSpy>
#include <QTest>

using TC = TypesConstants;
using TCL = TC::Localities;


Test_Locality::Test_Locality(QObject *parent) : QObject(parent)
{

}

void Test_Locality::compare(Locality *locality, const int id, const QString &name,
                            const QString &description)
{
    QCOMPARE(locality->id(), id);
    QCOMPARE(locality->name(), name);
    QCOMPARE(locality->description(), description);
}

void Test_Locality::compareDefault(Locality *locality)
{
    compare(locality, TCL::DEF_ID, TCL::DEF_NAME, TCL::DEF_DESCRIPTION);
}

void Test_Locality::compare(Locality *left, Locality *right)
{
    compare(left, right->id(), right->name(), right->description());
}

void Test_Locality::emptyConstructor()
{
    Locality l;
    compareDefault(&l);
}

void Test_Locality::copyConstructor()
{
    Locality localityToCopy({42, "N", "Descr-"});
    Locality l(localityToCopy);
    compare(&l, &localityToCopy);
}

void Test_Locality::constructor()
{
    Locality l({42, "N", "Descr-"});
    compare(&l, 42, "N", "Descr-");
}

void Test_Locality::methods()
{
    Locality l;
    l.setId(123);
    l.setName("dd");
    l.setDescription("fff");
    compare(&l, 123, "dd", "fff");
}

void Test_Locality::reset()
{
    Locality l;
    l.setId(126643);
    l.setName("dhtd");
    l.setDescription("ffaf");
    l.reset();
    compareDefault(&l);
}

void Test_Locality::storingInQVariant()
{
    Locality localityToCopy({42, "N", "Descr-"});
    auto locality = QVariant::fromValue(localityToCopy).value<Locality>();
    compare(&locality, &localityToCopy);
}

void Test_Locality::signalIdChanged()
{
    Locality l;
    const int data = 15;
    QSignalSpy signalSpy(&l, &Locality::idChanged);
    l.setId(data);
    l.setId(data);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toLongLong(), data);
}

void Test_Locality::signalNameChanged()
{
    Locality l;
    const QString data = "vdv";
    QSignalSpy signalSpy(&l, &Locality::nameChanged);
    l.setName(data);
    l.setName(data);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toString(), data);
}

void Test_Locality::signalDescriptionChanged()
{
    Locality l;
    const QString data = "aaa";
    QSignalSpy signalSpy(&l, &Locality::descriptionChanged);
    l.setDescription(data);
    l.setDescription(data);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toString(), data);
}
