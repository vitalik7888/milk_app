#ifndef TEST_MILKRECEPTIONDATA_H
#define TEST_MILKRECEPTIONDATA_H

#include "TypesConstants.h"
// Qt
#include <QObject>

class MilkReceptionData;


class Test_MilkReceptionData : public QObject
{
    Q_OBJECT
public:
    explicit Test_MilkReceptionData(QObject *parent = nullptr);

    static void compare(const MilkReceptionData &mrd, const TypesConstants::milk_id id,
                        const TypesConstants::milk_id delivererId, const TypesConstants::milk_id milkPointId,
                        const QDate &deliveryDate, const double priceLiter,
                        const double liters, const double fat);
    static void compareDefault(const MilkReceptionData &mrd);
    static void compare(const MilkReceptionData &left, const MilkReceptionData &right);

private slots:
    void emptyConstructor();
    void constructor();
    void copyConstructor();
    void methods();
    void storingInQVariant();
};

#endif // TEST_MILKRECEPTIONDATA_H
