#include "Test_LocalityData.h"

#include <localitydata.h>
// Qt
#include <QSignalSpy>
#include <QTest>

using TC = TypesConstants;


Test_LocalityData::Test_LocalityData(QObject *parent) : QObject(parent)
{

}

void Test_LocalityData::compare(const LocalityData &localityData, const TC::milk_id id,
                            const QString &name, const QString &description)
{
    QCOMPARE(localityData.id(), id);
    QCOMPARE(localityData.name(), name);
    QCOMPARE(localityData.description(), description);
}

void Test_LocalityData::compareDefault(const LocalityData &localityData)
{
    compare(localityData, TC::Localities::DEF_ID, TC::Localities::DEF_NAME, TC::Localities::DEF_DESCRIPTION);
}

void Test_LocalityData::compare(const LocalityData &left, const LocalityData &right)
{
    compare(left, right.id(), right.name(), right.description());
}

void Test_LocalityData::emptyConstructor()
{
    LocalityData ld;
    compareDefault(ld);
}

void Test_LocalityData::constructor()
{
    LocalityData ld(42, "N", "Descr-");
    compare(ld, 42, "N", "Descr-");
}

void Test_LocalityData::copyConstructor()
{
    LocalityData ldToCopy(42, "N", "Descr-");
    LocalityData ld(ldToCopy);
    compare(ld, ldToCopy);
}

void Test_LocalityData::methods()
{
    LocalityData ld;
    ld.setId(123);
    ld.setName("dd");
    ld.setDescription("fff");
    compare(ld, 123, "dd", "fff");
}

void Test_LocalityData::storingInQVariant()
{
    LocalityData ldToCopy(42, "N", "Descr-");

    compare(QVariant::fromValue(ldToCopy).value<LocalityData>(), ldToCopy);
}
