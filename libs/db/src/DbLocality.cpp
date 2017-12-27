#include "DbLocality.h"

#include <TypesConstants.h>
// Qt
#include <QDebug>

USE_DB_NAMESPACE
using TC = TypesConstants;


DbLocality::DbLocality(QObject *parent):
    MilkBaseDbObject(parent)
{
    m_item = std::make_unique<Locality>();
}

QString DbLocality::name() const {
    return locality()->name();
}

QString DbLocality::description() const
{
    return locality()->description();
}

void DbLocality::setName(const QString &name)
{
    if (this->name() == name)
        return;

    locality()->setName(name);
    emit nameChanged(name);
}

void DbLocality::setDescription(const QString &description)
{
    if (this->description() == description)
        return;

    locality()->setDescription(description);
    emit descriptionChanged(description);
}

Locality *DbLocality::locality() const
{
    return static_cast<Locality *>(m_item.get());
}

void db::DbLocality::setItem(const MilkBaseItem *_item)
{
    auto item = static_cast<const Locality *>(_item);
    base::setItem(item);
    setName(item ? item->name() : TC::Localities::DEF_NAME);
    setDescription(item ? item->description() : TC::Localities::DEF_DESCRIPTION);
}
