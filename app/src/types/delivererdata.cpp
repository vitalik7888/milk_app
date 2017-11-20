#include "delivererdata.h"

// Qt
#include <QtDebug>

using TC = TypesConstants;
using TCD = TC::Deliverers;


DelivererData::DelivererData():
    DelivererData(TCD::DEF_ID, TCD::DEF_NAME, TCD::DEF_LOCALITY_ID,
                  TCD::DEF_INN, TCD::DEF_ADDRESS, TCD::DEF_PHONE_NUMBER)
{

}

DelivererData::DelivererData(const DelivererData &data):
    m_id(data.id()),
    m_localityId(data.localityId()),
    m_inn(data.inn()),
    m_name(data.name()),
    m_address(data.address()),
    m_phoneNumber(data.phoneNumber())
{

}

DelivererData::DelivererData(const TC::milk_id id, const QString &name, const TC::milk_id localityId,
                             const TC::milk_inn inn, const QString &address, const QString &phoneNumber):
    m_id(id),
    m_localityId(localityId),
    m_inn(inn),
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

TC::milk_inn DelivererData::inn() const
{
    return m_inn;
}

void DelivererData::setInn(const TC::milk_inn inn)
{
    m_inn = inn;
}

TC::milk_id DelivererData::id() const
{
    return m_id;
}

void DelivererData::setId(const TC::milk_id &id)
{
    m_id = id;
}

TC::milk_id DelivererData::localityId() const
{
    return m_localityId;
}

void DelivererData::setLocalityId(const TC::milk_id &localityId)
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
