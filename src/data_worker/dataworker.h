#ifndef DATAWORKER_H
#define DATAWORKER_H

#include "locality.h"
#include "milkpoint.h"
#include "deliverer.h"
#include "milkreception.h"
// Qt
#include <QMap>
#include <QSharedPointer>

DB_BEGIN_NAMESPACE
    class Database;
    class DelivererData;
    class MilkPointData;
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
    void reload();

    void loadMilkReceptions(const QString &where); // TODO filter

    bool isLocalityExists(const milk_id id) const;
    bool isMilkPointExists(const milk_id id) const;
    bool isDelivererExists(const milk_id id) const;
    bool isMilkRecepExists(const milk_id id) const;

    QMap<milk_id, SharLocality> getLocalities() const;
    QMap<milk_id, SharMilkPoint> getMilkPoints() const;
    QMap<milk_id, SharDeliverer> getDeliverers() const;
    QMap<milk_id, SharMilkRecep> getMilkReceptions() const;

private:
    DB_NAMESPACE::Database *m_db;

    QMap< milk_id, SharLocality >  m_localities;
    QMap< milk_id, SharMilkPoint > m_milkPoints;
    QMap< milk_id, SharDeliverer > m_deliverers;
    QMap< milk_id, SharMilkRecep > m_milkReceptions;

    SharLocality getLocality(const DB_NAMESPACE::LocalityData &data);
    SharMilkPoint getMilkPoint(const DB_NAMESPACE::MilkPointData &data);
    SharDeliverer getDeliverer(const DB_NAMESPACE::DelivererData &data);
    SharMilkRecep getMilkReception(const DB_NAMESPACE::MilkReceptionData &data);
    SharLocality getLocality(const milk_id id);
    SharMilkPoint getMilkPoint(const milk_id id);
    SharDeliverer getDeliverer(const milk_id id);
    SharMilkRecep getMilkReception(const milk_id id);
    SharLocality insert(const DB_NAMESPACE::LocalityData &data);
    SharMilkPoint insert(const DB_NAMESPACE::MilkPointData &data);
    SharDeliverer insert(const DB_NAMESPACE::DelivererData &data);
    SharMilkRecep insert(const DB_NAMESPACE::MilkReceptionData &data);
};

#endif // DATAWORKER_H
