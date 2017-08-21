#include "MilkCore.h"

USE_DB_NAMESPACE


MilkCore::MilkCore(QObject *parent) :
    QObject(parent)
{
    setObjectName("MilkCore");

    m_settings = new Settings(this);
    m_database = new Database(this);
}
