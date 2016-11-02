#include "deliverer.h"

#include "locality.h"
#include "milkreception.h"
#include "Utils.h"


Deliverer::Deliverer():
    Deliverer(-1, QString(), -1, QString(), QString(), WpLocality())
{

}

Deliverer::Deliverer(const milk_id id, const QString &name, const milk_inn inn, const QString &address,
                     const QString &phoneNumber, const WpLocality &locality):
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

WpLocality Deliverer::locality() const
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

bool Deliverer::isHasMilkReceptions() const
{
    return !m_milkReceptions.empty();
}

DelivererMilkReceptions Deliverer::milkReceptions() const
{
    return m_milkReceptions;
}

void Deliverer::addMilkReception(const WpMilkRecep &milkReception)
{
    m_milkReceptions.append(milkReception);
}

CalculatedItem::Data Deliverer::getCalculations() const
{
    CalculatedItem::Data data;

    for (const auto &mr: m_milkReceptions) {
        const auto right = mr.data()->getCalculations().data();
        data += right;
    }

    return data;
}

void Deliverer::setLocality(const WpLocality &locality)
{
    m_locality = locality;
    m_data.setId(locality.isNull() ? -1 : locality.data()->id());
}

bool Deliverer::isValid() const
{
    return m_data.isValid();
}

DB_NAMESPACE::DelivererData Deliverer::data() const
{
    return m_data;
}
