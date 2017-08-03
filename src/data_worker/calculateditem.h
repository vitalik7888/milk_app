#ifndef CALCULATEDITEM_H
#define CALCULATEDITEM_H

#include <src/core/Constants.h>

class CalculatedItem
{
public:
    class Data {
    public:
        Data();

        double liters;
        double fat;
        price priceForLiter;
        double protein;
        double fatUnits;
        double rankWeight;
        double paymentWithOutPremium;
        double premiumForFat;
        double sum;
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
