#include "calculateditem.h"

#include "Utils.h"

//--------------------------------------------------------------------------------------------------
CalculatedItem::CalculatedItem(QObject *parent):
    CalculatedItem(.0, .0, .0, parent)
{

}

CalculatedItem::CalculatedItem(const double liters, const double fat, const price priceForLiter, QObject *parent):
    QObject(parent),
    m_data(calculate(liters, fat, priceForLiter))
{
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

CalculatedItem::Data CalculatedItem::calculate(const double liters, const double fat, const price priceForLiter)
{
    CalculatedItem::Data data;
    data.liters = liters;
    data.fat = fat;
    data.priceForLiter = priceForLiter;
    data.protein = Utils::Calc::protein(fat);
    data.fatUnits = Utils::Calc::fatUnits(liters, fat);
    data.rankWeight = Utils::Calc::rankWeight(data.fatUnits);
    data.paymentWithOutPremium = Utils::Calc::paymentWithOutPremium(data.liters, data.priceForLiter);
    data.premiumForFat = Utils::Calc::premiumForFat(fat, data.paymentWithOutPremium);
    data.sum = Utils::Calc::sum(data.rankWeight, data.priceForLiter);

    return data;
}

CalculatedItem::Data CalculatedItem::data() const
{
    return m_data;
}

//CalculatedItem *CalculatedItem::operator+(CalculatedItem *r)
//{
//    auto ci = new CalculatedItem(); // FIXME parent
//    ci->m_data = ci->m_data + r->data();
//    return ci;
//}

CalculatedItem *CalculatedItem::operator+=(CalculatedItem *r)
{
    m_data += r->data();
    return this;
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
