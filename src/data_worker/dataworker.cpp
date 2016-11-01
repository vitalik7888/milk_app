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

SharDeliverer DataWorker::getDeliverer(const milk_id id)
{
    SharDeliverer shpDeliverer;

    if (!m_deliverers.contains(id)) {
        DelivererData dd;
        try {
            dd = m_db->deliverers()->getDeliverer(id);
        } catch (const QString &err) {
            qDebug() << err;
        }
        if (dd.isValid()) {
            const auto locality = getLocality(dd.localityId());
            const auto deliverer = new Deliverer(dd.id(), dd.name(), dd.inn(), dd.address(),
                                                 dd.phoneNumber(), locality.toWeakRef());
            shpDeliverer = SharDeliverer(deliverer);
            m_deliverers.insert(id, shpDeliverer);
        }
    } else {
        shpDeliverer = m_deliverers[id];
    }

    return shpDeliverer;
}

SharMilkRecep DataWorker::getMilkReception(const milk_id id)
{
    SharMilkRecep shpMilkRecep;

    if (!m_milkReceptions.contains(id)) {
        MilkReceptionData mrd;
        try {
            mrd = m_db->milkReception()->getMilkReception(id);
        } catch (const QString &err) {
            qDebug() << err;
        }
        if (mrd.isValid()) {
            const auto deliverer = getDeliverer(mrd.delivererId());
            const auto milkPoint = getMilkPoint(mrd.milkPointId());
            const auto milkRecep = new MilkReception(mrd.id(), mrd.deliveryDate(), mrd.priceLiter(),
                                                     mrd.liters(), mrd.fat(), deliverer.toWeakRef(),
                                                     milkPoint.toWeakRef());
            shpMilkRecep = SharMilkRecep(milkRecep);
            m_milkReceptions.insert(id, shpMilkRecep);
        }
    } else {
        shpMilkRecep = m_milkReceptions[id];
    }

    return shpMilkRecep;
}

SharLocality DataWorker::getLocality(const milk_id id)
{
    SharLocality shpLocality;

    if (!m_localities.contains(id)) {
        LocalityData ld;
        try {
            ld = m_db->localities()->getLocality(id);
        } catch (const QString &err) {
            qDebug() << err;
        }
        if (ld.isValid()) {
            const auto locality = new Locality(ld.id(), ld.name(), ld.description());
            shpLocality = SharLocality(locality);
            m_localities.insert(id, shpLocality);
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
        MilkPointData md;
        try {
            md = m_db->milkPoints()->getMilkPoint(id);
        } catch (const QString &err) {
            qDebug() << err;
        }
        if (md.isValid()) {
            const auto locality = getLocality(md.localityId());
            const auto milkPoint = new MilkPoint(md.id(), md.name(), md.description(), locality.toWeakRef());
            shpMilkPoint = SharMilkPoint(milkPoint);
            m_milkPoints.insert(id, shpMilkPoint);
        }
    } else {
        shpMilkPoint = m_milkPoints[id];
    }

    return shpMilkPoint;
}
