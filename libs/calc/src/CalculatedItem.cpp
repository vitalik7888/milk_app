#include "CalculatedItem.h"

#include <MilkReception.h>
#include <Deliverer.h>
#include <MilkPoint.h>


CalculatedItem::CalculatedItem(const QString &delivererName, const QString &milkPointName, const QDate &deliveryDate,
                               const double liters, const double fat, const double price,
                               CalculatedItem *parent, QObject *objectParent):
    QObject(objectParent),
    m_parent(parent),
    m_delivererFullName(delivererName),
    m_milkPointName(milkPointName),
    m_deliveryDate(deliveryDate),
    m_itemData(liters, fat, price)
{
}

CalculatedItem::CalculatedItem(QObject *objectParent):
    CalculatedItem({}, {}, {}, .0, .0, .0, Q_NULLPTR, objectParent)
{

}

CalculatedItem::~CalculatedItem()
{
    qDeleteAll(m_items.begin(), m_items.end());
    m_items.clear();
}

void CalculatedItem::setItems(const Items &calcItems)
{
    m_items = calcItems;
    addData(m_items);
}

void CalculatedItem::setCalcParent(CalculatedItem *parent)
{
    if (m_parent == parent)
        return;

    m_parent = parent;
    emit parentChanged(m_parent);
}

CalculatedItem *CalculatedItem::item(const int position) const
{
    return m_items.at(position);
}

int CalculatedItem::itemsCount() const
{
    return m_items.size();
}

void CalculatedItem::clearItems()
{
    m_items.clear();
    m_itemData = CalculatedItemData();
}

QVariant CalculatedItem::data(const Columns column) const
{
    switch (column) {
    case Columns::Name: return QVariant::fromValue(delivererFullName());
    case Columns::Date: return QVariant::fromValue(deliveryDate());
    case Columns::MilkPointName: return QVariant::fromValue(milkPointName());
    case Columns::Price: return QVariant::fromValue(m_itemData.priceForLiter());
    case Columns::Liters: return QVariant::fromValue(m_itemData.liters());
    case Columns::Fat: return QVariant::fromValue(m_itemData.fat());
    case Columns::Protein: return QVariant::fromValue(m_itemData.protein());
    case Columns::FatUnits: return QVariant::fromValue(m_itemData.fatUnits());
    case Columns::RankWeight: return QVariant::fromValue(m_itemData.rankWeight());
    case Columns::PaymentWithOutPremium: return QVariant::fromValue(m_itemData.paymentWithOutPremium());
    case Columns::PremiumForFat: return QVariant::fromValue(m_itemData.premiumForFat());
    case Columns::Sum: return QVariant::fromValue(m_itemData.sum());
    case Columns::ColumnsCount: break;
    }

    return QVariant();
}

int CalculatedItem::row() const
{
    return m_parent ? m_parent->m_items.indexOf(const_cast<CalculatedItem *>(this)) : 0;
}

int CalculatedItem::columnCount() const
{
    return static_cast<int>(Columns::ColumnsCount);
}

void CalculatedItem::addItem(CalculatedItem *item)
{
    addData(item->itemData());
    m_items.append(item);
}

void CalculatedItem::addItems(const Items &calcItems)
{
    m_items.append(calcItems);
    addData(calcItems);
}

void CalculatedItem::addData(const Items &calcItems)
{
    const auto beforeData = m_itemData;

    for (auto item : calcItems)
        m_itemData += item->itemData();

    checkItemsData(beforeData, itemData());
}

void CalculatedItem::addData(const CalculatedItemData &item)
{
    const auto beforeData = m_itemData;

    m_itemData += item;

    checkItemsData(beforeData, itemData());
}

void CalculatedItem::checkItemsData(const CalculatedItemData &beforeData, const CalculatedItemData &afterData)
{
    if (beforeData.liters() < afterData.liters())
        emit litersChanged(afterData.liters());
    if (beforeData.fat() < afterData.fat())
        emit fatChanged(afterData.fat());
    if (beforeData.priceForLiter() < afterData.priceForLiter())
        emit priceForLiterChanged(afterData.priceForLiter());
    if (beforeData.protein() < afterData.protein())
        emit proteinChanged(afterData.protein());
    if (beforeData.fatUnits() < afterData.fatUnits())
        emit fatUnitsChanged(afterData.fatUnits());
    if (beforeData.rankWeight() < afterData.rankWeight())
        emit rankWeightChanged(afterData.rankWeight());
    if (beforeData.paymentWithOutPremium() < afterData.paymentWithOutPremium())
        emit paymentWithOutPremiumChanged(afterData.paymentWithOutPremium());
    if (beforeData.premiumForFat() < afterData.premiumForFat())
        emit premiumForFatChanged(afterData.premiumForFat());
    if (beforeData.sum() < afterData.sum())
        emit sumChanged(afterData.sum());
}

QQmlListProperty<CalculatedItem> CalculatedItem::items()
{
    return QQmlListProperty<CalculatedItem>(this, this,
                                           &CalculatedItem::appendItem,
                                           &CalculatedItem::itemsCount,
                                           &CalculatedItem::item,
                                           &CalculatedItem::clearItems);
}

void CalculatedItem::appendItem(QQmlListProperty<CalculatedItem> *list, CalculatedItem *item)
{
    reinterpret_cast< CalculatedItem* >(list->data)->addItem(item);
}

int CalculatedItem::itemsCount(QQmlListProperty<CalculatedItem> *list)
{
    return reinterpret_cast< CalculatedItem* >(list->data)->itemsCount();
}

CalculatedItem *CalculatedItem::item(QQmlListProperty<CalculatedItem> *list, int position)
{
    return reinterpret_cast< CalculatedItem* >(list->data)->item(position);
}

void CalculatedItem::clearItems(QQmlListProperty<CalculatedItem> *list)
{
    reinterpret_cast< CalculatedItem* >(list->data)->clearItems();
}
