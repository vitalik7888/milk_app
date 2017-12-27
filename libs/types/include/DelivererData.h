#ifndef _DELIVERER_DATA_H
#define _DELIVERER_DATA_H

#include "MilkBaseItem.h"
// Qt
#include <QSharedData>
#include <QMetaType>

class TYPESLIBRARYSHARED_EXPORT DelivererData : public MilkBaseItem, public QSharedData
{
public:
    DelivererData();
    DelivererData(const DelivererData &other);
    DelivererData(const MILK_ID id, const QString &firstName, const QString &lastName,
                  const MILK_ID localityId, const QString &inn, const QString &address,
                  const QString &phoneNumber);

    bool isValid() const Q_DECL_OVERRIDE;
    void reset() Q_DECL_OVERRIDE;

    MILK_ID milkId() const Q_DECL_OVERRIDE { return m_milkId; }
    void setMilkId(const MILK_ID id) Q_DECL_OVERRIDE;

    QString firstName() const { return m_firstName; }
    void setFirstName(const QString &firstName);

    QString lastName() const { return m_lastName; }
    void setLastName(const QString &lastName);
    QString fullName() const;

    QString inn() const { return m_inn; }
    void setInn(const QString &inn);

    MILK_ID localityId() const { return m_localityId; }
    void setLocalityId(const MILK_ID localityId);

    QString address() const { return m_address; }
    void setAddress(const QString &address);

    QString phoneNumber() const { return m_phoneNumber; }
    void setPhoneNumber(const QString &phoneNumber);

private:
    MILK_ID m_milkId;
    MILK_ID m_localityId;
    QString m_inn;
    QString m_firstName;
    QString m_lastName;
    QString m_address;
    QString m_phoneNumber;
};

QDebug operator<<(QDebug dbg, const DelivererData &data);

Q_DECLARE_METATYPE(DelivererData)

#endif // DELIVERER_H
