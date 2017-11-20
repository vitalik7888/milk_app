#ifndef CALCULATEDITEM_H
#define CALCULATEDITEM_H

#include "CalculatedItemData.h"
// Qt
#include <QObject>


class CalculatedItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double liters READ liters CONSTANT)
    Q_PROPERTY(double fat READ fat CONSTANT)
    Q_PROPERTY(double priceForLiter READ priceForLiter CONSTANT)
    Q_PROPERTY(double protein READ protein CONSTANT)
    Q_PROPERTY(double fatUnits READ fatUnits CONSTANT)
    Q_PROPERTY(double rankWeight READ rankWeight CONSTANT)
    Q_PROPERTY(double paymentWithOutPremium READ paymentWithOutPremium CONSTANT)
    Q_PROPERTY(double premiumForFat READ premiumForFat CONSTANT)
    Q_PROPERTY(double sum READ sum CONSTANT)

public:
    CalculatedItem(QObject *parent = Q_NULLPTR);
    CalculatedItem(const double liters, const double fat, const double priceForLiter, QObject *parent = Q_NULLPTR);

    double liters() const;
    double fat() const;
    double priceForLiter() const;
    double protein() const;
    double fatUnits() const;
    double rankWeight() const;
    double paymentWithOutPremium() const;
    double premiumForFat() const;
    double sum() const;

    CalculatedItemData data() const;

//    CalculatedItem *operator+(CalculatedItem *r) = delete;
    CalculatedItem *operator+=(CalculatedItem *r);

private:
    CalculatedItemData m_data;
};

#endif // CALCULATEDITEM_H
