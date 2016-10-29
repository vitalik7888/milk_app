#include "Locality.h"

USE_DB_NAMESPACE


Locality::Locality():
    Locality(-1, "", "")
{

}

Locality::Locality(const milk_id id, const QString &name, const QString &description):
    m_id(id),
    m_name(name),
    m_description(description)
{

}

milk_id Locality::id() const
{
    return m_id;
}

void Locality::setId(const milk_id &id)
{
    m_id = id;
}

QString Locality::name() const
{
    return m_name;
}

void Locality::setName(const QString &name)
{
    m_name = name;
}

QString Locality::description() const
{
    return m_description;
}

void Locality::setDescription(const QString &description)
{
    m_description = description;
}

bool Locality::isValid() const
{
    return m_id > 0;
}
