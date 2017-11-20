#include "Test_MilkPointData.h"

#include <MilkPointData.h>
// Qt
#include <QSignalSpy>
#include <QTest>

using TC = TypesConstants;
using TCMP = TC::MilkPoints;


Test_MilkPointData::Test_MilkPointData(QObject *parent) : QObject(parent)
{

}

void Test_MilkPointData::compare(const MilkPointData &mpd, const TC::milk_id id,
                             const TC::milk_id localityId, const QString &name,
                             const QString &description)
{
    QCOMPARE(mpd.id(), id);
    QCOMPARE(mpd.localityId(), localityId);
    QCOMPARE(mpd.name(), name);
    QCOMPARE(mpd.description(), description);
}

void Test_MilkPointData::compareDefault(const MilkPointData &mpd)
{
    compare(mpd, TCMP::DEF_ID, TCMP::DEF_LOCALITY_ID, TCMP::DEF_NAME, TCMP::DEF_DESCRIPTION);
}

void Test_MilkPointData::compare(const MilkPointData &left, const MilkPointData &right)
{
    compare(left, right.id(), right.localityId(), right.name(), right.description());
}

void Test_MilkPointData::emptyConstructor()
{
    MilkPointData mpd;
    compareDefault(mpd);
}

void Test_MilkPointData::constructor()
{
    MilkPointData mpd(42, 1, "n", "d");
    compare(mpd, 42, 1, "n", "d");
}

void Test_MilkPointData::copyConstructor()
{
    MilkPointData mpdToCopy(42, 1, "n", "d");
    compare(MilkPointData(mpdToCopy), mpdToCopy);
}

void Test_MilkPointData::methods()
{
    MilkPointData mpd;
    mpd.setId(42);
    mpd.setLocalityId(1);
    mpd.setName("n");
    mpd.setDescription("d");
    compare(mpd, 42, 1, "n", "d");
}

void Test_MilkPointData::storingInQVariant()
{
    MilkPointData mpdToCopy(42, 1, "n", "d");
    compare(QVariant::fromValue(mpdToCopy).value<MilkPointData>(), mpdToCopy);
}
