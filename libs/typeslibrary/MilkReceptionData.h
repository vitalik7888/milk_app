#ifndef MILKRECEPTIONDATA_H
#define MILKRECEPTIONDATA_H

#include "typeslibrary_global.h"
// Qt
#include <QDate>
#include <QMetaType>


class TYPESLIBRARYSHARED_EXPORT MilkReceptionData
{
public:
    MilkReceptionData();
    MilkReceptionData(const int id, const int delivererId, const int milkPointId,
                      const QDate &deliveryDate, const double priceLiter, const double liters, const double fat);
    MilkReceptionData(const MilkReceptionData &data);
    ~MilkReceptionData();

    int id() const;
    void setId(const int id);

    int delivererId() const;
    void setDelivererId(const int delivererId);

    int milkPointId() const;
    void setMilkPointId(const int milkPointId);

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
    int m_id;
    int m_delivererId;
    int m_milkPointId;
    QDate   m_deliveryDate;
    double   m_priceLiter;
    double   m_liters;
    double   m_fat;
};

Q_DECLARE_METATYPE(MilkReceptionData)

#endif // MILKRECEPTIONDATA_H
