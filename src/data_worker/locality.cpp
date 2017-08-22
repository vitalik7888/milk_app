#include "locality.h"

USE_DB_NAMESPACE;


Locality::Locality(QObject *parent):
    Locality(-1, QString(), QString(), parent)
{

}

Locality::Locality(const milk_id id, const QString &name,
                   const QString &description, QObject *parent):
    QObject(parent),
    m_data(id, name, description)
{

}

Locality::~Locality()
{

}

milk_id Locality::id() const
{
    return m_data.id();
}

void Locality::setId(const milk_id &id)
{
    m_data.setId(id);
}

QString Locality::name() const
{
    return m_data.name();
}

void Locality::setName(const QString &name)
{
    m_data.setName(name);
}

QString Locality::description() const
{
    return m_data.description();
}

void Locality::setDescription(const QString &description)
{
    m_data.setDescription(description);
}

LocalityData Locality::data() const
{
    return m_data;
}
