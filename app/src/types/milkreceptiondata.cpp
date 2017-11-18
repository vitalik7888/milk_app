#include "milkreceptiondata.h"

#include "TypesConstants.h"

using TC = TypesConstants;
using TCMR = TC::MilkReception;


MilkReceptionData::MilkReceptionData():
    MilkReceptionData(TCMR::DEF_ID, TCMR::DEF_ID_DELIVERER, TCMR::DEF_MILK_POINT_ID,
                      TCMR::DEF_DELIVERY_DATE, TCMR::DEF_PRICE_LITER, TCMR::DEF_LITERS, TCMR::DEF_FAT)
{

}

MilkReceptionData::MilkReceptionData(const TC::milk_id id, const TC::milk_id delivererId,
                                     const TC::milk_id milkPointId, const QDate &deliveryDate,
                                     const double priceLiter, const double liters, const double fat):
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

TC::milk_id MilkReceptionData::id() const
{
    return m_id;
}

void MilkReceptionData::setId(const TC::milk_id &id)
{
    m_id = id;
}

TC::milk_id MilkReceptionData::delivererId() const
{
    return m_delivererId;
}

void MilkReceptionData::setDelivererId(const TC::milk_id &deliverer)
{
    m_delivererId = deliverer;
}

TC::milk_id MilkReceptionData::milkPointId() const
{
    return m_milkPointId;
}

void MilkReceptionData::setMilkPointId(const TC::milk_id &milkPoint)
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

double MilkReceptionData::priceLiter() const
{
    return m_priceLiter;
}

void MilkReceptionData::setPriceLiter(double priceLiter)
{
    m_priceLiter = priceLiter;
}

double MilkReceptionData::liters() const
{
    return m_liters;
}

void MilkReceptionData::setLiters(double liters)
{
    m_liters = liters;
}

double MilkReceptionData::fat() const
{
    return m_fat;
}

void MilkReceptionData::setFat(double fat)
{
    m_fat = fat;
}

bool MilkReceptionData::isValid() const
{
    return m_id > 0;
}
