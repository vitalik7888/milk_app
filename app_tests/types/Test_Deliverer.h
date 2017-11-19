#ifndef TEST_DELIVERER_H
#define TEST_DELIVERER_H

#include "TypesConstants.h"
// Qt
#include <QObject>

class DelivererData;
class Deliverer;
class Locality;


class Test_Deliverer : public QObject
{
    Q_OBJECT
public:
    explicit Test_Deliverer(QObject *parent = nullptr);

    static void compare(DelivererData *deliverer, const TypesConstants::milk_id id,
                        const QString &name, const TypesConstants::milk_id localityId, const TypesConstants::milk_inn inn,
                        const QString &address, const QString &phoneNumber);
    static void compareDefault(DelivererData *deliverer);
    static void compare(Deliverer *deliverer, const TypesConstants::milk_id id,
                        const QString &name, Locality *locality, const TypesConstants::milk_inn inn,
                        const QString &address, const QString &phoneNumber);
    static void compareDefault(Deliverer *deliverer);

private slots:
    void testEmptyDataConstructor();
    void testDataConstructor();
    void testDataMethods();
    void testEmptyConstructor();
    void testCopyConstructor();
    void testConstructor();
    void testMethods();
    void testReset();
    void testSignalId();
    void testSignalLocality();
    void testSignalName();
    void testSignalInn();
    void testSignalAddress();
    void testSignalPhoneNumber();
};

#endif // TEST_DELIVERER_H
