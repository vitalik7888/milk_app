#include "DbMilkPoint.h"

#include <TypesConstants.h>
// Qt
#include <QDebug>

USE_DB_NAMESPACE
using TC = TypesConstants;


DbMilkPoint::DbMilkPoint(QObject *parent) :
    MilkBaseDbObject(parent)
{
    m_item = std::make_unique<MilkPoint>();
    m_locality = new DbLocality(this);

    connect(m_locality, &DbLocality::milkIdChanged, this, [this](const MILK_ID milkId) {
        auto mpModel = qobject_cast<MilkPointsModel *>(model());
        milkPoint()->setLocality(static_cast<const Locality *>(mpModel->localities()->getItemById(milkId)));
    });
    connect(this, &MilkBaseDbObject::modelChanged, this, [this](MilkModel* milkModel) {
       m_locality->setModel(qobject_cast<MilkPointsModel *>(milkModel)->localities());
    });
}

QString DbMilkPoint::name() const
{
    return milkPoint()->name();
}

QString DbMilkPoint::description() const
{
    return milkPoint()->description();
}

void DbMilkPoint::setName(const QString &name)
{
    if (milkPoint()->name() == name)
        return;

    milkPoint()->setName(name);
    emit nameChanged(name);
}

void DbMilkPoint::setDescription(const QString &description)
{
    if (milkPoint()->description() == description)
        return;

    milkPoint()->setDescription(description);
    emit descriptionChanged(description);
}

void DbMilkPoint::setItem(const MilkBaseItem *_item)
{
    auto item = static_cast<const MilkPoint *>(_item);
    base::setItem(item);
    milkPoint()->setLocality(item ? item->locality() : Q_NULLPTR);
    setName(item ? item->name() : TC::Localities::DEF_NAME);
    setDescription(item ? item->description() : TC::Localities::DEF_DESCRIPTION);
    m_locality->setItem(item ? item->locality() : Q_NULLPTR);
}

MilkPoint *DbMilkPoint::milkPoint() const
{
    return static_cast<MilkPoint *>(m_item.get());
}
