#ifndef MILKRECEPTION_H
#define MILKRECEPTION_H

#include <tables/milk_reception/milkreceptiondata.h>
// Qt
#include <QDate>

class MilkPoint;
class Deliverer;


class MilkReception {
public:
    MilkReception();
    MilkReception(const milk_id id, Deliverer *deliverer, MilkPoint *milkPoint,
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

    Deliverer *deliverer() const;
    void setDeliverer(Deliverer *deliverer);

    MilkPoint *milkPoint() const;
    void setMilkPoint(MilkPoint *milkPoint);

    DB_NAMESPACE::MilkReceptionData data() const;

private:
    DB_NAMESPACE::MilkReceptionData m_data;
    Deliverer *m_deliverer;
    MilkPoint *m_milkPoint;
};

#endif // MILKRECEPTION_H
