#ifndef CALCULATEDITEM_H
#define CALCULATEDITEM_H

#include <src/core/Constants.h>
// Qt
#include <QObject>


class CalculatedItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double liters READ liters)
    Q_PROPERTY(double fat READ fat)
    Q_PROPERTY(double priceForLiter READ priceForLiter)
    Q_PROPERTY(double protein READ protein)
    Q_PROPERTY(double fatUnits READ fatUnits)
    Q_PROPERTY(double rankWeight READ rankWeight)
    Q_PROPERTY(double paymentWithOutPremium READ paymentWithOutPremium)
    Q_PROPERTY(double premiumForFat READ premiumForFat)
    Q_PROPERTY(double sum READ sum)

public:
    struct Data {
        double liters = .0;
        double fat = .0;
        price priceForLiter = .0;
        double protein = .0;
        double fatUnits = .0;
        double rankWeight = .0;
        double paymentWithOutPremium = .0;
        double premiumForFat = .0;
        double sum = .0;
    };

    CalculatedItem(QObject *parent = Q_NULLPTR);
    CalculatedItem(const double liters, const double fat, const price priceForLiter, QObject *parent = Q_NULLPTR);

    double liters() const;
    double fat() const;
    price priceForLiter() const;
    double protein() const;
    double fatUnits() const;
    double rankWeight() const;
    double paymentWithOutPremium() const;
    double premiumForFat() const;
    double sum() const;

    CalculatedItem::Data data() const;

private:
    CalculatedItem::Data m_data;
};

CalculatedItem::Data operator+(const CalculatedItem::Data &l, const CalculatedItem::Data &r);
CalculatedItem::Data &operator+=(CalculatedItem::Data &l, const CalculatedItem::Data &r);

#endif // CALCULATEDITEM_H
