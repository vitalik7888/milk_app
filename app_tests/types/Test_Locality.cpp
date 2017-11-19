#include "Test_Locality.h"

#include "locality.h"
// Qt
#include <QSignalSpy>
#include <QTest>

using TC = TypesConstants;
using TCL = TC::Localities;


Test_Locality::Test_Locality(QObject *parent) : QObject(parent)
{

}

void Test_Locality::compare(LocalityData *locality, const TC::milk_id id,
                            const QString &name, const QString &description)
{
    QCOMPARE(locality->id(), id);
    QCOMPARE(locality->name(), name);
    QCOMPARE(locality->description(), description);
}

void Test_Locality::compareDefault(LocalityData *locality)
{
    compare(locality, TCL::DEF_ID, TCL::DEF_NAME, TCL::DEF_DESCRIPTION);
}

void Test_Locality::compare(Locality *locality, const TC::milk_id id, const QString &name,
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

void Test_Locality::testEmptyDataConstructor()
{
    LocalityData ld;
    compareDefault(&ld);
}

void Test_Locality::testDataConstructor()
{
    LocalityData ld(42, "N", "Descr-");
    compare(&ld, 42, "N", "Descr-");
}

void Test_Locality::testDataCopyConstructor()
{
    LocalityData ldToCopy(42, "N", "Descr-");
    LocalityData ld(ldToCopy);
    compare(&ld, ldToCopy.id(), ldToCopy.name(), ldToCopy.description());
}

void Test_Locality::testDataMethods()
{
    LocalityData ld;
    ld.setId(123);
    ld.setName("dd");
    ld.setDescription("fff");
    compare(&ld, 123, "dd", "fff");
}

void Test_Locality::testEmptyConstructor()
{
    Locality l;
    compareDefault(&l);
}

void Test_Locality::testCopyConstructor()
{
    Locality localityToCopy({42, "N", "Descr-"});
    Locality l(localityToCopy);
    compare(&l, localityToCopy.id(), localityToCopy.name(), localityToCopy.description());
}

void Test_Locality::testConstructor()
{
    Locality l({42, "N", "Descr-"});
    compare(&l, 42, "N", "Descr-");
}

void Test_Locality::testMethods()
{
    Locality l;
    l.setId(123);
    l.setName("dd");
    l.setDescription("fff");
    compare(&l, 123, "dd", "fff");
}

void Test_Locality::testReset()
{
    Locality l;
    l.setId(123);
    l.setName("dd");
    l.setDescription("fff");
    l.reset();
    compareDefault(&l);
}

void Test_Locality::testSignalId()
{
    Locality l;
    const TC::milk_id data = 15;
    QSignalSpy signalSpy(&l, &Locality::idChanged);
    l.setId(data);
    l.setId(data);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toLongLong(), data);
}

void Test_Locality::testSignalName()
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

void Test_Locality::testSignalDescription()
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
