#include "Test_Locality.h"
#include "Test_MilkPoint.h"

#include <locality.h>
#include <milkpoint.h>
// Qt
#include <QSignalSpy>
#include <QTest>

using TC = TypesConstants;
using TCMP = TC::MilkPoints;


Test_MilkPoint::Test_MilkPoint(QObject *parent) : QObject(parent)
{

}

void Test_MilkPoint::compare(MilkPointData *mpd, const TC::milk_id id,
                             const TC::milk_id localityId, const QString &name,
                             const QString &description)
{
    QCOMPARE(mpd->id(), id);
    QCOMPARE(mpd->localityId(), localityId);
    QCOMPARE(mpd->name(), name);
    QCOMPARE(mpd->description(), description);
}

void Test_MilkPoint::compareDefault(MilkPointData *mpd)
{
    compare(mpd, TCMP::DEF_ID, TCMP::DEF_LOCALITY_ID, TCMP::DEF_NAME, TCMP::DEF_DESCRIPTION);
}

void Test_MilkPoint::compare(MilkPoint *mp, const TC::milk_id id, const QString &name,
                             const QString &description, Locality *locality)
{
    QCOMPARE(mp->id(), id);
    QCOMPARE(mp->locality(), locality);
    if (locality)
        Test_Locality::compare(mp->locality(), locality->id(), locality->name(), locality->description());
    QCOMPARE(mp->name(), name);
    QCOMPARE(mp->description(), description);
}

void Test_MilkPoint::compareDefault(MilkPoint *mp)
{
    compare(mp, TCMP::DEF_ID, TCMP::DEF_NAME, TCMP::DEF_DESCRIPTION, Q_NULLPTR);
}

void Test_MilkPoint::testEmptyDataConstructor()
{
    MilkPointData mpd;
    compareDefault(&mpd);
}

void Test_MilkPoint::testDataConstructor()
{
    MilkPointData mpd(42, 1, "n", "d");
    compare(&mpd, 42, 1, "n", "d");
}

void Test_MilkPoint::testDataMethods()
{
    MilkPointData mpd;
    mpd.setId(42);
    mpd.setLocalityId(1);
    mpd.setName("n");
    mpd.setDescription("d");
    compare(&mpd, 42, 1, "n", "d");
}

void Test_MilkPoint::testEmptyConstructor()
{
    MilkPoint mp;
    compareDefault(&mp);
}

void Test_MilkPoint::testConstructor()
{
    Locality l({11, "ln", "ld"});
    MilkPoint mp(42, "n", "d", &l);
    compare(&mp, 42, "n", "d", &l);
}

void Test_MilkPoint::testMethods()
{
    Locality l({64, "lcn", "l234d"});

    MilkPoint mp;
    mp.setId(42);
    mp.setName("n");
    mp.setDescription("d");
    mp.setLocality(&l);
    compare(&mp, 42, "n", "d", &l);
}

void Test_MilkPoint::testReset()
{
    MilkPoint mp;
    mp.setId(42);
    mp.setName("n");
    mp.setDescription("d");
    mp.setLocality(new Locality(this));
    mp.reset();
    compareDefault(&mp);
}

void Test_MilkPoint::testSignalId()
{
    MilkPoint mp;
    const TC::milk_id data = 15;
    QSignalSpy signalSpy(&mp, &MilkPoint::idChanged);
    mp.setId(data);
    mp.setId(data);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toLongLong(), data);
}

void Test_MilkPoint::testSignalLocality()
{
    MilkPoint mp;
    Locality data({321, "dddd", "cccc"});
    QSignalSpy signalSpy(&mp, &MilkPoint::localityChanged);
    mp.setLocality(&data);
    mp.setLocality(&data);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    auto locality = qvariant_cast<Locality *>(arguments.first());

    Test_Locality::compare(&data, locality->id(), locality->name(), locality->description());
}

void Test_MilkPoint::testSignalName()
{
    MilkPoint mp;
    const QString data = "name";
    QSignalSpy signalSpy(&mp, &MilkPoint::nameChanged);
    mp.setName(data);
    mp.setName(data);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toString(), data);
}

void Test_MilkPoint::testSignalDescription()
{
    MilkPoint mp;
    const QString data = "descr";
    QSignalSpy signalSpy(&mp, &MilkPoint::descriptionChanged);
    mp.setDescription(data);
    mp.setDescription(data);
    QCOMPARE(signalSpy.count(), 1);
    const QVariantList arguments = signalSpy.first();
    QCOMPARE(arguments.at(0).toString(), data);
}
