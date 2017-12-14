#ifndef CALCULATEDITEM_H
#define CALCULATEDITEM_H

#include "CalculatedItemData.h"
// Qt
#include <QDate>
#include <QList>
#include <QQmlListProperty>


class CALCLIBRARYSHARED_EXPORT CalculatedItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(CalculatedItem* parent READ parent WRITE setParent NOTIFY parentChanged)
    Q_PROPERTY(QString delivererName READ delivererName WRITE setDelivererName NOTIFY delivererNameChanged)
    Q_PROPERTY(QDate deliveryDate READ deliveryDate WRITE setDeliveryDate NOTIFY deliveryDateChanged)
    Q_PROPERTY(QString milkPointName READ milkPointName WRITE setMilkPointName NOTIFY milkPointNameChanged)
    Q_PROPERTY(QQmlListProperty<CalculatedItem> items READ items)
    Q_PROPERTY(double liters READ liters NOTIFY litersChanged)
    Q_PROPERTY(double fat READ fat NOTIFY fatChanged)
    Q_PROPERTY(double price READ price NOTIFY priceChanged)
    Q_PROPERTY(double protein READ protein NOTIFY proteinChanged)
    Q_PROPERTY(double fatUnits READ fatUnits NOTIFY fatUnitsChanged)
    Q_PROPERTY(double rankWeight READ rankWeight NOTIFY rankWeightChanged)
    Q_PROPERTY(double paymentWithOutPremium READ paymentWithOutPremium NOTIFY paymentWithOutPremiumChanged)
    Q_PROPERTY(double premiumForFat READ premiumForFat NOTIFY premiumForFatChanged)
    Q_PROPERTY(double sum READ sum NOTIFY sumChanged)

public:
    enum class Columns {
        Name = 0,
        Date,
        MilkPointName,
        Price,
        Liters,
        Fat,
        Protein,
        FatUnits,
        RankWeight,
        PaymentWithOutPremium,
        PremiumForFat,
        Sum,
        ColumnsCount
    };

    using Items = QList<CalculatedItem *>;

    CalculatedItem(const double liters, const double fat, const double priceForLiter,
                   CalculatedItem *parent = Q_NULLPTR, QObject *objectParent = Q_NULLPTR);
    CalculatedItem(QObject *parent = Q_NULLPTR);
    ~CalculatedItem();

    CalculatedItem *parent() const { return m_parent; }
    QString delivererName() const { return m_delivererName; }
    QDate deliveryDate() const { return m_deliveryDate; }
    QString milkPointName() const { return m_milkPointName; }

    QQmlListProperty<CalculatedItem> items();
    Items getItems() const { return m_items; }
    CalculatedItem *item(const int position) const;
    int itemsCount() const;
    void clearItems();

    QVariant data(const Columns column) const;
    int row() const;
    int columnCount() const;

    void addItem(CalculatedItem *item);
    void addItems(const Items &calcItems);
    void setItems(const Items &calcItems);

    CalculatedItemData itemData() const { return m_itemData; }
    double liters() const { return m_itemData.liters(); }
    double fat() const { return m_itemData.fat(); }
    double price() const { return m_itemData.priceForLiter(); }
    double protein() const { return m_itemData.protein(); }
    double fatUnits() const { return m_itemData.fatUnits(); }
    double rankWeight() const { return m_itemData.rankWeight(); }
    double paymentWithOutPremium() const { return m_itemData.paymentWithOutPremium(); }
    double premiumForFat() const { return m_itemData.premiumForFat(); }
    double sum() const { return m_itemData.sum(); }

public slots:
    void setParent(CalculatedItem *parent);
    void setDelivererName(const QString &name);
    void setDeliveryDate(const QDate &deliveryDate);
    void setMilkPointName(const QString &milkPointName);

signals:
    void parentChanged(CalculatedItem *parent);
    void delivererNameChanged(QString delivererName);
    void deliveryDateChanged(QDate deliveryDate);
    void milkPointNameChanged(QString milkPointName);
    void litersChanged(double liters);
    void fatChanged(double fat);
    void priceChanged(double price);
    void proteinChanged(double protein);
    void fatUnitsChanged(double fatUnits);
    void rankWeightChanged(double rankWeight);
    void paymentWithOutPremiumChanged(double paymentWithOutPremium);
    void premiumForFatChanged(double premiumForFat);
    void sumChanged(double sum);

private:
    CalculatedItem *m_parent;
    QString m_delivererName;
    QDate m_deliveryDate;
    QString m_milkPointName;
    CalculatedItemData m_itemData;
    Items m_items;

    void addData(const Items &calcItems);
    void addData(const CalculatedItemData &item);

    void checkItemsData(const CalculatedItemData &beforeData, const CalculatedItemData &afterData);

    static void appendItem(QQmlListProperty<CalculatedItem> *list, CalculatedItem *item);
    static int itemsCount(QQmlListProperty<CalculatedItem>  *list);
    static CalculatedItem *item(QQmlListProperty<CalculatedItem> *list, int position);
    static void clearItems(QQmlListProperty<CalculatedItem> *list);
};

#endif // CALCULATEDITEM_H
