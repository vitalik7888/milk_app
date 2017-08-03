#include "calculateditem.h"

#include "Utils.h"

//--------------------------------------------------------------------------------------------------
CalculatedItem::CalculatedItem(const double liters, const double fat, const price priceForLiter):
    m_data({liters, fat, priceForLiter})
{
    m_data.protein = Utils::Calc::protein(fat);
    m_data.fatUnits = Utils::Calc::fatUnits(liters, fat);
    m_data.rankWeight = Utils::Calc::rankWeight(m_data.fatUnits);
    m_data.paymentWithOutPremium = Utils::Calc::paymentWithOutPremium(m_data.liters, m_data.priceForLiter);
    m_data.premiumForFat = Utils::Calc::premiumForFat(fat, m_data.paymentWithOutPremium);
    m_data.sum = Utils::Calc::sum(m_data.rankWeight, m_data.priceForLiter);
}

double CalculatedItem::liters() const
{
    return m_data.liters;
}

double CalculatedItem::fat() const
{
    return m_data.fat;
}

double CalculatedItem::priceForLiter() const
{
    return m_data.priceForLiter;
}

double CalculatedItem::protein() const
{
    return m_data.protein;
}

double CalculatedItem::fatUnits() const
{
    return m_data.fatUnits;
}

double CalculatedItem::rankWeight() const
{
    return m_data.rankWeight;
}

double CalculatedItem::paymentWithOutPremium() const
{
    return m_data.paymentWithOutPremium;
}

double CalculatedItem::premiumForFat() const
{
    return m_data.premiumForFat;
}

double CalculatedItem::sum() const
{
    return m_data.sum;
}

CalculatedItem::Data CalculatedItem::data() const
{
    return m_data;
}

CalculatedItem::Data operator+(const CalculatedItem::Data &l, const CalculatedItem::Data &r)
{
    CalculatedItem::Data result;
    result.liters = l.liters + r.liters;
    result.fatUnits = l.fatUnits + r.fatUnits;
    result.paymentWithOutPremium = l.paymentWithOutPremium + r.paymentWithOutPremium;
    result.premiumForFat = l.premiumForFat + r.premiumForFat;
    result.sum = l.sum + r.sum;
    result.fat = Utils::Calc::fat(result.fatUnits, result.liters);
    result.protein = Utils::Calc::protein(result.fat);
    result.rankWeight = Utils::Calc::rankWeight(result.fatUnits);

    return result;
}

CalculatedItem::Data &operator+=(CalculatedItem::Data &l, const CalculatedItem::Data &r)
{
    l.liters += r.liters;
    l.fatUnits += r.fatUnits;
    l.paymentWithOutPremium += r.paymentWithOutPremium;
    l.premiumForFat += r.premiumForFat;
    l.sum += r.sum;
    l.fat = Utils::Calc::fat(l.fatUnits, l.liters);
    l.protein = Utils::Calc::protein(l.fat);
    l.rankWeight = Utils::Calc::rankWeight(l.fatUnits);

    return l;
}
