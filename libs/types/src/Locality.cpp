#include "Locality.h"


Locality::Locality()
{
    m_data = new LocalityData();
}

Locality::Locality(const MILK_ID id, const QString &name, const QString &description)
{
    m_data = new LocalityData(id, name, description);
}

Locality::Locality(const Locality &other):
    m_data(other.m_data)
{

}

void Locality::setMilkId(const MILK_ID id)
{
    m_data->setMilkId(id);
}

void Locality::setName(const QString &name)
{
    m_data->setName(name);
}

void Locality::setDescription(const QString &description)
{
    m_data->setDescription(description);
}
