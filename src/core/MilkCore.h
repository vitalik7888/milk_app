#ifndef MILKCORE_H
#define MILKCORE_H

#include "src/database/base/Database.h"
#include "Settings.h"
// Qt
#include <QScopedPointer>

class MilkCore
{
public:
    explicit MilkCore();
    ~MilkCore() {}

    Settings *settings() { return m_settings.data(); }
    DB_NAMESPACE::Database *database() const { return m_database.data(); }

private:
    QScopedPointer<Settings> m_settings;
    QScopedPointer<DB_NAMESPACE::Database> m_database;
};

#endif // MILKCORE_H
