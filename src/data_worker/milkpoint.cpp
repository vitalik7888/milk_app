#include "milkpoint.h"

#include "locality.h"


MilkPoint::MilkPoint():
    MilkPoint(-1, Q_NULLPTR, QString(), QString())
{

}

MilkPoint::MilkPoint(const milk_id id, Locality *locality, const QString &name,
                     const QString &description):
    m_data(id, locality->id(), name, description),
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

Locality *MilkPoint::locality() const
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

DB_NAMESPACE::MilkPointData MilkPoint::data() const
{
    return m_data;
}

void MilkPoint::setLocality(Locality *locality)
{
    m_locality = locality;
    m_data.setLocalityId(m_locality->id());
}
