#include "calculateditem.h"

#include "Utils.h"


CalculatedItem::CalculatedItem(const float liters, const float fat, const float priceForLiter):
    m_protein(Utils::Calc::protein(fat)),
    m_fatUnits(Utils::Calc::fatUnits(liters, fat)),
    m_rankWeight(Utils::Calc::rankWeight(m_fatUnits)),
    m_paymentWithOutPremium(Utils::Calc::paymentWithOutPremium(liters, priceForLiter)),
    m_premiumForFat(Utils::Calc::premiumForFat(fat, m_paymentWithOutPremium)),
    m_sum(Utils::Calc::sum(m_rankWeight, priceForLiter))
{
}

float CalculatedItem::protein() const
{
    return m_protein;
}

float CalculatedItem::fatUnits() const
{
    return m_fatUnits;
}

float CalculatedItem::rankWeight() const
{
    return m_rankWeight;
}

float CalculatedItem::paymentWithOutPremium() const
{
    return m_paymentWithOutPremium;
}

float CalculatedItem::premiumForFat() const
{
    return m_premiumForFat;
}

float CalculatedItem::sum() const
{
    return m_sum;
}
