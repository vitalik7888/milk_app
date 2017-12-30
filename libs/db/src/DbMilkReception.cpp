#include "DbMilkReception.h"

#include <MilkReception.h>
#include <Deliverer.h>
#include <TypesConstants.h>
// Qt
#include <QDebug>

USE_DB_NAMESPACE
using TC = TypesConstants;
using DC = DbConstants;


DbMilkReception::DbMilkReception(QObject *parent):
    MilkBaseDbObject(parent)
{
    m_item = std::make_unique<MilkReception>();
    m_milkPoint = new DbMilkPoint(this);
    m_deliverer = new DbDeliverer(this);

    connect(m_milkPoint, &DbMilkPoint::milkIdChanged, this, [this](const MILK_ID milkId) {
        auto mpModel = qobject_cast<MilkReceptionModel *>(model())->milkPoints();
        milkReception()->setMilkPoint(static_cast<const MilkPoint *>(mpModel->getItemById(milkId)));
    });
    connect(m_deliverer, &DbMilkPoint::milkIdChanged, this, [this](const MILK_ID milkId) {
        auto delivModel = qobject_cast<MilkReceptionModel *>(model())->deliverers();
        milkReception()->setDeliverer(static_cast<const Deliverer *>(delivModel->getItemById(milkId)));
    });
    connect(this, &DbMilkReception::modelChanged, this, [this](MilkModel *milkModel) {
        auto _model  = qobject_cast<MilkReceptionModel *>(milkModel);
        m_deliverer->setModel(_model->deliverers());
        m_milkPoint->setModel(_model->milkPoints());
    });
}

QDate DbMilkReception::deliveryDate() const
{
    return milkReception()->deliveryDate();
}

double DbMilkReception::priceLiter() const
{
    return milkReception()->priceLiter();
}

double DbMilkReception::liters() const
{
    return milkReception()->liters();
}

double DbMilkReception::fat() const
{
    return milkReception()->fat();
}

void DbMilkReception::setDeliveryDate(const QDate &_deliveryDate)
{
    if (this->deliveryDate() == _deliveryDate)
        return;

    milkReception()->setDeliveryDate(_deliveryDate);
    emit deliveryDateChanged(this->deliveryDate());
}

void DbMilkReception::setPriceLiter(const double priceLiter)
{
    if (this->priceLiter() == priceLiter)
        return;

    milkReception()->setPriceLiter(priceLiter);
    emit priceLiterChanged(priceLiter);
}

void DbMilkReception::setLiters(const double liters)
{

    if (this->liters() == liters)
        return;

    milkReception()->setLiters(liters);
    emit litersChanged(this->liters());
}

void DbMilkReception::setFat(const double fat)
{
    if (this->fat() == fat)
        return;

    milkReception()->setFat(fat);
    emit fatChanged(this->fat());
}

bool DbMilkReception::saveDelivererId()
{
    if (!milkReception()->deliverer())
        return false;

    return saveValue(QVariant::fromValue<int>(milkReception()->deliverer()->milkId()),
                     static_cast<int>(DC::MilkReceptionRoles::MR_DelivererIdRole));
}

bool DbMilkReception::saveMilkPointId()
{
    if (!milkReception()->milkPoint())
        return false;

    return saveValue(QVariant::fromValue<int>(milkReception()->milkPoint()->milkId()),
                     static_cast<int>(DC::MilkReceptionRoles::MR_MilkPointIdRole));
}

bool DbMilkReception::saveDeliveryDate()
{
    return saveValue(deliveryDate(), static_cast<int>(DC::MilkReceptionRoles::MR_DeliveryDateRole));
}

bool DbMilkReception::savePriceLiter()
{
    return saveValue(priceLiter(), static_cast<int>(DC::MilkReceptionRoles::MR_PriceLiterRole));
}

bool DbMilkReception::saveLiters()
{
    return saveValue(liters(), static_cast<int>(DC::MilkReceptionRoles::MR_LitersRole));
}

bool DbMilkReception::saveFat()
{
    return saveValue(fat(), static_cast<int>(DC::MilkReceptionRoles::MR_FatRole));
}

DbDeliverer *DbMilkReception::deliverer() const
{
    return m_deliverer;
}

DbMilkPoint *DbMilkReception::milkPoint() const
{
    return m_milkPoint;
}

MilkReception *DbMilkReception::milkReception() const
{
    return static_cast<MilkReception*>(m_item.get());
}

void db::DbMilkReception::setItem(const MilkBaseItem *_item)
{
    auto item = static_cast<const MilkReception *>(_item);
    base::setItem(item);
    milkReception()->setDeliverer(item ? item->deliverer() : Q_NULLPTR);
    milkReception()->setMilkPoint(item ? item->milkPoint() : Q_NULLPTR);
    setDeliveryDate(item ? item->deliveryDate() : TC::MilkReception::DEF_DELIVERY_DATE);
    setPriceLiter(item ? item->priceLiter() : TC::MilkReception::DEF_PRICE_LITER);
    setLiters(item ? item->liters() : TC::MilkReception::DEF_LITERS);
    setFat(item ? item->fat() : TC::MilkReception::DEF_FAT);
    m_deliverer->setItem(milkReception()->deliverer());
    m_milkPoint->setItem(milkReception()->milkPoint());
}
