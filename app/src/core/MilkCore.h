#ifndef MILKCORE_H
#define MILKCORE_H

#include "Constants.h"
#include "src/database/base/Database.h"
#include "Settings.h"
// Qt
#include <QScopedPointer>

class MilkCore
{
public:
    explicit MilkCore();
    virtual ~MilkCore();

    Settings *settings() const;
    DB_NAMESPACE::Database *database() const;

private:
    QScopedPointer<Settings> m_settings;
    QScopedPointer<DB_NAMESPACE::Database> m_database;
};

#endif // MILKCORE_H
