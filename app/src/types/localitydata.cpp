#include "localitydata.h"

#include "TypesConstants.h"

using TC = TypesConstants;
using TCL = TC::Localities;


LocalityData::LocalityData():
    LocalityData(TCL::DEF_ID, TCL::DEF_NAME, TCL::DEF_DESCRIPTION)
{

}

LocalityData::LocalityData(const TC::milk_id id, const QString &name,
                           const QString &description):
    m_id(id),
    m_name(name),
    m_description(description)
{

}

LocalityData::LocalityData(const LocalityData &data):
    m_id(data.id()),
    m_name(data.name()),
    m_description(data.description())
{

}

LocalityData::~LocalityData()
{

}

TC::milk_id LocalityData::id() const
{
    return m_id;
}

void LocalityData::setId(const TC::milk_id &id)
{
    m_id = id;
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

bool LocalityData::isValid() const
{
    return m_id > 0;
}
