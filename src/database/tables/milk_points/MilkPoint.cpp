#include "MilkPoint.h"


MilkPoint::MilkPoint():
    _id(-1),
    _locality(Locality()),
    _name(QString()),
    _description(QString())
{

}

MilkPoint::MilkPoint(const Locality &locality, const QString &name,
                     const QString &description, const qlonglong id):
    _id(id),
    _locality(locality),
    _name(name),
    _description(description)
{

}

qlonglong MilkPoint::id() const
{
    return _id;
}

void MilkPoint::setId(const qlonglong &id)
{
    _id = id;
}

Locality MilkPoint::locality() const
{
    return _locality;
}

QString MilkPoint::name() const
{
    return _name;
}

void MilkPoint::setName(const QString &name)
{
    _name = name;
}

QString MilkPoint::description() const
{
    return _description;
}

void MilkPoint::setDescription(const QString &description)
{
    _description = description;
}

bool MilkPoint::isNull() const
{
    return _id < 0;
}

QString MilkPoint::toString() const
{
    return QString::fromUtf8("Молочный пункт %1(id %2): %3, описание = %4")
            .arg(_name).arg(_locality.toString()).arg(_id).arg(_description);
}

MilkPoint MilkPoint::CREATE_NULL()
{
    return MilkPoint(Locality::CREATE_NULL(), "", "", -1);
}
