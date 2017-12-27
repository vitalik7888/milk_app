#ifndef MILKRECEPTION_DATA_H_
#define MILKRECEPTION_DATA_H_

#include "MilkBaseItem.h"
// Qt
#include <QDate>
#include <QSharedData>
#include <QMetaType>


class TYPESLIBRARYSHARED_EXPORT MilkReceptionData : public MilkBaseItem, public QSharedData
{
public:
    MilkReceptionData();
    MilkReceptionData(const MILK_ID id, const MILK_ID delivererId, const MILK_ID milkPointId,
                      const QDate &deliveryDate, const double priceLiter, const double liters,
                      const double fat);
    MilkReceptionData(const MilkReceptionData &data);

    MILK_ID milkId() const Q_DECL_OVERRIDE { return m_milkId; }
    void setMilkId(const MILK_ID milkId) Q_DECL_OVERRIDE;

    MILK_ID delivererId() const { return m_delivererId; }
    void setDelivererId(const MILK_ID delivererId);

    MILK_ID milkPointId() const { return m_milkPointId; }
    void setMilkPointId(const MILK_ID milkPointId);

    QDate deliveryDate() const { return m_deliveryDate; }
    void setDeliveryDate(const QDate &deliveryDate);

    double priceLiter() const { return m_priceLiter; }
    void setPriceLiter(double priceLiter);

    double liters() const { return m_liters; }
    void setLiters(double liters);

    double fat() const { return m_fat; }
    void setFat(double fat);

    virtual bool isValid() const Q_DECL_OVERRIDE;
    virtual void reset() Q_DECL_OVERRIDE;

private:
    MILK_ID m_milkId;
    MILK_ID m_delivererId;
    MILK_ID m_milkPointId;
    QDate  m_deliveryDate;
    double m_priceLiter;
    double m_liters;
    double m_fat;
};

Q_DECLARE_METATYPE(MilkReceptionData)

#endif // MILKRECEPTIONDATA_H
