#ifndef MILKRECEPTION_H
#define MILKRECEPTION_H

#include "calculateditem.h"
#include "milkreceptiondata.h"
#include "src/core/Constants.h"
// Qt
#include <QDate>
#include <QWeakPointer>

class MilkPoint;
class Deliverer;

class MilkReception : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qlonglong f_id READ id WRITE setId)
    Q_PROPERTY(QDate deliveryDate READ deliveryDate WRITE setDeliveryDate)
    Q_PROPERTY(double priceLiter READ priceLiter WRITE setPriceLiter)
    Q_PROPERTY(double liters READ liters WRITE setLiters)
    Q_PROPERTY(double fat READ fat WRITE setFat)
    Q_PROPERTY(Deliverer *deliverer READ deliverer WRITE setDeliverer)
    Q_PROPERTY(MilkPoint *milkPoint READ milkPoint WRITE setMilkPoint)

public:
    MilkReception(const milk_id id, const QDate deliveryDate, const price priceLiter,
                  const double liters, const double fat, Deliverer *deliverer = Q_NULLPTR,
                  MilkPoint *milkPoint = Q_NULLPTR, QObject *parent = Q_NULLPTR);
    MilkReception(QObject *parent = Q_NULLPTR);
    virtual ~MilkReception();

    milk_id id() const;
    void setId(const milk_id &id);

    QDate deliveryDate() const;
    void setDeliveryDate(const QDate &deliveryDate);

    price priceLiter() const;
    void setPriceLiter(price priceLiter);

    double liters() const;
    void setLiters(double liters);

    double fat() const;
    void setFat(double fat);

    Deliverer *deliverer() const;
    void setDeliverer(Deliverer *deliverer);

    MilkPoint *milkPoint() const;
    void setMilkPoint(MilkPoint *milkPoint);

    DB_NAMESPACE::MilkReceptionData data() const;

    CalculatedItem::Data getCalculationsData() const;
    Q_INVOKABLE CalculatedItem *getCalculations();

    Q_INVOKABLE bool isValid() const;

private:
    DB_NAMESPACE::MilkReceptionData m_data;
    Deliverer *m_deliverer;
    MilkPoint *m_milkPoint;
};

#endif // MILKRECEPTION_H
