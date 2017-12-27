#include "MilkPoint.h"

#include <Locality.h>
#include "TypesConstants.h"

using TC = TypesConstants;


MilkPoint::MilkPoint()
{
    m_data = new MilkPointData();
    m_locality = Q_NULLPTR;
}

MilkPoint::MilkPoint(const MILK_ID id, const QString &name, const QString &description,
                     const Locality *locality):
    m_locality(locality)
{
    m_data = new MilkPointData(id, m_locality ? m_locality->milkId() : TC::DEFAULT_ID, name, description);
}

MilkPoint::MilkPoint(const MilkPoint &other):
    m_data(other.m_data),
    m_locality(other.m_locality)
{

}

void MilkPoint::setMilkId(const MILK_ID milkId)
{
    m_data->setMilkId(milkId);
}

void MilkPoint::setLocality(const Locality *locality)
{
    m_locality = locality;
    m_data->setLocalityId(m_locality ? m_locality->milkId() : TC::DEFAULT_ID);
}

void MilkPoint::setName(const QString &name)
{
    m_data->setName(name);
}

void MilkPoint::setDescription(const QString &description)
{
    m_data->setDescription(description);
}

bool MilkPoint::isValid() const
{
    return m_data->isValid();
}

void MilkPoint::reset()
{
    m_data->reset();
}
