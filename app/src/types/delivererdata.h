#ifndef DELIVERERDATA_H
#define DELIVERERDATA_H

#include "dbconstants.h"
// Qt
#include <QString>

class DelivererData
{
public:
    DelivererData();
    DelivererData(const milk_id id, const QString &name, const milk_id localityId, const milk_inn inn,
              const QString &address, const QString &phoneNumber);
    virtual ~DelivererData();

    bool isValid() const;

    milk_inn inn() const;
    void setInn(const milk_inn inn);

    milk_id id() const;
    void setId(const milk_id &id);

    milk_id localityId() const;
    void setLocalityId(const milk_id &localityId);

    QString name() const;
    void setName(const QString &name);

    QString address() const;
    void setAddress(const QString &address);

    QString phoneNumber() const;
    void setPhoneNumber(const QString &phoneNumber);

private:
    milk_inn m_inn;
    milk_id m_id;
    milk_id m_localityId;
    QString m_name;
    QString m_address;
    QString m_phoneNumber; // +9(999)999-99-99
};

QDebug operator<<(QDebug dbg, const DelivererData &data);

#endif // DELIVERERDATA_H
