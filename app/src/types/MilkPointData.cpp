#include "MilkPointData.h"

#include "TypesConstants.h"

using TC = TypesConstants;
using TCMP = TC::MilkPoints;


MilkPointData::MilkPointData():
    MilkPointData(TCMP::DEF_ID, TCMP::DEF_LOCALITY_ID, TCMP::DEF_NAME, TCMP::DEF_DESCRIPTION)
{

}

MilkPointData::MilkPointData(const MilkPointData &mp):
    m_id(mp.id()),
    m_localityId(mp.localityId()),
    m_name(mp.name()),
    m_description(mp.description())
{

}

MilkPointData::MilkPointData(const int id, const int localityId, const QString &name,
                             const QString &description):
    m_id(id),
    m_localityId(localityId),
    m_name(name),
    m_description(description)
{

}

MilkPointData &MilkPointData::operator =(const MilkPointData &data)
{
    if (&data != this) {
        m_id = data.id();
        m_localityId = data.localityId();
        m_name = data.name();
        m_description = data.description();
    }

    return *this;
}

int MilkPointData::id() const
{
    return m_id;
}

void MilkPointData::setId(const int id)
{
    m_id = id;
}

int MilkPointData::localityId() const
{
    return m_localityId;
}

void MilkPointData::setLocalityId(const int localityId)
{
    m_localityId = localityId;
}

QString MilkPointData::name() const
{
    return m_name;
}

void MilkPointData::setName(const QString &name)
{
    m_name = name;
}

QString MilkPointData::description() const
{
    return m_description;
}

void MilkPointData::setDescription(const QString &description)
{
    m_description = description;
}

bool MilkPointData::isValid() const
{
    return m_id > 0;
}
