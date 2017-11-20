#ifndef MILKRECEPTIONDATA_H
#define MILKRECEPTIONDATA_H

#include "TypesConstants.h"
// Qt
#include <QDate>
#include <QMetaType>


class MilkReceptionData
{
public:
    MilkReceptionData();
    MilkReceptionData(const TypesConstants::milk_id id, const TypesConstants::milk_id delivererId, const TypesConstants::milk_id milkPointId,
                      const QDate &deliveryDate, const double priceLiter,
                      const double liters, const double fat);
    MilkReceptionData(const MilkReceptionData &data);
    ~MilkReceptionData();

    TypesConstants::milk_id id() const;
    void setId(const TypesConstants::milk_id &id);

    TypesConstants::milk_id delivererId() const;
    void setDelivererId(const TypesConstants::milk_id &delivererId);

    TypesConstants::milk_id milkPointId() const;
    void setMilkPointId(const TypesConstants::milk_id &milkPointId);

    QDate deliveryDate() const;
    void setDeliveryDate(const QDate &deliveryDate);

    double priceLiter() const;
    void setPriceLiter(double priceLiter);

    double liters() const;
    void setLiters(double liters);

    double fat() const;
    void setFat(double fat);

    bool isValid() const;

private:
    TypesConstants::milk_id m_id;
    TypesConstants::milk_id m_delivererId;
    TypesConstants::milk_id m_milkPointId;
    QDate   m_deliveryDate;
    double   m_priceLiter;
    double   m_liters;
    double   m_fat;
};

Q_DECLARE_METATYPE(MilkReceptionData)

#endif // MILKRECEPTIONDATA_H
