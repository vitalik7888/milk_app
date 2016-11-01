#include "deliverer.h"

#include "locality.h"



Deliverer::Deliverer():
    m_data()
{

}

Deliverer::Deliverer(const milk_id id, const QString &name, const milk_inn inn, const QString &address,
                     const QString &phoneNumber, const QWeakPointer<Locality> &locality):
    m_data(id, name, locality.isNull() ? -1 : locality.data()->id(), inn, address, phoneNumber),
    m_locality(locality)
{

}

Deliverer::Deliverer(const Deliverer &deliverer):
    m_data(deliverer.data()),
    m_locality(deliverer.locality())
{

}

Deliverer::~Deliverer()
{

}

milk_id Deliverer::id() const
{
    return m_data.id();
}

void Deliverer::setId(const milk_id &id)
{
    m_data.setId(id);
}

QWeakPointer<Locality> Deliverer::locality() const
{
    return m_locality;
}

QString Deliverer::name() const
{
    return m_data.name();
}

void Deliverer::setName(const QString &name)
{
    m_data.setName(name);
}

milk_inn Deliverer::inn() const
{
    return m_data.inn();
}

void Deliverer::setInn(const milk_inn &inn)
{
    m_data.setInn(inn);
}

QString Deliverer::address() const
{
    return m_data.address();
}

void Deliverer::setAddress(const QString &address)
{
    m_data.setAddress(address);
}

QString Deliverer::phoneNumber() const
{
    return m_data.phoneNumber();
}

void Deliverer::setPhoneNumber(const QString &phoneNumber)
{
    m_data.setPhoneNumber(phoneNumber);
}

bool Deliverer::isValid() const
{
    return m_data.isValid();
}

DB_NAMESPACE::DelivererData Deliverer::data() const
{
    return m_data;
}

void Deliverer::setLocality(const QWeakPointer<Locality> &locality)
{
    m_locality = locality;
    m_data.setId(locality.isNull() ? -1 : locality.data()->id());
}
