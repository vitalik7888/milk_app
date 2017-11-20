#include "CalculatedItem.h"

#include "CalcUtils.h"


CalculatedItem::CalculatedItem(QObject *parent):
    QObject(parent),
    m_data()
{

}

CalculatedItem::CalculatedItem(const double liters, const double fat, const double priceForLiter, QObject *parent):
    QObject(parent),
    m_data(liters, fat, priceForLiter)
{
}

double CalculatedItem::liters() const
{
    return m_data.liters();
}

double CalculatedItem::fat() const
{
    return m_data.fat();
}

double CalculatedItem::priceForLiter() const
{
    return m_data.priceForLiter();
}

double CalculatedItem::protein() const
{
    return m_data.protein();
}

double CalculatedItem::fatUnits() const
{
    return m_data.fatUnits();
}

double CalculatedItem::rankWeight() const
{
    return m_data.rankWeight();
}

double CalculatedItem::paymentWithOutPremium() const
{
    return m_data.paymentWithOutPremium();
}

double CalculatedItem::premiumForFat() const
{
    return m_data.premiumForFat();
}

double CalculatedItem::sum() const
{
    return m_data.sum();
}

CalculatedItemData CalculatedItem::data() const
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
