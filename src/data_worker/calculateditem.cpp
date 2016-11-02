#include "calculateditem.h"

#include "Utils.h"

//--------------------------------------------------------------------------------------------------
CalculatedItem::Data::Data():
    liters(.0f),
    fat(.0f),
    price(.0f),
    protein(.0f),
    fatUnits(.0f),
    rankWeight(.0f),
    paymentWithOutPremium(.0f),
    premiumForFat(.0f),
    sum(.0f)
{

}

//--------------------------------------------------------------------------------------------------
CalculatedItem::CalculatedItem(const float liters, const float fat, const float priceForLiter):
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

float CalculatedItem::liters() const
{
    return m_data.liters;
}

float CalculatedItem::fat() const
{
    return m_data.fat;
}

float CalculatedItem::price() const
{
    return m_data.price;
}

float CalculatedItem::protein() const
{
    return m_data.protein;
}

float CalculatedItem::fatUnits() const
{
    return m_data.fatUnits;
}

float CalculatedItem::rankWeight() const
{
    return m_data.rankWeight;
}

float CalculatedItem::paymentWithOutPremium() const
{
    return m_data.paymentWithOutPremium;
}

float CalculatedItem::premiumForFat() const
{
    return m_data.premiumForFat;
}

float CalculatedItem::sum() const
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
