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

void Test_MilkPoint::compare(MilkPoint *left, MilkPoint *right)
{
    compare(left, right->id(), right->name(), right->description(), right->locality());
}

void Test_MilkPoint::storingInQVariant()
{
    MilkPoint mpToCopy(42, "n", "d", new Locality({11, "ln", "ld"}));
    auto mp = QVariant::fromValue(mpToCopy).value<MilkPoint>();
    compare(&mp, &mpToCopy);
}

void Test_MilkPoint::emptyConstructor()
{
    MilkPoint mp;
    compareDefault(&mp);
}

void Test_MilkPoint::copyConstructor()
{
    MilkPoint mpToCopy(42, "n", "d", new Locality({11, "ln", "ld"}));
    compare(new MilkPoint(mpToCopy), &mpToCopy);
}

void Test_MilkPoint::constructor()
{
    Locality l({11, "ln", "ld"});
    MilkPoint mp(42, "n", "d", &l);
    compare(&mp, 42, "n", "d", &l);
}

void Test_MilkPoint::methods()
{
    Locality l({64, "lcn", "l234d"});

    MilkPoint mp;
    mp.setId(42);
    mp.setName("n");
    mp.setDescription("d");
    mp.setLocality(&l);
    compare(&mp, 42, "n", "d", &l);
}

void Test_MilkPoint::reset()
{
    MilkPoint mp;
    mp.setId(42);
    mp.setName("n");
    mp.setDescription("d");
    mp.setLocality(new Locality(this));
    mp.reset();
    compareDefault(&mp);
}

void Test_MilkPoint::signalIdChanged()
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

void Test_MilkPoint::signalLocalityChanged()
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

void Test_MilkPoint::signalNameChanged()
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

void Test_MilkPoint::signalDescriptionChanged()
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
