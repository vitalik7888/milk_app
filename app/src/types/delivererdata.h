#ifndef DELIVERERDATA_H
#define DELIVERERDATA_H

#include "TypesConstants.h"
// Qt
#include <QString>

class DelivererData
{
public:
    DelivererData();
    DelivererData(const TypesConstants::milk_id id, const QString &name, const TypesConstants::milk_id localityId, const TypesConstants::milk_inn inn,
              const QString &address, const QString &phoneNumber);
    virtual ~DelivererData();

    bool isValid() const;

    TypesConstants::milk_inn inn() const;
    void setInn(const TypesConstants::milk_inn inn);

    TypesConstants::milk_id id() const;
    void setId(const TypesConstants::milk_id &id);

    TypesConstants::milk_id localityId() const;
    void setLocalityId(const TypesConstants::milk_id &localityId);

    QString name() const;
    void setName(const QString &name);

    QString address() const;
    void setAddress(const QString &address);

    QString phoneNumber() const;
    void setPhoneNumber(const QString &phoneNumber);

private:
    TypesConstants::milk_inn m_inn;
    TypesConstants::milk_id m_id;
    TypesConstants::milk_id m_localityId;
    QString m_name;
    QString m_address;
    QString m_phoneNumber; // +9(999)999-99-99
};

QDebug operator<<(QDebug dbg, const DelivererData &data);

#endif // DELIVERERDATA_H
