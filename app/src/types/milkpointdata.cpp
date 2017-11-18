#include "milkpointdata.h"


MilkPointData::MilkPointData():
    MilkPointData(-1, -1, "", "")
{

}

MilkPointData::MilkPointData(const TypesConstants::milk_id id, const TypesConstants::milk_id localityId, const QString &name,
                             const QString &description):
    m_id(id),
    m_localityId(localityId),
    m_name(name),
    m_description(description)
{

}

TypesConstants::milk_id MilkPointData::id() const
{
    return m_id;
}

void MilkPointData::setId(const TypesConstants::milk_id &id)
{
    m_id = id;
}

TypesConstants::milk_id MilkPointData::localityId() const
{
    return m_localityId;
}

void MilkPointData::setLocalityId(const TypesConstants::milk_id &localityId)
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
