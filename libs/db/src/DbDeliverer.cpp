#include "DbDeliverer.h"

#include "DbMilkReception.h"
#include <Deliverer.h>
#include <TypesConstants.h>
// Qt
#include <QDebug>

USE_DB_NAMESPACE
using TC = TypesConstants;
using DC = DbConstants;


// -- Repository
void MilkReceptionRepository::append(DbMilkReception *milkReception)
{
    m_items.append(milkReception);
}

void MilkReceptionRepository::clear()
{
    m_items.clear();
}

DelivererMilkReceptions MilkReceptionRepository::getAll() const
{
    return m_items;
}

DbMilkReception *MilkReceptionRepository::get(const int position) const
{
    return m_items.at(position);
}

int MilkReceptionRepository::count() const
{
    return m_items.size();
}

bool MilkReceptionRepository::isEmpty() const
{
    return m_items.isEmpty();
}
// ------------------------

DbDeliverer::DbDeliverer(QObject *parent) : MilkBaseDbObject(parent)
{
    m_item = std::make_unique<Deliverer>();
    m_locality = new DbLocality(this);

    connect(m_locality, &DbLocality::milkIdChanged, this, [this](const MILK_ID milkId) {
        auto mpModel = qobject_cast<DeliverersModel *>(model());
        deliverer()->setLocality(static_cast<const Locality *>(mpModel->localities()->getItemById(milkId)));
    });
    connect(this, &DbDeliverer::modelChanged, this, [this](MilkModel* model) {
        m_locality->setModel(qobject_cast<DeliverersModel *>(model)->localities());
    });
}

QString DbDeliverer::firstName() const
{
    return deliverer()->firstName();
}

QString DbDeliverer::lastName() const
{
    return deliverer()->lastName();
}

QString DbDeliverer::fullName() const
{
    return deliverer()->fullName();
}

QString DbDeliverer::inn() const
{
    return deliverer()->inn();
}

QString DbDeliverer::address() const
{
    return deliverer()->address();
}

QString DbDeliverer::phoneNumber() const
{
    return deliverer()->phoneNumber();
}

void DbDeliverer::setFirstName(const QString &firstName)
{
    if (deliverer()->firstName() == firstName)
        return;

    deliverer()->setFirstName(firstName);
    emit firstNameChanged(firstName);
}

void DbDeliverer::setLastName(const QString &lastName)
{
    if (deliverer()->lastName() == lastName)
        return;

    deliverer()->setLastName(lastName);
    emit lastNameChanged(lastName);
}

void DbDeliverer::setInn(const QString &inn)
{
    if (deliverer()->inn() == inn)
        return;

    deliverer()->setInn(inn);
    emit innChanged(inn);
}

void DbDeliverer::setAddress(const QString &address)
{
    if (deliverer()->address() == address)
        return;

    deliverer()->setAddress(address);
    emit addressChanged(address);
}

void DbDeliverer::setPhoneNumber(const QString &phoneNumber)
{
    if (deliverer()->phoneNumber() == phoneNumber)
        return;

    deliverer()->setPhoneNumber(phoneNumber);
    emit phoneNumberChanged(phoneNumber);
}

bool DbDeliverer::saveMilkId()
{
    return saveValue(QVariant::fromValue<int>(milkId()),
                     static_cast<int>(DC::DeliverersRoles::MilkIdRole));
}

Deliverer *DbDeliverer::deliverer() const
{
    return static_cast<Deliverer *>(m_item.get());
}

void DbDeliverer::setItem(const MilkBaseItem *_item)
{
    auto item = static_cast<const Deliverer *>(_item);
    base::setItem(item);
    deliverer()->setLocality(item ? item->locality() : Q_NULLPTR);
    setFirstName(item ? item->firstName() : TC::Deliverers::DEF_FIRST_NAME);
    setLastName(item ? item->lastName() : TC::Deliverers::DEF_LAST_NAME);
    setInn(item ? item->inn() : TC::Deliverers::DEF_INN);
    setAddress(item ? item->address() : TC::Deliverers::DEF_ADDRESS);
    setPhoneNumber(item ? item->phoneNumber() : TC::Deliverers::DEF_PHONE_NUMBER);
    m_locality->setItem(deliverer()->locality());
}

QQmlListProperty<DbMilkReception> DbDeliverer::_milkReceptions()
{
    return QQmlListProperty<DbMilkReception>(this, this,
                                             &DbDeliverer::_appendMilkReception,
                                             &DbDeliverer::_milkReceprionsCount,
                                             &DbDeliverer::_milkReception,
                                             &DbDeliverer::_clearMilkReceptions);
}

void DbDeliverer::_appendMilkReception(QQmlListProperty<DbMilkReception> *list, DbMilkReception *milkReception)
{
    reinterpret_cast< DbDeliverer* >(list->data)->m_repository.append(milkReception);
}

int DbDeliverer::_milkReceprionsCount(QQmlListProperty<DbMilkReception> *list)
{
    return reinterpret_cast< DbDeliverer* >(list->data)->m_repository.count();
}

DbMilkReception *DbDeliverer::_milkReception(QQmlListProperty<DbMilkReception> *list, const int position)
{
    return reinterpret_cast< DbDeliverer* >(list->data)->m_repository.get(position);
}

void DbDeliverer::_clearMilkReceptions(QQmlListProperty<DbMilkReception> *list)
{
    reinterpret_cast< DbDeliverer* >(list->data)->m_repository.clear();
}
