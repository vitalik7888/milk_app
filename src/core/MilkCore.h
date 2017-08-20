#ifndef MILKCORE_H
#define MILKCORE_H

#include "src/database/base/Database.h"
#include "Settings.h"
// Qt
#include <QScopedPointer>


class MilkCore : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Settings *settings READ settings)

public:
    MilkCore(QObject *parent = Q_NULLPTR);
    virtual ~MilkCore() {}

    Settings *settings() { return m_settings; }
    DB_NAMESPACE::Database *database() const { return m_database.data(); }

private:
    Settings *m_settings;
    QScopedPointer<DB_NAMESPACE::Database> m_database;
};

#endif // MILKCORE_H
