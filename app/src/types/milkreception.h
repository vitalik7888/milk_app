#ifndef MILKRECEPTION_H
#define MILKRECEPTION_H

#include "calculateditem.h"
#include "milkreceptiondata.h"
// Qt
#include <QDate>

class MilkPoint;
class Deliverer;

class MilkReception : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qlonglong milkReceptionId READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QDate deliveryDate READ deliveryDate WRITE setDeliveryDate NOTIFY deliveryDateChanged)
    Q_PROPERTY(double priceLiter READ priceLiter WRITE setPriceLiter NOTIFY priceLiterChanged)
    Q_PROPERTY(double liters READ liters WRITE setLiters NOTIFY litersChanged)
    Q_PROPERTY(double fat READ fat WRITE setFat NOTIFY fatChanged)
    Q_PROPERTY(Deliverer *deliverer READ deliverer WRITE setDeliverer NOTIFY delivererChanged)
    Q_PROPERTY(MilkPoint *milkPoint READ milkPoint WRITE setMilkPoint NOTIFY milkPointChanged)

public:
    MilkReception(const milk_id id, const QDate deliveryDate, const double priceLiter,
                  const double liters, const double fat, Deliverer *deliverer = Q_NULLPTR,
                  MilkPoint *milkPoint = Q_NULLPTR, QObject *parent = Q_NULLPTR);
    MilkReception(QObject *parent = Q_NULLPTR);
    virtual ~MilkReception();

    milk_id id() const;
    QDate deliveryDate() const;
    double priceLiter() const;
    double liters() const;
    double fat() const;
    Deliverer *deliverer() const;
    MilkPoint *milkPoint() const;
    MilkReceptionData data() const;

    CalculatedItem::Data getCalculationsData() const;
    Q_INVOKABLE CalculatedItem *getCalculations();

    Q_INVOKABLE bool isValid() const;

public slots:
    void setId(const milk_id &id);
    void setDeliveryDate(const QDate &deliveryDate);
    void setPriceLiter(double priceLiter);
    void setLiters(double liters);
    void setFat(double fat);
    void setDeliverer(Deliverer *deliverer);
    void setMilkPoint(MilkPoint *milkPoint);

signals:
    void idChanged(qlonglong milkReceptionId);
    void deliveryDateChanged(QDate deliveryDate);
    void priceLiterChanged(double priceLiter);
    void litersChanged(double liters);
    void fatChanged(double fat);
    void delivererChanged(Deliverer * deliverer);
    void milkPointChanged(MilkPoint * milkPoint);

private:
    MilkReceptionData m_data;
    Deliverer *m_deliverer;
    MilkPoint *m_milkPoint;
};

#endif // MILKRECEPTION_H
