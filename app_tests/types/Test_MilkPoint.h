#ifndef TEST_MILKPOINT_H
#define TEST_MILKPOINT_H

#include "TypesConstants.h"
// Qt
#include <QObject>

class MilkPoint;
class MilkPointData;
class Locality;


class Test_MilkPoint : public QObject
{
    Q_OBJECT
public:
    explicit Test_MilkPoint(QObject *parent = nullptr);

    static void compare(MilkPointData *mpd, const TypesConstants::milk_id id,
                        const TypesConstants::milk_id localityId, const QString &name, const QString &description);
    static void compareDefault(MilkPointData *mpd);
    static void compare(MilkPoint *mp,const TypesConstants::milk_id id, const QString &name, const QString &description,
                        Locality *locality);
    static void compareDefault(MilkPoint *mp);

private slots:
    void testEmptyDataConstructor();
    void testDataConstructor();
    void testDataMethods();
    void testEmptyConstructor();
    void testConstructor();
    void testMethods();
    void testReset();
    void testSignalId();
    void testSignalLocality();
    void testSignalName();
    void testSignalDescription();
};

#endif // TEST_MILKPOINT_H
