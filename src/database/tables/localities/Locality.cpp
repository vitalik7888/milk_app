#include "Locality.h"



Locality::Locality():
    _id(-1),
    _name(QString()),
    _description(QString())
{

}

Locality::Locality(const QString &name, const QString &description, const qlonglong id):
    _id(id),
    _name(name),
    _description(description)
{

}

qlonglong Locality::id() const
{
    return _id;
}

void Locality::setId(const qlonglong &id)
{
    _id = id;
}

QString Locality::name() const
{
    return _name;
}

void Locality::setName(const QString &name)
{
    _name = name;
}

QString Locality::description() const
{
    return _description;
}

void Locality::setDescription(const QString &description)
{
    _description = description;
}

bool Locality::isNull() const
{
    return _id < 0;
}

QString Locality::toString() const
{
    return QString::fromUtf8("%1(id %2): описание = %3;")
            .arg(_name).arg(_id).arg(_description);
}

Locality Locality::CREATE_NULL()
{
    return Locality();
}
