#include "milkreception.h"

#include "deliverer.h"
#include "milkpoint.h"


MilkReception::MilkReception(QObject *parent):
    MilkReception(-1, QDate(), .0, .0, .0, Q_NULLPTR, Q_NULLPTR, parent)
{

}

MilkReception::MilkReception(const milk_id id, const QDate deliveryDate, const price priceLiter,
                             const double liters, const double fat,
                             Deliverer *deliverer, MilkPoint *milkPoint, QObject *parent):
    QObject(parent),
    m_data(id, deliverer == Q_NULLPTR ? -1 : deliverer->id(),
               milkPoint == Q_NULLPTR ? -1 : milkPoint->id(),
           deliveryDate, priceLiter, liters, fat),
    m_deliverer(deliverer),
    m_milkPoint(milkPoint)
{

}

MilkReception::~MilkReception()
{

}

milk_id MilkReception::id() const
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

DB_NAMESPACE::MilkReceptionData MilkReception::data() const
{
    return m_data;
}

CalculatedItem::Data MilkReception::getCalculationsData() const
{
    return CalculatedItem(liters(), fat(), priceLiter()).data();
}

CalculatedItem *MilkReception::getCalculations()
{
    return new CalculatedItem(liters(), fat(), priceLiter(), this);
}

bool MilkReception::isValid() const
{
    return m_data.isValid();
}

void MilkReception::setId(const milk_id &id)
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
    m_data.setDelivererId(deliverer == Q_NULLPTR ? -1 : deliverer->id());
    emit delivererChanged(deliverer);
}

void MilkReception::setMilkPoint(MilkPoint *milkPoint)
{
    if (m_milkPoint == milkPoint)
        return;

    m_milkPoint = milkPoint;
    m_data.setMilkPointId(milkPoint == Q_NULLPTR ? -1 : milkPoint->id());
    emit milkPointChanged(milkPoint);
}

void MilkReception::setDeliveryDate(const QDate &deliveryDate)
{
    if (m_data.deliveryDate() == deliveryDate)
        return;

    m_data.setDeliveryDate(deliveryDate);
    emit deliveryDateChanged(deliveryDate);
}

void MilkReception::setPriceLiter(price priceLiter)
{
    if (m_data.priceLiter() == priceLiter)
        return;

    m_data.setPriceLiter(priceLiter);
    emit priceLiterChanged(priceLiter);
}

void MilkReception::setLiters(double liters)
{
    if (m_data.liters() == liters)
        return;

    m_data.setLiters(liters);
    emit litersChanged(liters);
}

void MilkReception::setFat(double fat)
{
    if (m_data.fat() == fat)
        return;

    m_data.setFat(fat);
    emit fatChanged(fat);
}
