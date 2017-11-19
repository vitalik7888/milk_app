#ifndef TEST_LOCALITY_H
#define TEST_LOCALITY_H

#include "TypesConstants.h"
// Qt
#include <QObject>

class LocalityData;
class Locality;


class Test_Locality : public QObject
{
    Q_OBJECT
public:
    explicit Test_Locality(QObject *parent = nullptr);

    static void compare(LocalityData *locality, const TypesConstants::milk_id id,
                        const QString &name, const QString &description);
    static void compareDefault(LocalityData *locality);
    static void compare(Locality *locality, const TypesConstants::milk_id id,
                        const QString &name, const QString &description);
    static void compareDefault(Locality *locality);

private slots:
    void testEmptyDataConstructor();
    void testDataConstructor();
    void testDataCopyConstructor();
    void testDataMethods();
    void testEmptyConstructor();
    void testCopyConstructor();
    void testConstructor();
    void testMethods();
    void testReset();
    void testSignalId();
    void testSignalName();
    void testSignalDescription();
};

#endif // TEST_LOCALITY_H
