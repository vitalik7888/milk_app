#include "deliverer.h"

#include "locality.h"
#include "milkreception.h"


Deliverer::Deliverer(QObject *parent):
    Deliverer(-1, QString(), -1, QString(), QString(), Q_NULLPTR, parent)
{

}

Deliverer::Deliverer(const TypesConstants::milk_id id, const QString &name, const TypesConstants::milk_inn inn,
                     const QString &address, const QString &phoneNumber,
                     Locality *locality, QObject *parent):
    QObject(parent),
    m_data(id, name, locality == Q_NULLPTR ? -1 : locality->id(), inn, address, phoneNumber),
    m_locality(locality)
{

}

Deliverer::~Deliverer()
{

}

TypesConstants::milk_id Deliverer::id() const
{
    return m_data.id();
}

Locality *Deliverer::locality() const
{
    return m_locality;
}

QString Deliverer::name() const
{
    return m_data.name();
}

TypesConstants::milk_inn Deliverer::inn() const
{
    return m_data.inn();
}

QString Deliverer::address() const
{
    return m_data.address();
}

QString Deliverer::phoneNumber() const
{
    return m_data.phoneNumber();
}

void Deliverer::setId(const TypesConstants::milk_id &id)
{
    if (id == m_data.id())
        return;

    m_data.setId(id);
    emit idChanged(m_data.id());
}

void Deliverer::setName(const QString &name)
{
    if (m_data.name() == name)
        return;

    m_data.setName(name);
    emit nameChanged(name);
}

void Deliverer::setInn(const TypesConstants::milk_inn &inn)
{
    if (m_data.inn() == inn)
        return;

    m_data.setInn(inn);
    emit innChanged(inn);
}

void Deliverer::setAddress(const QString &address)
{
    if (m_data.address() == address)
        return;

    m_data.setAddress(address);
    emit addressChanged(address);
}

void Deliverer::setLocality(Locality *locality)
{
    if (m_locality == locality)
        return;

    m_locality = locality;
    m_data.setId(locality == Q_NULLPTR ? -1 : locality->id());
    emit localityChanged(locality);
}

void Deliverer::setPhoneNumber(const QString &phoneNumber)
{
    if (m_data.phoneNumber() == phoneNumber)
        return;

    m_data.setPhoneNumber(phoneNumber);
    emit phoneNumberChanged(phoneNumber);
}

void Deliverer::reset()
{
    m_data = {};
    m_locality = Q_NULLPTR;
    m_milkReceptions.clear();
}

bool Deliverer::isHasMilkReceptions() const
{
    return !m_milkReceptions.empty();
}


bool Deliverer::isValid() const
{
    return m_data.isValid();
}

DelivererData Deliverer::data() const
{
    return m_data;
}

QQmlListProperty<MilkReception> Deliverer::milkReceptions()
{
    return QQmlListProperty<MilkReception>(this, this,
                                           &Deliverer::appendMilkReception,
                                           &Deliverer::milkReceprionsCount,
                                           &Deliverer::milkReception,
                                           &Deliverer::clearMilkReceptions);
}

int Deliverer::milkReceprionsCount() const
{
    return m_milkReceptions.count();
}

MilkReception *Deliverer::milkReception(int pos) const
{
    return m_milkReceptions.at(pos);
}

void Deliverer::clearMilkReceptions()
{
    m_milkReceptions.clear();
}

void Deliverer::appendMilkReception(MilkReception *milkReception)
{
    m_milkReceptions.append(milkReception);
}

void Deliverer::appendMilkReception(QQmlListProperty<MilkReception> *list, MilkReception *mr)
{
    reinterpret_cast< Deliverer* >(list->data)->appendMilkReception(mr);
}

int Deliverer::milkReceprionsCount(QQmlListProperty<MilkReception> *list)
{
    return reinterpret_cast< Deliverer* >(list->data)->milkReceprionsCount();
}

MilkReception *Deliverer::milkReception(QQmlListProperty<MilkReception> *list, int pos)
{
    return reinterpret_cast< Deliverer* >(list->data)->milkReception(pos);
}

void Deliverer::clearMilkReceptions(QQmlListProperty<MilkReception> *list)
{
    reinterpret_cast< Deliverer* >(list->data)->clearMilkReceptions();
}
