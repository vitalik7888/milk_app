#include "CalcUtils.h"

#include "CalcConstants.h"


double CalcUtils::protein(const double fat)
{
    if(fat <= 0)
        return 0.0;

    return fat * CalcConstants::BASE_PROTEIN / CalcConstants::BASE_FAT;
}

double CalcUtils::fat(const double fatUnits, const double liters) {
    if (fatUnits <= .0 || liters <= .0)
        return .0;
    return fatUnits / liters;
}

double CalcUtils::liters(const double fatUnits, const double fat) {
    if (fatUnits <= .0 || fat <= .0)
        return .0;
    return fatUnits / fat;
}

double CalcUtils::fatUnits(const double liters, const double fat)
{
    if (liters <= .0 || fat <= .0)
        return .0;

    return liters * fat;
}

double CalcUtils::rankWeight(const double fatUnits)
{
    if(fatUnits <= 0)
        return 0.0;

    return fatUnits / CalcConstants::BASE_FAT; //qRound(fatUnits / BASE_FAT);
}

double CalcUtils::premiumForFat(const double fat, const double paymentWithOutPremium)
{
    if(fat <= 0)
        return 0.0;

    return (fat / CalcConstants::BASE_FAT - 1) * paymentWithOutPremium;
}

double CalcUtils::paymentWithOutPremium(const double liters, const double price)
{
    if (liters <= .0 || price <= .0)
        return .0;
    return liters * price;
}

double CalcUtils::sum(const double rankWeight, const double price)
{
    if (rankWeight <= .0 || price <= .0)
        return .0;
    return rankWeight * price;
}
