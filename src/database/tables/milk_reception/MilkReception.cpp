#include "MilkReception.h"

#include "Utils.h"


MilkReception::MilkReception():
    _id(-1),
    _deliverer(Deliverer()),
    _milkPoint(MilkPoint()),
    _deliveryDate(QDate()),
    _priceLiter(.0f),
    _liters(.0f),
    _fat(.0f)
{

}

MilkReception::MilkReception(const Deliverer &deliverer, const MilkPoint &milkPoint,
                             const QDate deliveryDate, const float priceLiter,
                             const float liters, const float fat, const qint32 id):
    _id(id),
    _deliverer(deliverer),
    _milkPoint(milkPoint),
    _deliveryDate(deliveryDate),
    _priceLiter(priceLiter),
    _liters(liters),
    _fat(fat)
{

}

qint32 MilkReception::id() const
{
    return _id;
}

void MilkReception::setId(const qint32 &id)
{
    _id = id;
}

Deliverer MilkReception::deliverer() const
{
    return _deliverer;
}

MilkPoint MilkReception::milkPoint() const
{
    return _milkPoint;
}

QDate MilkReception::deliveryDate() const
{
    return _deliveryDate;
}

void MilkReception::setDeliveryDate(const QDate &deliveryDate)
{
    _deliveryDate = deliveryDate;
}

float MilkReception::priceLiter() const
{
    return _priceLiter;
}

void MilkReception::setPriceLiter(float priceLiter)
{
    _priceLiter = priceLiter;
}

float MilkReception::liters() const
{
    return _liters;
}

void MilkReception::setLiters(float liters)
{
    _liters = liters;
}

float MilkReception::fat() const
{
    return _fat;
}

void MilkReception::setFat(float fat)
{
    _fat = fat;
}

bool MilkReception::isNull() const
{
    return (_id < 0 || _deliverer.isNull() || _milkPoint.isNull());
}

QString MilkReception::toString() const
{
    return QString("Сдача молока(id: %1): %2, %3, delivery date: %4, price: %5, liters: %6, fat: %7")
            .arg(id())
            .arg(_deliverer.toString())
            .arg(_milkPoint.toString())
            .arg(_deliveryDate.toString())
            .arg(_priceLiter)
            .arg(_liters).arg(_fat);
}

MilkReception MilkReception::CREATE_NULL()
{
    return MilkReception(Deliverer::CREATE_NULL(), MilkPoint::CREATE_NULL(), QDate(),
                         .0f, .0f, .0f, -1);
}
