#include "DelivererData.h"

#include "TypesConstants.h"
// Qt
#include <QtDebug>

using TC = TypesConstants;


DelivererData::DelivererData():
    DelivererData(TC::DEFAULT_ID, TC::Deliverers::DEF_FIRST_NAME, TC::Deliverers::DEF_LAST_NAME,
                  TC::DEFAULT_ID, TC::Deliverers::DEF_INN,
                  TC::Deliverers::DEF_ADDRESS, TC::Deliverers::DEF_PHONE_NUMBER)
{

}

DelivererData::DelivererData(const DelivererData &other):
    QSharedData(other),
    m_milkId(other.milkId()),
    m_localityId(other.localityId()),
    m_inn(other.inn()),
    m_firstName(other.firstName()),
    m_lastName(other.lastName()),
    m_address(other.address()),
    m_phoneNumber(other.phoneNumber())
{

}

DelivererData::DelivererData(const MILK_ID id, const QString &firstName, const QString &lastName,
                             const MILK_ID localityId, const QString &inn, const QString &address,
                             const QString &phoneNumber):
    m_milkId(id),
    m_localityId(localityId),
    m_inn(inn),
    m_firstName(firstName),
    m_lastName(lastName),
    m_address(address),
    m_phoneNumber(phoneNumber)
{

}

bool DelivererData::isValid() const
{
    return MilkBaseItem::isValid() && m_localityId > 0;
}

void DelivererData::reset()
{
    MilkBaseItem::reset();
    m_localityId = TC::DEFAULT_ID;
    m_inn = TC::Deliverers::DEF_INN;
    m_firstName = TC::Deliverers::DEF_FIRST_NAME;
    m_lastName = TC::Deliverers::DEF_LAST_NAME;
    m_address = TC::Deliverers::DEF_ADDRESS;
    m_phoneNumber = TC::Deliverers::DEF_PHONE_NUMBER;
}

void DelivererData::setInn(const QString &inn)
{
    m_inn = inn;
}

void DelivererData::setMilkId(const MILK_ID id)
{
    m_milkId = id;
}

void DelivererData::setLocalityId(const MILK_ID localityId)
{
    m_localityId = localityId;
}

void DelivererData::setAddress(const QString &address)
{
    m_address = address;
}

void DelivererData::setPhoneNumber(const QString &phoneNumber)
{
    m_phoneNumber = phoneNumber;
}

void DelivererData::setFirstName(const QString &firstName)
{
    m_firstName = firstName;
}

void DelivererData::setLastName(const QString &lastName)
{
    m_lastName = lastName;
}

QString DelivererData::fullName() const
{
    QString firstName = m_firstName.trimmed(), lastName;
    if (firstName.length() == 1)
        firstName.append('.');
    lastName = firstName.isEmpty() ? m_lastName.trimmed() : " " + m_lastName.trimmed();

    return firstName + lastName;
}

QDebug operator<<(QDebug dbg, const DelivererData &data)
{
    dbg << "DelivererData(" << data.milkId() << ")"
        << "first name:" << data.firstName()
        << "last name:" << data.lastName()
        << "address:" << data.address()
        << "phone number:" << data.phoneNumber()
        << "locality id:" << data.localityId()
        << "inn:" << data.inn();

    return dbg;
}
