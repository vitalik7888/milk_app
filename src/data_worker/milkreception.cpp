#include "milkreception.h"

#include "deliverer.h"
#include "milkpoint.h"


MilkReception::MilkReception():
    MilkReception(-1, QDate(), .0f, .0f, .0f, WpDeliverer(), WpMilkPoint())
{

}

MilkReception::MilkReception(const milk_id id, const QDate deliveryDate, const float priceLiter,
                             const float liters, const float fat,
                             const WpDeliverer &deliverer,
                             const WpMilkPoint &milkPoint):
    m_data(id, deliverer.isNull() ? -1 : deliverer.data()->id(),
           milkPoint.isNull() ? -1 : milkPoint.data()->id(), deliveryDate, priceLiter, liters, fat),
    m_deliverer(deliverer),
    m_milkPoint(milkPoint)
{

}

MilkReception::MilkReception(const MilkReception &milkReception):
    m_data(milkReception.data()),
    m_deliverer(milkReception.deliverer()),
    m_milkPoint(milkReception.milkPoint())
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

WpDeliverer MilkReception::deliverer() const
{
    return m_deliverer;
}

WpMilkPoint MilkReception::milkPoint() const
{
    return m_milkPoint;
}

void MilkReception::setDeliverer(const WpDeliverer deliverer)
{
    m_deliverer = deliverer;
    m_data.setDelivererId(deliverer.isNull() ? -1 : deliverer.data()->id());
}

void MilkReception::setMilkPoint(const WpMilkPoint milkPoint)
{
    m_milkPoint = milkPoint;
    m_data.setMilkPointId(milkPoint.isNull() ? -1 : milkPoint.data()->id());
}

DB_NAMESPACE::MilkReceptionData MilkReception::data() const
{
    return m_data;
}

CalculatedItem MilkReception::getCalculations() const
{
    return CalculatedItem(liters(), fat(), priceLiter());
}

QDate MilkReception::deliveryDate() const
{
    return m_data.deliveryDate();
}

void MilkReception::setDeliveryDate(const QDate &deliveryDate)
{
    m_data.setDeliveryDate(deliveryDate);
}

float MilkReception::priceLiter() const
{
    return m_data.priceLiter();
}

void MilkReception::setPriceLiter(float priceLiter)
{
    m_data.setPriceLiter(priceLiter);
}

float MilkReception::liters() const
{
    return m_data.liters();
}

void MilkReception::setLiters(float liters)
{
    m_data.setLiters(liters);
}

float MilkReception::fat() const
{
    return m_data.fat();
}

void MilkReception::setFat(float fat)
{
    m_data.setFat(fat);
}

bool MilkReception::isValid() const
{
    return m_data.isValid();
}
