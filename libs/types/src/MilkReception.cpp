#include "MilkReception.h"

#include "Deliverer.h"
#include "MilkPoint.h"
#include "TypesConstants.h"

using TC = TypesConstants;


MilkReception::MilkReception():
    m_deliverer(Q_NULLPTR),
    m_milkPoint(Q_NULLPTR)
{
    m_data = new MilkReceptionData();
}

MilkReception::MilkReception(const MILK_ID id, const QDate &deliveryDate, const double priceLiter,
                             const double liters, const double fat,
                             const Deliverer *deliverer, const MilkPoint *milkPoint):
    m_deliverer(deliverer),
    m_milkPoint(milkPoint)
{
    m_data = new MilkReceptionData(id, m_deliverer ? deliverer->milkId() : TC::DEFAULT_ID,
                                   m_milkPoint ? m_milkPoint->milkId() : TC::DEFAULT_ID,
                                   deliveryDate, priceLiter, liters, fat);
}

MilkReception::MilkReception(const MilkReception &other):
    m_data(other.m_data),
    m_deliverer(other.deliverer()),
    m_milkPoint(other.milkPoint())
{

}

void MilkReception::setMilkId(const MILK_ID milkId)
{
    m_data->setMilkId(milkId);
}

void MilkReception::setDeliverer(const Deliverer *deliverer)
{
    m_deliverer = deliverer;
    m_data->setDelivererId(m_deliverer ? m_deliverer->milkId() : TC::DEFAULT_ID);
}

void MilkReception::setMilkPoint(const MilkPoint *milkPoint)
{
    m_milkPoint = milkPoint;
    m_data->setMilkPointId(m_milkPoint ? m_milkPoint->milkId() : TC::DEFAULT_ID);
}

void MilkReception::setDeliveryDate(const QDate &deliveryDate)
{
    m_data->setDeliveryDate(deliveryDate);
}

void MilkReception::setPriceLiter(double priceLiter)
{
    m_data->setPriceLiter(priceLiter);
}

void MilkReception::setLiters(double liters)
{
    m_data->setLiters(liters);
}

void MilkReception::setFat(double fat)
{
    m_data->setFat(fat);
}

bool MilkReception::isValid() const
{
    return m_data->isValid();
}

void MilkReception::reset()
{
    m_data->reset();
}
