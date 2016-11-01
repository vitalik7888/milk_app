#include "MilkPoint.h"

USE_DB_NAMESPACE


MilkPoint::MilkPoint():
    MilkPoint(-1, LocalityData(), "", "")
{

}

MilkPoint::MilkPoint(const milk_id id, const LocalityData &locality, const QString &name,
                     const QString &description):
    m_data(id, locality.id(), name, description),
    m_locality(locality)
{

}

MilkPoint::MilkPoint(const MilkPoint &milkPoint):
    m_data(milkPoint.data()),
    m_locality(milkPoint.locality())
{

}

MilkPoint::~MilkPoint()
{

}

milk_id MilkPoint::id() const
{
    return m_data.id();
}

void MilkPoint::setId(const milk_id &id)
{
    m_data.setId(id);
}

LocalityData MilkPoint::locality() const
{
    return m_locality;
}

QString MilkPoint::name() const
{
    return m_data.name();
}

void MilkPoint::setName(const QString &name)
{
    m_data.setName(name);
}

QString MilkPoint::description() const
{
    return m_data.description();
}

void MilkPoint::setDescription(const QString &description)
{
    m_data.setDescription(description);
}

bool MilkPoint::isValid() const
{
    return m_data.isValid();
}

MilkPointData MilkPoint::data() const
{
    return m_data;
}

void MilkPoint::setLocality(const LocalityData &locality)
{
    m_locality = locality;
    m_data.setLocalityId(m_locality.id());
}
