#ifndef MILKRECEPTION_H
#define MILKRECEPTION_H

#include "MilkReceptionData.h"
// Qt
#include <QObject>
#include <QDate>

class MilkPoint;
class Deliverer;

class TYPESLIBRARYSHARED_EXPORT MilkReception : public QObject, public IMilkReception
{
    Q_OBJECT
    Q_PROPERTY(int milkReceptionId READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QDate deliveryDate READ deliveryDate WRITE setDeliveryDate NOTIFY deliveryDateChanged)
    Q_PROPERTY(double priceLiter READ priceLiter WRITE setPriceLiter NOTIFY priceLiterChanged)
    Q_PROPERTY(double liters READ liters WRITE setLiters NOTIFY litersChanged)
    Q_PROPERTY(double fat READ fat WRITE setFat NOTIFY fatChanged)
    Q_PROPERTY(Deliverer *deliverer READ deliverer WRITE setDeliverer NOTIFY delivererChanged)
    Q_PROPERTY(MilkPoint *milkPoint READ milkPoint WRITE setMilkPoint NOTIFY milkPointChanged)

public:
    MilkReception(const int id, const QDate deliveryDate, const double priceLiter,
                  const double liters, const double fat, Deliverer *deliverer = Q_NULLPTR,
                  MilkPoint *milkPoint = Q_NULLPTR, QObject *parent = Q_NULLPTR);
    MilkReception(const MilkReception &mr);
    MilkReception(QObject *parent = Q_NULLPTR);

    int id() const Q_DECL_OVERRIDE;
    QDate deliveryDate() const Q_DECL_OVERRIDE;
    double priceLiter() const Q_DECL_OVERRIDE;
    double liters() const Q_DECL_OVERRIDE;
    double fat() const Q_DECL_OVERRIDE;
    Deliverer *deliverer() const;
    MilkPoint *milkPoint() const;
    MilkReceptionData data() const;
    Q_INVOKABLE bool isValid() const Q_DECL_OVERRIDE;

public slots:
    void setId(const int id);
    void setDeliveryDate(const QDate &deliveryDate);
    void setPriceLiter(double priceLiter);
    void setLiters(double liters);
    void setFat(double fat);
    void setDeliverer(Deliverer *deliverer);
    void setMilkPoint(MilkPoint *milkPoint);
    void reset();

signals:
    void idChanged(int milkReceptionId);
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

    virtual int delivererId() const Q_DECL_OVERRIDE;
    virtual void setDelivererId(const int delivererId) Q_DECL_OVERRIDE;
    virtual int milkPointId() const Q_DECL_OVERRIDE;
    virtual void setMilkPointId(const int milkPointId) Q_DECL_OVERRIDE;
};

Q_DECLARE_METATYPE(MilkReception)

#endif // MILKRECEPTION_H
