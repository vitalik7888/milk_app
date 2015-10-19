#ifndef MILKRECEPTION_H
#define MILKRECEPTION_H

#include "tables/deliverers/Deliverer.h"
#include "tables/milk_points/MilkPoint.h"
#include <QDate>


class MilkReception {
public:
    MilkReception();
    MilkReception(const Deliverer &deliverer, const MilkPoint &milkPoint, const QDate deliveryDate,
                  const float priceLiter, const float liters, const float fat, const qint32 id = -1);

    qint32 id() const;
    void setId(const qint32 &id);

    QDate deliveryDate() const;
    void setDeliveryDate(const QDate &deliveryDate);

    float priceLiter() const;
    void setPriceLiter(float priceLiter);

    float liters() const;
    void setLiters(float liters);

    float fat() const;
    void setFat(float fat);

    bool isNull() const;

    QString toString() const;

    static MilkReception CREATE_NULL();

    Deliverer deliverer() const;

    MilkPoint milkPoint() const;

private:
    qint32 _id;
    Deliverer _deliverer;
    MilkPoint _milkPoint;
    QDate _deliveryDate;
    float _priceLiter;
    float _liters;
    float _fat;
};

#endif // MILKRECEPTION_H
