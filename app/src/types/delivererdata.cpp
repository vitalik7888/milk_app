#include "delivererdata.h"

// Qt
#include <QtDebug>


DelivererData::DelivererData():
    DelivererData(-1, "", -1, 0, "", "")
{

}

DelivererData::DelivererData(const TypesConstants::milk_id id, const QString &name, const TypesConstants::milk_id localityId,
                             const TypesConstants::milk_inn inn, const QString &address, const QString &phoneNumber):
    m_inn(inn),
    m_id(id),
    m_localityId(localityId),
    m_name(name),
    m_address(address),
    m_phoneNumber(phoneNumber)
{

}

DelivererData::~DelivererData()
{

}

bool DelivererData::isValid() const
{
    return m_id > 0;
}

TypesConstants::milk_inn DelivererData::inn() const
{
    return m_inn;
}

void DelivererData::setInn(const TypesConstants::milk_inn inn)
{
    m_inn = inn;
}

TypesConstants::milk_id DelivererData::id() const
{
    return m_id;
}

void DelivererData::setId(const TypesConstants::milk_id &id)
{
    m_id = id;
}

TypesConstants::milk_id DelivererData::localityId() const
{
    return m_localityId;
}

void DelivererData::setLocalityId(const TypesConstants::milk_id &localityId)
{
    m_localityId = localityId;
}

QString DelivererData::name() const
{
    return m_name;
}

void DelivererData::setName(const QString &name)
{
    m_name = name;
}

QString DelivererData::address() const
{
    return m_address;
}

void DelivererData::setAddress(const QString &address)
{
    m_address = address;
}

QString DelivererData::phoneNumber() const
{
    return m_phoneNumber;
}

void DelivererData::setPhoneNumber(const QString &phoneNumber)
{
    m_phoneNumber = phoneNumber;
}

QDebug operator<<(QDebug dbg, const DelivererData &data)
{
    dbg << "DelivererData(" << data.id() << ")"
        << "name:" << data.name()
        << "address:" << data.address()
        << "phone number:" << data.phoneNumber()
        << "locality id:" << data.localityId()
        << "inn:" << data.inn();

    return dbg;
}
