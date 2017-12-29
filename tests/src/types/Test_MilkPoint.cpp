#include "types/Test_MilkPoint.h"

#include "types/Test_Locality.h"
#include <TypesConstants.h>
#include <Locality.h>
#include <MilkPoint.h>
// Qt
#include <QSignalSpy>
#include <QTest>

using TC = TypesConstants;
using TCMP = TC::MilkPoints;


Test_MilkPoint::Test_MilkPoint(QObject *parent) : QObject(parent)
{

}

void Test_MilkPoint::compare(const MilkPoint *mp, const int id, const QString &name,
                             const QString &description, const Locality *locality)
{
    QCOMPARE(mp->milkId(), id);
    if (locality)
        Test_Locality::compare(mp->locality(), locality->milkId(), locality->name(),
                               locality->description());
    QCOMPARE(mp->name(), name);
    QCOMPARE(mp->description(), description);
}

void Test_MilkPoint::compareDefault(const MilkPoint *mp)
{
    compare(mp, TC::DEFAULT_ID, TCMP::DEF_NAME, TCMP::DEF_DESCRIPTION, Q_NULLPTR);
}

void Test_MilkPoint::compare(const MilkPoint *left, const MilkPoint *right)
{
    compare(left, right->milkId(), right->name(), right->description(), right->locality());
}

void Test_MilkPoint::storingInQVariant()
{
    Locality locality{11, "ln", "ld"};
    MilkPoint mpToCopy(42, "n", "d", &locality);
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
    Locality locality{11, "ln", "ld"};
    MilkPoint mpToCopy(42, "n", "d", &locality);
    compare(new MilkPoint(mpToCopy), &mpToCopy);
}

void Test_MilkPoint::constructor()
{
    Locality l{11, "ln", "ld"};
    MilkPoint mp(42, "n", "d", &l);
    compare(&mp, 42, "n", "d", &l);
}

void Test_MilkPoint::methods()
{
    Locality l(64, "lcn", "l234d");

    MilkPoint mp;
    mp.setMilkId(42);
    mp.setName("n");
    mp.setDescription("d");
    mp.setLocality(&l);
    compare(&mp, 42, "n", "d", &l);
}

void Test_MilkPoint::reset()
{
    Locality l(64, "lcn", "l234d");
    MilkPoint mp;
    mp.setMilkId(42);
    mp.setName("n");
    mp.setDescription("d");
    mp.setLocality(&l);
    mp.reset();
    compareDefault(&mp);
}
