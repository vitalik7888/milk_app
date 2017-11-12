#include "MilkCore.h"

USE_DB_NAMESPACE


MilkCore::MilkCore() :
    m_settings(new Settings()),
    m_database(new Database())
{
}

MilkCore::~MilkCore() {}

Settings *MilkCore::settings() const { return m_settings.data(); }

Database *MilkCore::database() const { return m_database.data(); }
