#include "MilkPointData.h"

#include "TypesConstants.h"

using TC = TypesConstants;


MilkPointData::MilkPointData():
    MilkPointData(TC::DEFAULT_ID, TC::DEFAULT_ID, TC::MilkPoints::DEF_NAME, TC::MilkPoints::DEF_DESCRIPTION)
{

}

MilkPointData::MilkPointData(const MilkPointData &mp):
    QSharedData(mp),
    m_milkId(mp.milkId()),
    m_localityId(mp.localityId()),
    m_name(mp.name()),
    m_description(mp.description())
{

}

MilkPointData::MilkPointData(const MILK_ID id, const MILK_ID localityId, const QString &name,
                             const QString &description):
    m_milkId(id),
    m_localityId(localityId),
    m_name(name),
    m_description(description)
{

}

MilkPointData &MilkPointData::operator =(const MilkPointData &data)
{
    if (&data != this) {
        m_milkId = data.milkId();
        m_localityId = data.localityId();
        m_name = data.name();
        m_description = data.description();
    }

    return *this;
}

void MilkPointData::setMilkId(const MILK_ID milkId)
{
    m_milkId = milkId;
}

void MilkPointData::setLocalityId(const MILK_ID localityId)
{
    m_localityId = localityId;
}

void MilkPointData::setName(const QString &name)
{
    m_name = name;
}

void MilkPointData::setDescription(const QString &description)
{
    m_description = description;
}

bool MilkPointData::isValid() const
{
    return MilkBaseItem::isValid() && m_localityId > 0 && !m_name.isEmpty();
}

void MilkPointData::reset()
{
    MilkBaseItem::reset();
    m_localityId = TC::DEFAULT_ID;
    m_name = TC::MilkPoints::DEF_NAME;
    m_description = TC::MilkPoints::DEF_DESCRIPTION;
}
