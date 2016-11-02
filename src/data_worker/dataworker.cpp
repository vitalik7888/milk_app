#include "dataworker.h"

#include <base/Database.h>
#include "milkpoint.h"
#include "deliverer.h"
// Qt
#include <QDebug>

USE_DB_NAMESPACE


DataWorker::DataWorker(Database *db):
    m_db(db)
{

}

void DataWorker::clear()
{
    m_deliverers.clear();
    m_milkPoints.clear();
    m_localities.clear();
}

void DataWorker::reload()
{
    const QList<milk_id> localities = m_localities.keys(),
            milkPoints = m_milkPoints.keys(),
            deliverers = m_deliverers.keys(),
            milkReceptions = m_milkReceptions.keys();
    clear();
    for (const auto id: localities)
        getLocality(id);
    for (const auto id: milkPoints)
        getMilkPoint(id);
    for (const auto id: deliverers)
        getDeliverer(id);
    for (const auto id: milkReceptions)
        getMilkReception(id);
}

void DataWorker::loadMilkReceptions(const QString &where)
{
    try {
        const auto milkReceptions = m_db->milkReception()->getMilkReceptions(where);
        for (const auto &data: milkReceptions) {
            getMilkReception(data);
        }
    } catch (const QString &err) {
        qDebug() << "Data worker load milk receptions error:" << err;
        throw;
    }
}

bool DataWorker::isLocalityExists(const milk_id id) const
{
    return m_localities.contains(id);
}

bool DataWorker::isMilkPointExists(const milk_id id) const
{
    return m_milkPoints.contains(id);
}

bool DataWorker::isDelivererExists(const milk_id id) const
{
    return m_deliverers.contains(id);
}

bool DataWorker::isMilkRecepExists(const milk_id id) const
{
    return m_milkReceptions.contains(id);
}

QMap<milk_id, SharLocality> DataWorker::getLocalities() const
{
    return m_localities;
}

QMap<milk_id, SharMilkPoint> DataWorker::getMilkPoints() const
{
    return m_milkPoints;
}

QMap<milk_id, SharDeliverer> DataWorker::getDeliverers() const
{
    return m_deliverers;
}

QMap<milk_id, SharMilkRecep> DataWorker::getMilkReceptions() const
{
    return m_milkReceptions;
}

SharLocality DataWorker::getLocality(const LocalityData &data)
{
    if (!isLocalityExists(data.id())) {
        return insert(data);
    }

    return m_localities[data.id()];
}

SharMilkPoint DataWorker::getMilkPoint(const MilkPointData &data)
{
    if (!isMilkPointExists(data.id())) {
        return insert(data);
    }
    return m_milkPoints[data.id()];
}

SharDeliverer DataWorker::getDeliverer(const DelivererData &data)
{
    if (isDelivererExists(data.id())) {
        return insert(data);
    }
    return m_deliverers[data.id()];
}

SharMilkRecep DataWorker::getMilkReception(const MilkReceptionData &data)
{
    if (isMilkRecepExists(data.id())) {
        return insert(data);
    }
    return m_milkReceptions[data.id()];
}

SharLocality DataWorker::getLocality(const milk_id id)
{
    SharLocality shpLocality;

    if (!isLocalityExists(id)) {
        try {
            const auto data = m_db->localities()->getLocality(id);
            shpLocality = insert(data);
        } catch (const QString &err) {
            qDebug() << "Data worker get locality error:" << err;
        }
    } else
        shpLocality = m_localities[id];

    return shpLocality;
}

SharMilkPoint DataWorker::getMilkPoint(const milk_id id)
{
    SharMilkPoint shpMilkPoint;

    if (!isMilkPointExists(id)) {
        try {
            const auto data = m_db->milkPoints()->getMilkPoint(id);
            shpMilkPoint = insert(data);
        } catch (const QString &err) {
            qDebug() << "Data worker get milk point error:" << err;
        }
    } else {
        shpMilkPoint = m_milkPoints[id];
    }

    return shpMilkPoint;
}

SharDeliverer DataWorker::getDeliverer(const milk_id id)
{
    SharDeliverer shpDeliverer;

    if (!isDelivererExists(id)) {
        try {
            const auto data = m_db->deliverers()->getDeliverer(id);
            shpDeliverer = insert(data);
        } catch (const QString &err) {
            qDebug() << "Data worker get deliverer error:" << err;
        }
    } else {
        shpDeliverer = m_deliverers[id];
    }

    return shpDeliverer;
}

SharMilkRecep DataWorker::getMilkReception(const milk_id id)
{
    SharMilkRecep shpMilkRecep;

    if (!isMilkRecepExists(id)) {
        try {
            const auto data = m_db->milkReception()->getMilkReception(id);
            shpMilkRecep = insert(data);
        } catch (const QString &err) {
            qDebug() << "Data worker get milk reception error:" << err;
        }
    } else {
        shpMilkRecep = m_milkReceptions[id];
    }

    return shpMilkRecep;
}

SharLocality DataWorker::insert(const LocalityData &data)
{
    const auto locality = new Locality(data.id(), data.name(), data.description());
    const auto shLocality = SharLocality(locality);
    m_localities.insert(data.id(), shLocality);

    return shLocality;
}

SharMilkPoint DataWorker::insert(const MilkPointData &data)
{
    const auto locality = getLocality(data.localityId());
    const auto milkPoint = new MilkPoint(data.id(), data.name(), data.description(), locality.toWeakRef());
    const auto shared = SharMilkPoint(milkPoint);
    m_milkPoints.insert(data.id(), shared);

    return shared;
}

SharDeliverer DataWorker::insert(const DelivererData &data)
{
    const auto locality = getLocality(data.localityId());
    const auto deliverer = new Deliverer(data.id(), data.name(), data.inn(), data.address(),
                                         data.phoneNumber(), locality.toWeakRef());
    const auto shared = SharDeliverer(deliverer);
    m_deliverers.insert(data.id(), shared);

    return shared;
}

SharMilkRecep DataWorker::insert(const MilkReceptionData &data)
{
    auto deliverer = getDeliverer(data.delivererId());
    const auto milkPoint = getMilkPoint(data.milkPointId());
    const auto milkRecep = new MilkReception(data.id(), data.deliveryDate(), data.priceLiter(),
                                             data.liters(), data.fat(), deliverer.toWeakRef(),
                                             milkPoint.toWeakRef());
    const auto shared = SharMilkRecep(milkRecep);
    deliverer->addMilkReception(shared.toWeakRef());
    m_milkReceptions.insert(data.id(), shared);

    return shared;
}
