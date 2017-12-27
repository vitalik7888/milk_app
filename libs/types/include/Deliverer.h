#ifndef _DELIVERER_H_
#define _DELIVERER_H_

#include "DelivererData.h"

class Locality;

class TYPESLIBRARYSHARED_EXPORT Deliverer : public MilkBaseItem
{
public:
    Deliverer();
    Deliverer(const Deliverer &other);
    Deliverer(const MILK_ID id, const QString &firstName, const QString &lastName, const QString &inn,
              const QString &address, const QString &phoneNumber, const Locality *locality = Q_NULLPTR);

    MILK_ID milkId() const Q_DECL_OVERRIDE { return m_data->milkId(); }
    void setMilkId(const MILK_ID id) Q_DECL_OVERRIDE;

    QString firstName() const { return m_data->firstName(); }
    void setFirstName(const QString &firstName);

    QString lastName() const { return m_data->lastName(); }
    void setLastName(const QString &lastName);
    QString fullName() const { return m_data->fullName(); }

    QString inn() const { return m_data->inn(); }
    void setInn(const QString &inn);

    const Locality *locality() const { return m_locality; }
    void setLocality(const Locality *locality);

    QString address() const { return m_data->address(); }
    void setAddress(const QString &address);

    QString phoneNumber() const { return m_data->phoneNumber(); }
    void setPhoneNumber(const QString &phoneNumber);

    bool isValid() const Q_DECL_OVERRIDE;
    void reset() Q_DECL_OVERRIDE;

private:
    QSharedDataPointer<DelivererData> m_data;
    const Locality *m_locality;
};

Q_DECLARE_METATYPE(Deliverer)

#endif // DELIVERER_H
