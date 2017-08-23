#include "milkreception.h"

#include "deliverer.h"
#include "milkpoint.h"


MilkReception::MilkReception(QObject *parent):
    MilkReception(-1, QDate(), .0, .0, .0, Q_NULLPTR, Q_NULLPTR, parent)
{

}

MilkReception::MilkReception(const milk_id id, const QDate deliveryDate, const price priceLiter,
                             const double liters, const double fat,
                             Deliverer *deliverer, MilkPoint *milkPoint, QObject *parent):
    QObject(parent),
    m_data(id, deliverer == Q_NULLPTR ? -1 : deliverer->id(),
               milkPoint == Q_NULLPTR ? -1 : milkPoint->id(),
           deliveryDate, priceLiter, liters, fat),
    m_deliverer(deliverer),
    m_milkPoint(milkPoint)
{

}

MilkReception::~MilkReception()
{

}

milk_id MilkReception::id() const
{
    return m_data.id();
}

void MilkReception::setId(const milk_id &id)
{
    m_data.setId(id);
}

Deliverer *MilkReception::deliverer() const
{
    return m_deliverer;
}

MilkPoint *MilkReception::milkPoint() const
{
    return m_milkPoint;
}

void MilkReception::setDeliverer(Deliverer *deliverer)
{
    m_deliverer = deliverer;
    m_data.setDelivererId(deliverer == Q_NULLPTR ? -1 : deliverer->id());
}

void MilkReception::setMilkPoint(MilkPoint *milkPoint)
{
    m_milkPoint = milkPoint;
    m_data.setMilkPointId(milkPoint == Q_NULLPTR ? -1 : milkPoint->id());
}

DB_NAMESPACE::MilkReceptionData MilkReception::data() const
{
    return m_data;
}

CalculatedItem::Data MilkReception::getCalculationsData() const
{
    return CalculatedItem(liters(), fat(), priceLiter()).data();
}

CalculatedItem *MilkReception::getCalculations()
{
    return new CalculatedItem(liters(), fat(), priceLiter(), this);
}

QDate MilkReception::deliveryDate() const
{
    return m_data.deliveryDate();
}

void MilkReception::setDeliveryDate(const QDate &deliveryDate)
{
    m_data.setDeliveryDate(deliveryDate);
}

double MilkReception::priceLiter() const
{
    return m_data.priceLiter();
}

void MilkReception::setPriceLiter(price priceLiter)
{
    m_data.setPriceLiter(priceLiter);
}

double MilkReception::liters() const
{
    return m_data.liters();
}

void MilkReception::setLiters(double liters)
{
    m_data.setLiters(liters);
}

double MilkReception::fat() const
{
    return m_data.fat();
}

void MilkReception::setFat(double fat)
{
    m_data.setFat(fat);
}

bool MilkReception::isValid() const
{
    return m_data.isValid();
}
