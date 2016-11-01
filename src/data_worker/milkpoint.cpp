#include "milkpoint.h"

#include "locality.h"


MilkPoint::MilkPoint():
    MilkPoint(-1, QString(), QString(), QWeakPointer<Locality>())
{

}

MilkPoint::MilkPoint(const milk_id id, const QString &name, const QString &description,
                     const QWeakPointer<Locality> &locality):
    m_data(id, locality.isNull() ? -1 : locality.data()->id(), name, description),
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

QWeakPointer<Locality> MilkPoint::locality() const
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

void MilkPoint::setLocality(const QWeakPointer<Locality> &locality)
{
    m_locality = locality;
    m_data.setLocalityId(locality.isNull() ? -1 : locality.data()->id());
}
