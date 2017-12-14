#ifndef CALCULATEDITEMDATA_H
#define CALCULATEDITEMDATA_H

#include "calclibrary_global.h"


class CALCLIBRARYSHARED_EXPORT CalculatedItemData
{
public:
    CalculatedItemData(const double liters, const double fat, const double priceForLiter);
    CalculatedItemData();

    double liters() const { return m_liters; }
    double fat() const { return m_fat; }
    double priceForLiter() const { return m_priceForLiter; }
    double protein() const { return m_protein; }
    double fatUnits() const { return m_fatUnits; }
    double rankWeight() const { return m_rankWeight; }
    double paymentWithOutPremium() const { return m_paymentWithOutPremium; }
    double premiumForFat() const { return m_premiumForFat; }
    double sum() const { return m_sum; }

    CalculatedItemData operator+(const CalculatedItemData &data);
    CalculatedItemData &operator+=(const CalculatedItemData &r);

private:
    double m_liters;
    double m_fat;
    double m_priceForLiter;
    double m_protein;
    double m_fatUnits;
    double m_rankWeight;
    double m_paymentWithOutPremium;
    double m_premiumForFat;
    double m_sum;

    void calculate();
};


#endif // CALCULATEDITEMDATA_H
