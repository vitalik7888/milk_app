#include "MilkReceptionData.h"

#include "TypesConstants.h"

using TC = TypesConstants;
using TCMR = TC::MilkReception;


MilkReceptionData::MilkReceptionData():
    MilkReceptionData(TC::DEFAULT_ID, TC::DEFAULT_ID, TC::DEFAULT_ID, TCMR::DEF_DELIVERY_DATE,
                      TCMR::DEF_PRICE_LITER, TCMR::DEF_LITERS, TCMR::DEF_FAT)
{

}

MilkReceptionData::MilkReceptionData(const MILK_ID id, const MILK_ID delivererId,
                                     const MILK_ID milkPointId, const QDate &deliveryDate,
                                     const double priceLiter, const double liters, const double fat):
    m_milkId(id),
    m_delivererId(delivererId),
    m_milkPointId(milkPointId),
    m_deliveryDate(deliveryDate),
    m_priceLiter(priceLiter),
    m_liters(liters),
    m_fat(fat)
{

}

MilkReceptionData::MilkReceptionData(const MilkReceptionData &data):
    QSharedData(data),
    m_milkId(data.milkId()),
    m_delivererId(data.delivererId()),
    m_milkPointId(data.milkPointId()),
    m_deliveryDate(data.deliveryDate()),
    m_priceLiter(data.priceLiter()),
    m_liters(data.liters()),
    m_fat(data.fat())
{

}

void MilkReceptionData::setMilkId(const MILK_ID milkId)
{
    m_milkId = milkId;
}

void MilkReceptionData::setDelivererId(const MILK_ID delivererId)
{
    m_delivererId = delivererId;
}

void MilkReceptionData::setMilkPointId(const MILK_ID milkPointId)
{
    m_milkPointId = milkPointId;
}

void MilkReceptionData::setDeliveryDate(const QDate &deliveryDate)
{
    m_deliveryDate = deliveryDate;
}

void MilkReceptionData::setPriceLiter(double priceLiter)
{
    m_priceLiter = priceLiter;
}

void MilkReceptionData::setLiters(double liters)
{
    m_liters = liters;
}

void MilkReceptionData::setFat(double fat)
{
    m_fat = fat;
}

bool MilkReceptionData::isValid() const
{
    return MilkBaseItem::isValid() && m_delivererId > TC::DEFAULT_ID &&
            m_milkPointId > TC::DEFAULT_ID && m_liters > TCMR::DEF_LITERS &&
            m_fat > TCMR::DEF_FAT && m_priceLiter > TCMR::DEF_PRICE_LITER;
}

void MilkReceptionData::reset()
{
    MilkBaseItem::reset();
    m_delivererId = TC::DEFAULT_ID;
    m_milkPointId = TC::DEFAULT_ID;
    m_deliveryDate = TCMR::DEF_DELIVERY_DATE;
    m_priceLiter = TCMR::DEF_PRICE_LITER;
    m_liters = TCMR::DEF_LITERS;
    m_fat = TCMR::DEF_FAT;

}
