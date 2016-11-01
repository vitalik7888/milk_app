#ifndef MILKRECEPTION_H
#define MILKRECEPTION_H

#include <tables/milk_reception/milkreceptiondata.h>
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
    MilkReception(const milk_id id, const QDate deliveryDate, const float priceLiter,
                  const float liters, const float fat,
                  const WpDeliverer &deliverer = WpDeliverer(),
                  const WpMilkPoint &milkPoint = WpMilkPoint());
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

    WpDeliverer deliverer() const;
    void setDeliverer(const WpDeliverer deliverer);

    WpMilkPoint milkPoint() const;
    void setMilkPoint(const WpMilkPoint milkPoint);

    DB_NAMESPACE::MilkReceptionData data() const;

private:
    DB_NAMESPACE::MilkReceptionData m_data;
    WpDeliverer m_deliverer;
    WpMilkPoint m_milkPoint;
};

#endif // MILKRECEPTION_H
