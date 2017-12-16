#ifndef TEST_CALCULATEDITEM_H
#define TEST_CALCULATEDITEM_H

#include <QObject>

class CalculatedItemData;


class Test_CalculatedItemData : public QObject
{
    Q_OBJECT
public:
    explicit Test_CalculatedItemData(QObject *parent = nullptr);

    static void compare(const CalculatedItemData &item, const double liters, const double fat, const double priceForLiter,
                        const double protein, const double fatUnits, const double rankWeight,
                        const double paymentWithOutPremium, const double premiumForFat, const double sum);
private slots:
    void emptyConstructor();
    void calculatedResult_data();
    void calculatedResult();
    void add();
};

#endif // TEST_CALCULATEDITEM_H
