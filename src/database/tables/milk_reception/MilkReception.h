#ifndef MILKRECEPTION_H
#define MILKRECEPTION_H

#include "milkreceptiondata.h"
#include "tables/deliverers/Deliverer.h"
#include "tables/milk_points/MilkPoint.h"
// Qt
#include <QDate>

DB_BEGIN_NAMESPACE


class MilkReception {
public:
    MilkReception();
    MilkReception(const milk_id id, const Deliverer &deliverer, const MilkPoint &milkPoint,
                  const QDate deliveryDate, const float priceLiter, const float liters, const float fat);
    MilkReception(const MilkReception &milkReception);
    ~MilkReception();

    milk_id id() const;
    void setId(const milk_id &id);

    QDate deliveryDate() const;
    void setDeliveryDate(const QDate &deliveryDate);

    float priceLiter() const;
    void setPriceLiter(float priceLiter);

    float liters() const;
    void setLiters(float liters);

    float fat() const;
    void setFat(float fat);

    bool isValid() const;

    Deliverer deliverer() const;
    void setDeliverer(const Deliverer &deliverer);

    MilkPoint milkPoint() const;
    void setMilkPoint(const MilkPoint &milkPoint);

    MilkReceptionData data() const;

private:
    MilkReceptionData m_data;
    Deliverer m_deliverer;
    MilkPoint m_milkPoint;
};

DB_END_NAMESPACE

#endif // MILKRECEPTION_H
