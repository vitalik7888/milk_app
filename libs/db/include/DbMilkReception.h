#ifndef DB_MILK_RECEPTION_H
#define DB_MILK_RECEPTION_H

#include "DbDeliverer.h"
#include "DbMilkPoint.h"
#include "MilkReceptionModel.h"
// Qt
#include <QDate>


class MilkReception;

DB_BEGIN_NAMESPACE


class DBLIBRARYSHARED_EXPORT DbMilkReception : public MilkBaseDbObject
{
    using base = MilkBaseDbObject;
    Q_OBJECT
    Q_PROPERTY(DbDeliverer* deliverer READ deliverer CONSTANT)
    Q_PROPERTY(DbMilkPoint* milkPoint READ milkPoint CONSTANT)
    Q_PROPERTY(QDate deliveryDate READ deliveryDate WRITE setDeliveryDate NOTIFY deliveryDateChanged)
    Q_PROPERTY(double priceLiter READ priceLiter WRITE setPriceLiter NOTIFY priceLiterChanged)
    Q_PROPERTY(double liters READ liters WRITE setLiters NOTIFY litersChanged)
    Q_PROPERTY(double fat READ fat WRITE setFat NOTIFY fatChanged)

public:
    DbMilkReception(QObject *parent = Q_NULLPTR);

    DbMilkPoint *milkPoint() const;
    DbDeliverer *deliverer() const;
    QDate deliveryDate() const;
    double priceLiter() const;
    double liters() const;
    double fat() const;

signals:
    void delivererIdChanged(const MILK_ID delivererId);
    void milkPointIdChanged(const MILK_ID milkPointId);
    void deliveryDateChanged(const QDate &deliveryDate);
    void priceLiterChanged(const double priceLiter);
    void litersChanged(const double liters);
    void fatChanged(const double fat);

public slots:
    void setItem(const MilkBaseItem *item) Q_DECL_OVERRIDE;
    void setDeliveryDate(const QDate &deliveryDate);
    void setPriceLiter(const double priceLiter);
    void setLiters(const double liters);
    void setFat(const double fat);
    bool saveDelivererId();
    bool saveMilkPointId();
    bool saveDeliveryDate();
    bool savePriceLiter();
    bool saveLiters();
    bool saveFat();

private:
    DbMilkPoint* m_milkPoint;
    DbDeliverer* m_deliverer;

    MilkReception *milkReception() const;
};

DB_END_NAMESPACE

#endif // DBMILKRECEPTION_H
