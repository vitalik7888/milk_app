#include "Deliverer.h"

#include <Locality.h>
#include "TypesConstants.h"

using TC = TypesConstants;


Deliverer::Deliverer():
    m_locality(Q_NULLPTR)
{
    m_data = new DelivererData();
}

Deliverer::Deliverer(const Deliverer &other):
    m_data(other.m_data),
    m_locality(other.locality())
{

}

Deliverer::Deliverer(const MILK_ID id, const QString &firstName, const QString &lastName,
                     const QString &inn, const QString &address,
                     const QString &phoneNumber, const Locality *locality):
    m_locality(locality)
{
    m_data = new DelivererData(id, firstName, lastName, m_locality ? m_locality->milkId() : TC::DEFAULT_ID,
                               inn, address, phoneNumber);
}

void Deliverer::setMilkId(const MILK_ID id)
{
    m_data->setMilkId(id);
}

void Deliverer::setFirstName(const QString &firstName)
{
    m_data->setFirstName(firstName);
}

void Deliverer::setLastName(const QString &lastName)
{
    m_data->setLastName(lastName);
}

void Deliverer::setInn(const QString &inn)
{
    m_data->setInn(inn);
}

void Deliverer::setLocality(const Locality *locality)
{
    m_locality = locality;
    m_data->setLocalityId(m_locality ? m_locality->milkId() : TC::DEFAULT_ID);
}

void Deliverer::setAddress(const QString &address)
{
    m_data->setAddress(address);
}

void Deliverer::setPhoneNumber(const QString &phoneNumber)
{
    m_data->setPhoneNumber(phoneNumber);
}

bool Deliverer::isValid() const { return m_data->isValid(); }

void Deliverer::reset() { m_data->reset(); }


