#ifndef MILKRECEPTIONDATA_H
#define MILKRECEPTIONDATA_H

#include "IMilkReception.h"
// Qt
#include <QMetaType>


class TYPESLIBRARYSHARED_EXPORT MilkReceptionData : public IMilkReception
{
public:
    MilkReceptionData();
    MilkReceptionData(const int id, const int delivererId, const int milkPointId,
                      const QDate &deliveryDate, const double priceLiter, const double liters, const double fat);
    MilkReceptionData(const MilkReceptionData &data);

    int id() const Q_DECL_OVERRIDE;
    void setId(const int id) Q_DECL_OVERRIDE;

    int delivererId() const Q_DECL_OVERRIDE;
    void setDelivererId(const int delivererId) Q_DECL_OVERRIDE;

    int milkPointId() const Q_DECL_OVERRIDE;
    void setMilkPointId(const int milkPointId) Q_DECL_OVERRIDE;

    QDate deliveryDate() const Q_DECL_OVERRIDE;
    void setDeliveryDate(const QDate &deliveryDate) Q_DECL_OVERRIDE;

    double priceLiter() const Q_DECL_OVERRIDE;
    void setPriceLiter(double priceLiter) Q_DECL_OVERRIDE;

    double liters() const Q_DECL_OVERRIDE;
    void setLiters(double liters) Q_DECL_OVERRIDE;

    double fat() const Q_DECL_OVERRIDE;
    void setFat(double fat) Q_DECL_OVERRIDE;

    bool isValid() const Q_DECL_OVERRIDE;

private:
    int m_id;
    int m_delivererId;
    int m_milkPointId;
    QDate  m_deliveryDate;
    double m_priceLiter;
    double m_liters;
    double m_fat;
};

Q_DECLARE_METATYPE(MilkReceptionData)

#endif // MILKRECEPTIONDATA_H
