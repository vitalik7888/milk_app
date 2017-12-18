#ifndef IMILKRECEPTION_H
#define IMILKRECEPTION_H

#include "IMilkBaseType.h"
// Qt
#include <QDate>


class TYPESLIBRARYSHARED_EXPORT IMilkReception : public IMilkBaseType
{
public:
    virtual int delivererId() const = 0;
    virtual void setDelivererId(const int delivererId) = 0;

    virtual int milkPointId() const = 0;
    virtual void setMilkPointId(const int milkPointId) = 0;

    virtual QDate deliveryDate() const = 0;
    virtual void setDeliveryDate(const QDate &deliveryDate) = 0;

    virtual double priceLiter() const = 0;
    virtual void setPriceLiter(double priceLiter) = 0;

    virtual double liters() const = 0;
    virtual void setLiters(double liters) = 0;

    virtual double fat() const = 0;
    virtual void setFat(double fat) = 0;
};

#define IMilkReception_iid "com.milk.IMilkReception"

#endif // IMILKRECEPTION_H
