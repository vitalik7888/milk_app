#include "milkpoint.h"

#include "locality.h"
#include "TypesConstants.h"

using TC = TypesConstants;
using TCMP = TC::MilkPoints;


MilkPoint::MilkPoint(const TC::milk_id id, const QString &name, const QString &description,
                     Locality *locality, QObject *parent):
    QObject(parent),
    m_data{id, locality == Q_NULLPTR ? TCMP::DEF_LOCALITY_ID : locality->id(), name, description},
    m_locality(locality)
{
}

MilkPoint::MilkPoint(QObject *parent):
    MilkPoint(TCMP::DEF_ID, TCMP::DEF_NAME, TCMP::DEF_DESCRIPTION, Q_NULLPTR, parent) {

}

MilkPoint::~MilkPoint() {

}

TC::milk_id MilkPoint::id() const
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

MilkPointData MilkPoint::data() const
{
    return m_data;
}

void MilkPoint::setId(const TC::milk_id &id)
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

void MilkPoint::reset()
{
    m_data = {};
    m_locality = Q_NULLPTR;
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
    m_data.setLocalityId(locality == Q_NULLPTR ? TCMP::DEF_LOCALITY_ID : locality->id());
    emit localityChanged(m_locality);
}

