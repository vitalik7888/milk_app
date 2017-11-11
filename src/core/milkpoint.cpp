#include "milkpoint.h"

#include "locality.h"


MilkPoint::MilkPoint(const db::MilkPointData &data, Locality *locality, QObject *parent):
    QObject(parent),
    m_data(data),
    m_locality(locality)
{

}

MilkPoint::MilkPoint(const milk_id id, const QString &name, const QString &description,
                     Locality *locality, QObject *parent):
    MilkPoint({id, locality == Q_NULLPTR ? -1 : locality->id(), name, description}, locality, parent)
{
}

MilkPoint::MilkPoint(QObject *parent):
    MilkPoint(-1, QString(), QString(), Q_NULLPTR, parent) {

}

MilkPoint::~MilkPoint() {

}

milk_id MilkPoint::id() const
{
    return m_data.id();
}

Locality *MilkPoint::locality() const
{
    return m_locality;
}

QString MilkPoint::name() const
{
    return m_data.name();
}

QString MilkPoint::description() const
{
    return m_data.description();
}

DB_NAMESPACE::MilkPointData MilkPoint::data() const
{
    return m_data;
}

void MilkPoint::setId(const milk_id &id)
{
    if (id == m_data.id())
        return;

    m_data.setId(id);
    emit idChanged(id);
}

void MilkPoint::setName(const QString &name)
{
    if (m_data.name() == name)
        return;

    m_data.setName(name);
    emit nameChanged(name);
}

void MilkPoint::setDescription(const QString &description)
{
    if (m_data.description() == description)
        return;

    m_data.setDescription(description);
    emit descriptionChanged(description);
}

bool MilkPoint::isValid() const
{
    return m_data.isValid();
}

void MilkPoint::setLocality(Locality *locality)
{
    if (m_locality == locality)
        return;

    m_locality = locality;
    m_data.setLocalityId(locality->id());
    emit localityChanged(m_locality);
}

