#include "MilkCore.h"

USE_DB_NAMESPACE


MilkCore::MilkCore() :
    m_settings(new Settings()),
    m_database(new Database())
{
}
