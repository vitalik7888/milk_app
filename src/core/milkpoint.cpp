#include "milkpoint.h"

#include "locality.h"


MilkPoint::MilkPoint(const db::MilkPointData &data, Locality *locality, QObject *parent):
    QObject(parent),
    m_data(data),
    m_locality(locality)
{

}

MilkPoint::MilkPoint(const milk_id id, const QString &name, const QString &description,
                     Locality *locality, QObject *parent):
    MilkPoint({id, locality == Q_NULLPTR ? -1 : locality->id(), name, description}, locality, parent)
{
}

MilkPoint::MilkPoint(QObject *parent):
    MilkPoint(-1, QString(), QString(), Q_NULLPTR, parent)
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
    m_data.setLocalityId(locality->id());
}
