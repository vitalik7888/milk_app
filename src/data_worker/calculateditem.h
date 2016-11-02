#ifndef CALCULATEDITEM_H
#define CALCULATEDITEM_H


class CalculatedItem
{
public:
    class Data {
    public:
        Data();


        float liters;
        float fat;
        float price;
        float protein;
        float fatUnits;
        float rankWeight;
        float paymentWithOutPremium;
        float premiumForFat;
        float sum;
    };

    CalculatedItem(const float liters, const float fat, const float priceForLiter);

    float liters() const;
    float fat() const;
    float price() const;
    float protein() const;
    float fatUnits() const;
    float rankWeight() const;
    float paymentWithOutPremium() const;
    float premiumForFat() const;
    float sum() const;

    CalculatedItem::Data data() const;

private:
    CalculatedItem::Data m_data;
};

CalculatedItem::Data operator+(const CalculatedItem::Data &l, const CalculatedItem::Data &r);
CalculatedItem::Data &operator+=(CalculatedItem::Data &l, const CalculatedItem::Data &r);

#endif // CALCULATEDITEM_H
