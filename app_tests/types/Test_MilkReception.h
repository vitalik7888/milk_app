#ifndef TEST_MILKRECEPTION_H
#define TEST_MILKRECEPTION_H

#include "TypesConstants.h"
// Qt
#include <QObject>

class MilkReceptionData;
class MilkReception;
class MilkPoint;
class Deliverer;


class Test_MilkReception : public QObject
{
    Q_OBJECT
public:
    explicit Test_MilkReception(QObject *parent = nullptr);

    static void compare(MilkReceptionData *mrd, const TypesConstants::milk_id id,
                        const TypesConstants::milk_id delivererId, const TypesConstants::milk_id milkPointId,
                        const QDate &deliveryDate, const double priceLiter,
                        const double liters, const double fat);
    static void compareDefault(MilkReceptionData *mrd);
    static void compare(MilkReception *mr,const TypesConstants::milk_id id, const QDate deliveryDate,
                        const double priceLiter, const double liters, const double fat,
                        Deliverer *deliverer, MilkPoint *milkPoint);
    static void compareDefault(MilkReception *mr);

private slots:
    void testEmptyDataConstructor();
    void testDataConstructor();
    void testDataMethods();
    void testEmptyConstructor();
    void testConstructor();
    void testMethods();
    void testReset();
    void testSignalId();
    void testSignalDeliveryDate();
    void testSignalPriceLiter();
    void testSignalLiters();
    void testSignalFat();
    void testSignalDeliverer();
    void testSignalMilkPoint();
};

#endif // TEST_MILKRECEPTION_H
