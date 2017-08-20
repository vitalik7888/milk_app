#include "MilkCore.h"

USE_DB_NAMESPACE


MilkCore::MilkCore(QObject *parent) :
    QObject(parent),
    m_database(new Database())
{
    m_settings = new Settings(this);
}
