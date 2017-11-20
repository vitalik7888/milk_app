#include "milkpointdata.h"

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

MilkPointData::MilkPointData(const TC::milk_id id, const TC::milk_id localityId, const QString &name,
                             const QString &description):
    m_id(id),
    m_localityId(localityId),
    m_name(name),
    m_description(description)
{

}

TC::milk_id MilkPointData::id() const
{
    return m_id;
}

void MilkPointData::setId(const TC::milk_id &id)
{
    m_id = id;
}

TC::milk_id MilkPointData::localityId() const
{
    return m_localityId;
}

void MilkPointData::setLocalityId(const TC::milk_id &localityId)
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
