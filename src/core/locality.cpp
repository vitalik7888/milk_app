#include "locality.h"

USE_DB_NAMESPACE


Locality::Locality(QObject *parent):
    Locality({}, parent)
{

}

Locality::Locality(const LocalityData &data, QObject *parent):
    QObject(parent),
    m_data(data)
{

}

Locality::~Locality()
{

}

milk_id Locality::id() const
{
    return m_data.id();
}

QString Locality::name() const
{
    return m_data.name();
}

QString Locality::description() const
{
    return m_data.description();
}

LocalityData Locality::data() const
{
    return m_data;
}

void Locality::setId(const milk_id &id)
{
    if (id == m_data.id())
        return;

    m_data.setId(id);
    emit idChanged(id);
}

void Locality::setName(const QString &name)
{
    if (m_data.name() == name)
        return;

    m_data.setName(name);
    emit nameChanged(name);
}

void Locality::setDescription(const QString &description)
{
    if (m_data.description() == description)
        return;

    m_data.setDescription(description);
    emit descriptionChanged(description);
}