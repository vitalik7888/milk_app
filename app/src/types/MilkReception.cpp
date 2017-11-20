#include "MilkReception.h"

#include "Deliverer.h"
#include "MilkPoint.h"
#include "TypesConstants.h"

using TC = TypesConstants;
using TCMR = TC::MilkReception;


MilkReception::MilkReception(QObject *parent):
    MilkReception(TCMR::DEF_ID, TCMR::DEF_DELIVERY_DATE,
                  TCMR::DEF_PRICE_LITER, TCMR::DEF_LITERS, TCMR::DEF_FAT, Q_NULLPTR, Q_NULLPTR, parent)
{

}

MilkReception::MilkReception(const TC::milk_id id, const QDate deliveryDate, const double priceLiter,
                             const double liters, const double fat,
                             Deliverer *deliverer, MilkPoint *milkPoint, QObject *parent):
    QObject(parent),
    m_data(id, deliverer == Q_NULLPTR ? TCMR::DEF_ID_DELIVERER : deliverer->id(),
               milkPoint == Q_NULLPTR ? TCMR::DEF_MILK_POINT_ID : milkPoint->id(),
           deliveryDate, priceLiter, liters, fat),
    m_deliverer(deliverer),
    m_milkPoint(milkPoint)
{

}

MilkReception::MilkReception(const MilkReception &mr):
    QObject(mr.parent()),
    m_data(mr.data()),
    m_deliverer(mr.deliverer()),
    m_milkPoint(mr.milkPoint())
{

}

MilkReception::~MilkReception()
{

}

TC::milk_id MilkReception::id() const
{
    return m_data.id();
}

QDate MilkReception::deliveryDate() const
{
    return m_data.deliveryDate();
}

double MilkReception::priceLiter() const
{
    return m_data.priceLiter();
}

double MilkReception::liters() const
{
    return m_data.liters();
}

double MilkReception::fat() const
{
    return m_data.fat();
}

Deliverer *MilkReception::deliverer() const
{
    return m_deliverer;
}

MilkPoint *MilkReception::milkPoint() const
{
    return m_milkPoint;
}

MilkReceptionData MilkReception::data() const
{
    return m_data;
}

bool MilkReception::isValid() const
{
    return m_data.isValid();
}

void MilkReception::setId(const TC::milk_id &id)
{
    if (id == m_data.id())
        return;

    m_data.setId(id);
    emit idChanged(id);
}

void MilkReception::setDeliverer(Deliverer *deliverer)
{
    if (m_deliverer == deliverer)
        return;

    m_deliverer = deliverer;
    m_data.setDelivererId(deliverer == Q_NULLPTR ? TCMR::DEF_ID_DELIVERER: deliverer->id());
    emit delivererChanged(deliverer);
}

void MilkReception::setMilkPoint(MilkPoint *milkPoint)
{
    if (m_milkPoint == milkPoint)
        return;

    m_milkPoint = milkPoint;
    m_data.setMilkPointId(milkPoint == Q_NULLPTR ? TCMR::DEF_MILK_POINT_ID : milkPoint->id());
    emit milkPointChanged(milkPoint);
}

void MilkReception::reset()
{
    m_data = {};
    m_milkPoint = Q_NULLPTR;
    m_deliverer = Q_NULLPTR;
}

void MilkReception::setDeliveryDate(const QDate &deliveryDate)
{
    if (m_data.deliveryDate() == deliveryDate)
        return;

    m_data.setDeliveryDate(deliveryDate);
    emit deliveryDateChanged(m_data.deliveryDate());
}

void MilkReception::setPriceLiter(double priceLiter)
{
//    qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_data.priceLiter(), priceLiter))
        return;

    m_data.setPriceLiter(priceLiter);
    emit priceLiterChanged(priceLiter);
}

void MilkReception::setLiters(double liters)
{
//    qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_data.liters(), liters))
        return;

    m_data.setLiters(liters);
    emit litersChanged(liters);
}

void MilkReception::setFat(double fat)
{
//    qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_data.fat(), fat))
        return;

    m_data.setFat(fat);
    emit fatChanged(fat);
}
