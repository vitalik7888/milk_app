#include "Deliverer.h"


Deliverer::Deliverer():
    _id(-1),
    _name(QString()),
    _locality(Locality()),
    _inn(0),
    _address(QString()),
    _phoneNumber(QString())
{

}

Deliverer::Deliverer(const QString &name, const Locality &locality, const qlonglong inn, const QString &address, const QString &phoneNumber, const qlonglong id):
    _id(id),
    _name(name),
    _locality(locality),
    _inn(inn),
    _address(address),
    _phoneNumber(phoneNumber)
{
}

qlonglong Deliverer::id() const
{
    return _id;
}

void Deliverer::setId(const qlonglong &id)
{
    _id = id;
}

Locality Deliverer::locality() const
{
    return _locality;
}

QString Deliverer::name() const
{
    return _name;
}

void Deliverer::setName(const QString &name)
{
    _name = name;
}

qlonglong Deliverer::inn() const
{
    return _inn;
}

void Deliverer::setInn(const qlonglong &inn)
{
    _inn = inn;
}

QString Deliverer::address() const
{
    return _address;
}

void Deliverer::setAddress(const QString &address)
{
    _address = address;
}

QString Deliverer::phoneNumber() const
{
    return _phoneNumber;
}

void Deliverer::setPhoneNumber(const QString &phoneNumber)
{
    _phoneNumber = phoneNumber;
}

bool Deliverer::isNull() const
{
    return _id < 0;
}

QString Deliverer::toString() const
{
    return QString::fromUtf8("Сдатчик %1(id %2): %3, inn = %4, "
                             "address = %5, phoneNumber = %6")
            .arg(_name).arg(_id).arg(_locality.toString()).arg(_inn)
            .arg(_address).arg(_phoneNumber);
}

Deliverer Deliverer::CREATE_NULL()
{
    return Deliverer();
}
