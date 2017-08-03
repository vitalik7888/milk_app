#ifndef MILKRECEPTION_H
#define MILKRECEPTION_H

#include "calculateditem.h"
#include <tables/milk_reception/milkreceptiondata.h>
#include <src/core/Constants.h>
// Qt
#include <QDate>
#include <QWeakPointer>

class MilkPoint;
class Deliverer;

using WpDeliverer = QWeakPointer<Deliverer>;
using WpMilkPoint = QWeakPointer<MilkPoint>;


class MilkReception {
public:
    MilkReception();
    MilkReception(const milk_id id, const QDate deliveryDate, const price priceLiter,
                  const double liters, const double fat,
                  const WpDeliverer &deliverer = WpDeliverer(),
                  const WpMilkPoint &milkPoint = WpMilkPoint());
    MilkReception(const MilkReception &milkReception);
    ~MilkReception();

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

    WpDeliverer deliverer() const;
    void setDeliverer(const WpDeliverer deliverer);

    WpMilkPoint milkPoint() const;
    void setMilkPoint(const WpMilkPoint milkPoint);

    DB_NAMESPACE::MilkReceptionData data() const;

    CalculatedItem getCalculations() const;

    bool isValid() const;

private:
    DB_NAMESPACE::MilkReceptionData m_data;
    WpDeliverer m_deliverer;
    WpMilkPoint m_milkPoint;
};

#endif // MILKRECEPTION_H
