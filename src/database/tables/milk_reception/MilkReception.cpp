#include "MilkReception.h"

#include "Utils.h"

USE_DB_NAMESPACE


MilkReception::MilkReception():
    MilkReception(-1, Deliverer(), MilkPoint(), QDate(), .0f, .0f, .0f)
{

}

MilkReception::MilkReception(const milk_id id, const Deliverer &deliverer, const MilkPoint &milkPoint,
                             const QDate deliveryDate, const float priceLiter,
                             const float liters, const float fat):
    m_data(id, deliverer.id(), milkPoint.id(), deliveryDate, priceLiter, liters, fat),
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

Deliverer MilkReception::deliverer() const
{
    return m_deliverer;
}

MilkPoint MilkReception::milkPoint() const
{
    return m_milkPoint;
}

void MilkReception::setDeliverer(const Deliverer &deliverer)
{
    m_deliverer = deliverer;
    m_data.setDelivererId(m_deliverer.id());
}

void MilkReception::setMilkPoint(const MilkPoint &milkPoint)
{
    m_milkPoint = milkPoint;
    m_data.setMilkPointId(m_milkPoint.id());
}

MilkReceptionData MilkReception::data() const
{
    return m_data;
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
