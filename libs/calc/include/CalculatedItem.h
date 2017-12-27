#ifndef CALCULATEDITEM_H
#define CALCULATEDITEM_H

#include "CalculatedItemData.h"
// Qt
#include <QDate>
#include <QList>
#include <QQmlListProperty>

class MilkReception;


class CALCLIBRARYSHARED_EXPORT CalculatedItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(CalculatedItem* calcParent READ calcParent WRITE setCalcParent NOTIFY parentChanged)
    Q_PROPERTY(QQmlListProperty<CalculatedItem> items READ items)
    Q_PROPERTY(QString delivererFullName READ delivererFullName CONSTANT)
    Q_PROPERTY(QString milkPointName READ milkPointName CONSTANT)
    Q_PROPERTY(QDate deliveryDate READ deliveryDate CONSTANT)
    Q_PROPERTY(double liters READ liters NOTIFY litersChanged)
    Q_PROPERTY(double fat READ fat NOTIFY fatChanged)
    Q_PROPERTY(double priceForLiter READ priceForLiter NOTIFY priceForLiterChanged)
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

    CalculatedItem(const QString &delivererName, const QString &milkPointName, const QDate &deliveryDate,
                   const double liters, const double fat, const double price,
                   CalculatedItem *calcParent = Q_NULLPTR, QObject *objectParent = Q_NULLPTR);
    CalculatedItem(QObject *objectParent = Q_NULLPTR);
    ~CalculatedItem();

    CalculatedItem *calcParent() const { return m_parent; }

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
    double protein() const { return m_itemData.protein(); }
    double priceForLiter() const { return m_itemData.priceForLiter(); }
    double fatUnits() const { return m_itemData.fatUnits(); }
    double rankWeight() const { return m_itemData.rankWeight(); }
    double paymentWithOutPremium() const { return m_itemData.paymentWithOutPremium(); }
    double premiumForFat() const { return m_itemData.premiumForFat(); }
    double sum() const { return m_itemData.sum(); }

    QString delivererFullName() const { return m_delivererFullName; }
    QString milkPointName() const { return m_milkPointName; }
    QDate deliveryDate() const { return m_deliveryDate; }

public slots:
    void setCalcParent(CalculatedItem *calcParent);

signals:
    void parentChanged(CalculatedItem *calcParent);
    void proteinChanged(double protein);
    void litersChanged(double liters);
    void priceForLiterChanged(double priceForLiter);
    void fatChanged(double fat);
    void fatUnitsChanged(double fatUnits);
    void rankWeightChanged(double rankWeight);
    void paymentWithOutPremiumChanged(double paymentWithOutPremium);
    void premiumForFatChanged(double premiumForFat);
    void sumChanged(double sum);

private:
    CalculatedItem *m_parent;
    QString m_delivererFullName;
    QString m_milkPointName;
    QDate m_deliveryDate;
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
