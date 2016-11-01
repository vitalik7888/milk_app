#ifndef CALCULATEDITEM_H
#define CALCULATEDITEM_H


class CalculatedItem
{
public:
    CalculatedItem(const float liters, const float fat, const float priceForLiter);

    float protein() const;

    float fatUnits() const;

    float rankWeight() const;

    float paymentWithOutPremium() const;

    float premiumForFat() const;

    float sum() const;

private:
    float m_protein;
    float m_fatUnits;
    float m_rankWeight;
    float m_paymentWithOutPremium;
    float m_premiumForFat;
    float m_sum;
};

#endif // CALCULATEDITEM_H
