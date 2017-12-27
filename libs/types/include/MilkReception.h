#ifndef _MILKRECEPTION_H_
#define _MILKRECEPTION_H_

#include "MilkReceptionData.h"

class Deliverer;
class MilkPoint;


class TYPESLIBRARYSHARED_EXPORT MilkReception : public MilkBaseItem
{
public:
    MilkReception();
    MilkReception(const MILK_ID id, const QDate &deliveryDate, const double priceLiter,
                  const double liters, const double fat,
                  const Deliverer *deliverer = Q_NULLPTR, const MilkPoint *milkPoint = Q_NULLPTR);
    MilkReception(const MilkReception &other);

    MILK_ID milkId() const Q_DECL_OVERRIDE { return m_data->milkId(); }
    void setMilkId(const MILK_ID milkId) Q_DECL_OVERRIDE;

    const Deliverer *deliverer() const { return m_deliverer; }
    void setDeliverer(const Deliverer *deliverer);

    const MilkPoint *milkPoint() const { return m_milkPoint; }
    void setMilkPoint(const MilkPoint *milkPoint);

    QDate deliveryDate() const { return m_data->deliveryDate(); }
    void setDeliveryDate(const QDate &deliveryDate);

    double priceLiter() const { return m_data->priceLiter(); }
    void setPriceLiter(double priceLiter);

    double liters() const { return m_data->liters(); }
    void setLiters(double liters);

    double fat() const { return m_data->fat(); }
    void setFat(double fat);

    virtual bool isValid() const Q_DECL_OVERRIDE;
    virtual void reset() Q_DECL_OVERRIDE;

private:
    QSharedDataPointer<MilkReceptionData> m_data;

    const Deliverer *m_deliverer;
    const MilkPoint *m_milkPoint;
};

Q_DECLARE_METATYPE(MilkReception)

#endif // MILKRECEPTION_H
