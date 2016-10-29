#include "milkpointdata.h"

USE_DB_NAMESPACE


MilkPointData::MilkPointData():
    MilkPointData(-1, -1, "", "")
{

}

MilkPointData::MilkPointData(const milk_id id, const milk_id localityId, const QString &name,
                             const QString &description):
    m_id(id),
    m_localityId(localityId),
    m_name(name),
    m_description(description)
{

}

MilkPointData::MilkPointData(const MilkPointData &data):
    m_id(data.id()),
    m_localityId(data.localityId()),
    m_name(data.name()),
    m_description(data.description())
{

}

milk_id MilkPointData::id() const
{
    return m_id;
}

void MilkPointData::setId(const milk_id &id)
{
    m_id = id;
}

milk_id MilkPointData::localityId() const
{
    return m_localityId;
}

void MilkPointData::setLocalityId(const milk_id &localityId)
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
