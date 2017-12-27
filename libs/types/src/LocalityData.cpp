#include "LocalityData.h"

#include "TypesConstants.h"

using TC = TypesConstants;


LocalityData::LocalityData():
    LocalityData(TC::DEFAULT_ID, TC::Localities::DEF_NAME, TC::Localities::DEF_DESCRIPTION)
{

}

LocalityData::LocalityData(const MILK_ID id, const QString &name, const QString &description):
    m_milkId(id),
    m_name(name),
    m_description(description)
{

}

LocalityData::LocalityData(const LocalityData &data):
    QSharedData(data),
    m_milkId(data.milkId()),
    m_name(data.name()),
    m_description(data.description())
{

}

void LocalityData::setMilkId(const MILK_ID id)
{
    m_milkId = id;
}

QString LocalityData::name() const
{
    return m_name;
}

void LocalityData::setName(const QString &name)
{
    m_name = name;
}

QString LocalityData::description() const
{
    return m_description;
}

void LocalityData::setDescription(const QString &description)
{
    m_description = description;
}

void LocalityData::reset()
{
    MilkBaseItem::reset();
    m_name = TC::Localities::DEF_NAME;
    m_description = TC::Localities::DEF_DESCRIPTION;
}
