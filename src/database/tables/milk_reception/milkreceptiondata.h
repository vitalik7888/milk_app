#ifndef MILKRECEPTIONDATA_H
#define MILKRECEPTIONDATA_H

#include "dbconstants.h"
// Qt
#include <QDate>

DB_BEGIN_NAMESPACE


class MilkReceptionData
{
public:
    MilkReceptionData();
    MilkReceptionData(const milk_id id, const milk_id delivererId, const milk_id milkPointId,
                      const QDate &deliveryDate, const float priceLiter,
                      const float liters, const float fat);
    MilkReceptionData(const MilkReceptionData &data);
    ~MilkReceptionData();

    milk_id id() const;
    void setId(const milk_id &id);

    milk_id delivererId() const;
    void setDelivererId(const milk_id &delivererId);

    milk_id milkPointId() const;
    void setMilkPointId(const milk_id &milkPointId);

    QDate deliveryDate() const;
    void setDeliveryDate(const QDate &deliveryDate);

    float priceLiter() const;
    void setPriceLiter(float priceLiter);

    float liters() const;
    void setLiters(float liters);

    float fat() const;
    void setFat(float fat);

    bool isValid() const;

private:
    milk_id m_id;
    milk_id m_delivererId;
    milk_id m_milkPointId;
    QDate   m_deliveryDate;
    float   m_priceLiter;
    float   m_liters;
    float   m_fat;
};

DB_END_NAMESPACE

#endif // MILKRECEPTIONDATA_H
