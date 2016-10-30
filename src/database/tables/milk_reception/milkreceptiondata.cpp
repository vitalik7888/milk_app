#include "milkreceptiondata.h"

USE_DB_NAMESPACE


MilkReceptionData::MilkReceptionData():
    MilkReceptionData(-1, -1, -1, QDate(), .0f, .0f, .0f)
{

}

MilkReceptionData::MilkReceptionData(const milk_id id, const milk_id delivererId,
                                     const milk_id milkPointId, const QDate &deliveryDate,
                                     const float priceLiter, const float liters, const float fat):
    m_id(id),
    m_delivererId(delivererId),
    m_milkPointId(milkPointId),
    m_deliveryDate(deliveryDate),
    m_priceLiter(priceLiter),
    m_liters(liters),
    m_fat(fat)
{

}

MilkReceptionData::MilkReceptionData(const MilkReceptionData &data):
    m_id(data.id()),
    m_delivererId(data.delivererId()),
    m_milkPointId(data.milkPointId()),
    m_deliveryDate(data.deliveryDate()),
    m_priceLiter(data.priceLiter()),
    m_liters(data.liters()),
    m_fat(data.fat())
{

}

MilkReceptionData::~MilkReceptionData()
{

}

milk_id MilkReceptionData::id() const
{
    return m_id;
}

void MilkReceptionData::setId(const milk_id &id)
{
    m_id = id;
}

milk_id MilkReceptionData::delivererId() const
{
    return m_delivererId;
}

void MilkReceptionData::setDelivererId(const milk_id &deliverer)
{
    m_delivererId = deliverer;
}

milk_id MilkReceptionData::milkPointId() const
{
    return m_milkPointId;
}

void MilkReceptionData::setMilkPointId(const milk_id &milkPoint)
{
    m_milkPointId = milkPoint;
}

QDate MilkReceptionData::deliveryDate() const
{
    return m_deliveryDate;
}

void MilkReceptionData::setDeliveryDate(const QDate &deliveryDate)
{
    m_deliveryDate = deliveryDate;
}

float MilkReceptionData::priceLiter() const
{
    return m_priceLiter;
}

void MilkReceptionData::setPriceLiter(float priceLiter)
{
    m_priceLiter = priceLiter;
}

float MilkReceptionData::liters() const
{
    return m_liters;
}

void MilkReceptionData::setLiters(float liters)
{
    m_liters = liters;
}

float MilkReceptionData::fat() const
{
    return m_fat;
}

void MilkReceptionData::setFat(float fat)
{
    m_fat = fat;
}

bool MilkReceptionData::isValid() const
{
    return m_id > 0;
}