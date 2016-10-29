#include "delivererdata.h"

// Qt
#include <QtDebug>

USE_DB_NAMESPACE


DelivererData::DelivererData():
    DelivererData(-1, "", -1, 0, "", "")
{

}

DelivererData::DelivererData(const milk_id id, const QString &name, const milk_id localityId,
                             const milk_inn inn, const QString &address, const QString &phoneNumber):
    m_inn(inn),
    m_id(id),
    m_localityId(localityId),
    m_name(name),
    m_address(address),
    m_phoneNumber(phoneNumber)
{

}

DelivererData::DelivererData(const DelivererData &data):
    m_inn(data.inn()),
    m_id(data.id()),
    m_localityId(data.localityId()),
    m_name(data.name()),
    m_address(data.address()),
    m_phoneNumber(data.phoneNumber())
{

}

DelivererData::~DelivererData()
{

}

bool DelivererData::isValid() const
{
    return m_id > 0;
}

milk_inn DelivererData::inn() const
{
    return m_inn;
}

void DelivererData::setInn(const milk_inn inn)
{
    m_inn = inn;
}

milk_id DelivererData::id() const
{
    return m_id;
}

void DelivererData::setId(const milk_id &id)
{
    m_id = id;
}

milk_id DelivererData::localityId() const
{
    return m_localityId;
}

void DelivererData::setLocalityId(const milk_id &localityId)
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
