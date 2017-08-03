#ifndef UTILS
#define UTILS

#include "Constants.h"
#include "dbconstants.h"


namespace Utils {
class Main {
public:
    static bool isAutoIncrIdIsValid(const milk_id id);

    static QString getSelectStr(const QString &tableName, const QStringList &columns);
    static QString getPrepUpdateStr(const QString &tableName, const QStringList &columns);
    static QString getPrepInsertStr(const QString &tableName, const QStringList &columns);
};

namespace Calc {

struct CalcResult {
    double protein = .0;
    double fatUnits = .0;
    double rankWeight = .0;
    double paymentWithOutPremium = .0;
    double premiumForFat = .0;
    double sum = .0;
};

static inline double protein(const double fat)
{
    if(fat <= 0)
        return 0.0;

    return fat * Constants::BASE_PROTEIN / Constants::BASE_FAT;
}

static inline double fat(const double fatUnits, const double liters) {
    if (fatUnits <= .0 || liters <= .0)
        return .0;
    return fatUnits / liters;
}

static inline double liters(const double fatUnits, const double fat) {
    if (fatUnits <= .0 || fat <= .0)
        return .0;
    return fatUnits / fat;
}

static inline double fatUnits(const double liters, const double fat)
{
    return liters * fat;
}

static inline double rankWeight(const double fatUnits)
{
    if(fatUnits <= 0)
        return 0.0;

    return fatUnits / Constants::BASE_FAT; //qRound(fatUnits / BASE_FAT);
}

static inline double premiumForFat(const double fat, const double paymentWithOutPremium)
{
    if(fat <= 0)
        return 0.0;

    return (fat / Constants::BASE_FAT - 1) * paymentWithOutPremium;
}

static inline double paymentWithOutPremium(const double liters, const price price)
{
    return liters * price;
}

static inline double sum(const double rankWeight, const price price)
{
    return rankWeight * price;
}
static inline CalcResult getCalculations(const double liters, const double fat, const price price) {
    CalcResult calc;

    calc.protein = Utils::Calc::protein(fat);
    calc.fatUnits = Utils::Calc::fatUnits(liters, fat);
    calc.rankWeight = Utils::Calc::rankWeight(calc.fatUnits);
    calc.paymentWithOutPremium = Utils::Calc::paymentWithOutPremium(liters, price);
    calc.premiumForFat = Utils::Calc::premiumForFat(fat, calc.paymentWithOutPremium);
    calc.sum = Utils::Calc::sum(calc.rankWeight, price);

    return calc;
}
}
}

#endif // UTILS

