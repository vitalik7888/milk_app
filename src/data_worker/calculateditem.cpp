#include "calculateditem.h"

#include "Utils.h"

//--------------------------------------------------------------------------------------------------
CalculatedItem::Data::Data():
    liters(.0),
    fat(.0),
    price(.0),
    protein(.0),
    fatUnits(.0),
    rankWeight(.0),
    paymentWithOutPremium(.0),
    premiumForFat(.0),
    sum(.0)
{

}

//--------------------------------------------------------------------------------------------------
CalculatedItem::CalculatedItem(const double liters, const double fat, const double priceForLiter):
    m_data()
{
    m_data.liters = liters;
    m_data.fat = fat;
    m_data.price = priceForLiter;
    m_data.protein = Utils::Calc::protein(fat);
    m_data.fatUnits = Utils::Calc::fatUnits(liters, fat);
    m_data.rankWeight = Utils::Calc::rankWeight(m_data.fatUnits);
    m_data.paymentWithOutPremium = Utils::Calc::paymentWithOutPremium(m_data.liters, m_data.price);
    m_data.premiumForFat = Utils::Calc::premiumForFat(fat, m_data.paymentWithOutPremium);
    m_data.sum = Utils::Calc::sum(m_data.rankWeight, m_data.price);
}

double CalculatedItem::liters() const
{
    return m_data.liters;
}

double CalculatedItem::fat() const
{
    return m_data.fat;
}

double CalculatedItem::price() const
{
    return m_data.price;
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
    result.premiumForFat = l.premiumForFat + l.premiumForFat;
    result.sum = l.sum + r.sum;
    result.fat = Utils::Calc::fat(result.fatUnits, result.liters),
    result.protein = Utils::Calc::protein(result.fat),
    result.rankWeight = Utils::Calc::rankWeight(result.fatUnits);

    return result;
}

CalculatedItem::Data &operator+=(CalculatedItem::Data &l, const CalculatedItem::Data &r)
{
    l.liters += r.liters;
    l.fatUnits += r.fatUnits;
    l.paymentWithOutPremium += r.paymentWithOutPremium;
    l.premiumForFat += l.premiumForFat;
    l.sum += r.sum;
    l.fat = Utils::Calc::fat(l.fatUnits, l.liters),
    l.protein = Utils::Calc::protein(l.fat),
    l.rankWeight = Utils::Calc::rankWeight(l.fatUnits);

    return l;
}
