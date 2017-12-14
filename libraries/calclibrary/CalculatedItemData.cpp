#include "CalcUtils.h"

#include "CalculatedItemData.h"


CalculatedItemData::CalculatedItemData(const double liters, const double fat, const double priceForLiter):
    m_liters(liters),
    m_fat(fat),
    m_priceForLiter(priceForLiter)
{
    calculate();
}

CalculatedItemData::CalculatedItemData():
    m_liters(.0),
    m_fat(.0),
    m_priceForLiter(.0),
    m_protein(.0),
    m_fatUnits(.0),
    m_rankWeight(.0),
    m_paymentWithOutPremium(.0),
    m_premiumForFat(.0),
    m_sum(.0)
{

}

void CalculatedItemData::calculate()
{
    m_protein = CalcUtils::protein(m_fat);
    m_fatUnits = CalcUtils::fatUnits(m_liters, m_fat);
    m_rankWeight = CalcUtils::rankWeight(m_fatUnits);
    m_paymentWithOutPremium = CalcUtils::paymentWithOutPremium(m_liters, m_priceForLiter);
    m_premiumForFat = CalcUtils::premiumForFat(m_fat, m_paymentWithOutPremium);
    m_sum = CalcUtils::sum(m_rankWeight, m_priceForLiter);
}

CalculatedItemData CalculatedItemData::operator+(const CalculatedItemData &r)
{
    CalculatedItemData result;
    result.m_liters = liters() + r.liters();
    result.m_fatUnits = fatUnits() + r.fatUnits();
    result.m_paymentWithOutPremium = paymentWithOutPremium() + r.paymentWithOutPremium();
    result.m_premiumForFat = premiumForFat() + r.premiumForFat();
    result.m_sum = sum() + r.sum();
    result.m_fat = CalcUtils::fat(result.fatUnits(), result.liters());
    result.m_protein = CalcUtils::protein(result.fat());
    result.m_rankWeight = CalcUtils::rankWeight(result.fatUnits());

    return result;
}

CalculatedItemData &CalculatedItemData::operator+=(const CalculatedItemData &r)
{
    m_liters += r.liters();
    m_fatUnits += r.fatUnits();
    m_paymentWithOutPremium += r.paymentWithOutPremium();
    m_premiumForFat += r.premiumForFat();
    m_sum += r.sum();
    m_fat = CalcUtils::fat(m_fatUnits, m_liters);
    m_protein = CalcUtils::protein(m_fat);
    m_rankWeight = CalcUtils::rankWeight(m_fatUnits);

    return *this;
}
