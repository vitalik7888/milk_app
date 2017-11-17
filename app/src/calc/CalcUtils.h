#ifndef CALCUTILS_H
#define CALCUTILS_H


class CalcUtils
{
public:
    static double protein(const double fat);
    static double fat(const double fatUnits, const double liters);
    static double liters(const double fatUnits, const double fat);
    static double fatUnits(const double liters, const double fat);
    static double rankWeight(const double fatUnits);
    static double premiumForFat(const double fat, const double paymentWithOutPremium);
    static double paymentWithOutPremium(const double liters, const double price);
    static double sum(const double rankWeight, const double price);
};

#endif // CALCUTILS_H
