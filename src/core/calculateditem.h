#ifndef CALCULATEDITEM_H
#define CALCULATEDITEM_H

#include <src/core/Constants.h>

class CalculatedItem
{
public:
    struct Data {
        double liters = .0;
        double fat = .0;
        price priceForLiter = .0;
        double protein = .0;
        double fatUnits = .0;
        double rankWeight = .0;
        double paymentWithOutPremium = .0;
        double premiumForFat = .0;
        double sum = .0;
    };

    CalculatedItem(const double liters, const double fat, const price priceForLiter);

    double liters() const;
    double fat() const;
    price priceForLiter() const;
    double protein() const;
    double fatUnits() const;
    double rankWeight() const;
    double paymentWithOutPremium() const;
    double premiumForFat() const;
    double sum() const;

    CalculatedItem::Data data() const;

private:
    CalculatedItem::Data m_data;
};

CalculatedItem::Data operator+(const CalculatedItem::Data &l, const CalculatedItem::Data &r);
CalculatedItem::Data &operator+=(CalculatedItem::Data &l, const CalculatedItem::Data &r);

#endif // CALCULATEDITEM_H
