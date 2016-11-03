#include "milkreception.h"

#include "deliverer.h"
#include "milkpoint.h"


MilkReception::MilkReception():
    MilkReception(-1, QDate(), .0, .0, .0, WpDeliverer(), WpMilkPoint())
{

}

MilkReception::MilkReception(const milk_id id, const QDate deliveryDate, const double priceLiter,
                             const double liters, const double fat,
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

double MilkReception::priceLiter() const
{
    return m_data.priceLiter();
}

void MilkReception::setPriceLiter(double priceLiter)
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
