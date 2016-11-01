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

SharLocality DataWorker::getLocality(const milk_id id)
{
    SharLocality shpLocality;

    if (!m_localities.contains(id)) {
        LocalityData ld;
        try {
            ld = m_db->localities()->getLocality(id);
        } catch (const QString &err) {
            qDebug() << "Data worker get locality error:" << err;
        }
        if (ld.isValid()) {

            m_localities.insert(id, fromData(ld));
        }
    } else {
        shpLocality = m_localities[id];
    }

    return shpLocality;
}

SharMilkPoint DataWorker::getMilkPoint(const milk_id id)
{
    SharMilkPoint shpMilkPoint;

    if (!m_milkPoints.contains(id)) {
        MilkPointData data;
        try {
            data = m_db->milkPoints()->getMilkPoint(id);
        } catch (const QString &err) {
            qDebug() << "Data worker get milk point error:" << err;
        }
        if (data.isValid())
            m_milkPoints.insert(id, fromData(data));
    } else {
        shpMilkPoint = m_milkPoints[id];
    }

    return shpMilkPoint;
}

SharDeliverer DataWorker::getDeliverer(const milk_id id)
{
    SharDeliverer shpDeliverer;

    if (!m_deliverers.contains(id)) {
        DelivererData data;
        try {
            data = m_db->deliverers()->getDeliverer(id);
        } catch (const QString &err) {
            qDebug() << "Data worker get deliverer error:" << err;
        }
        if (data.isValid())
            m_deliverers.insert(id, fromData(data));
    } else {
        shpDeliverer = m_deliverers[id];
    }

    return shpDeliverer;
}

SharMilkRecep DataWorker::getMilkReception(const milk_id id)
{
    SharMilkRecep shpMilkRecep;

    if (!m_milkReceptions.contains(id)) {
        MilkReceptionData data;
        try {
            data = m_db->milkReception()->getMilkReception(id);
        } catch (const QString &err) {
            qDebug() << "Data worker get milk reception error:" << err;
        }
        if (data.isValid())
            m_milkReceptions.insert(id, fromData(data));
    } else {
        shpMilkRecep = m_milkReceptions[id];
    }

    return shpMilkRecep;
}

SharDeliverer DataWorker::fromData(const DelivererData &data)
{
    const auto locality = getLocality(data.localityId());
    const auto deliverer = new Deliverer(data.id(), data.name(), data.inn(), data.address(),
                                         data.phoneNumber(), locality.toWeakRef());
    return SharDeliverer(deliverer);
}

SharMilkRecep DataWorker::fromData(const MilkReceptionData &data)
{
    const auto deliverer = getDeliverer(data.delivererId());
    const auto milkPoint = getMilkPoint(data.milkPointId());
    const auto milkRecep = new MilkReception(data.id(), data.deliveryDate(), data.priceLiter(),
                                             data.liters(), data.fat(), deliverer.toWeakRef(),
                                             milkPoint.toWeakRef());
    return SharMilkRecep(milkRecep);
}

SharLocality DataWorker::fromData(const LocalityData &data)
{
    const auto locality = new Locality(data.id(), data.name(), data.description());
    return SharLocality(locality);
}

SharMilkPoint DataWorker::fromData(const db::MilkPointData &data)
{
    const auto locality = getLocality(data.localityId());
    const auto milkPoint = new MilkPoint(data.id(), data.name(), data.description(), locality.toWeakRef());
    return SharMilkPoint(milkPoint);
}
