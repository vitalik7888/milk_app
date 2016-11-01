#include "localitydata.h"

USE_DB_NAMESPACE


LocalityData::LocalityData():
    LocalityData(-1, "", "")
{

}

LocalityData::LocalityData(const milk_id id, const QString &name, const QString &description):
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

milk_id LocalityData::id() const
{
    return m_id;
}

void LocalityData::setId(const milk_id &id)
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
