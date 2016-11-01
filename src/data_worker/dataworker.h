#ifndef DATAWORKER_H
#define DATAWORKER_H

#include "milkreception.h"
#include "locality.h"
// Qt
#include <QMap>
#include <QSharedPointer>

DB_BEGIN_NAMESPACE
    class Database;
DB_END_NAMESPACE

using SharLocality = QSharedPointer<Locality>;
using SharMilkPoint = QSharedPointer<MilkPoint>;
using SharDeliverer = QSharedPointer<Deliverer>;
using SharMilkRecep = QSharedPointer<MilkReception>;

class DataWorker
{
public:
    DataWorker(DB_NAMESPACE::Database *db);

    void clear();

    SharLocality getLocality(const milk_id id);
    SharMilkPoint getMilkPoint(const milk_id id);
    SharDeliverer getDeliverer(const milk_id id);
    SharMilkRecep getMilkReception(const milk_id id);

private:
    DB_NAMESPACE::Database *m_db;

    QMap< milk_id, SharLocality >  m_localities;
    QMap< milk_id, SharMilkPoint > m_milkPoints;
    QMap< milk_id, SharDeliverer > m_deliverers;
    QMap< milk_id, SharMilkRecep > m_milkReceptions;
};

#endif // DATAWORKER_H
