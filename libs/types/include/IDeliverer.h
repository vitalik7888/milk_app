#ifndef IDELIVERER_H
#define IDELIVERER_H

#include "IMilkBaseType.h"


class TYPESLIBRARYSHARED_EXPORT IDeliverer : public IMilkBaseType
{
public:
    virtual QString firstName() const = 0;
    virtual void setFirstName(const QString &firstName) = 0;

    virtual QString lastName() const = 0;
    virtual void setLastName(const QString &lastName) = 0;

    virtual QString fullName() const = 0;

    virtual QString inn() const = 0;
    virtual void setInn(const QString &inn) = 0;

    virtual int localityId() const = 0;
    virtual void setLocalityId(const int localityId) = 0;

    virtual QString address() const = 0;
    virtual void setAddress(const QString &address) = 0;

    virtual QString phoneNumber() const = 0;
    virtual void setPhoneNumber(const QString &phoneNumber) = 0;
};

#define IDeliverer_iid "com.milk.IDeliverer"

#endif // IDELIVERER_H
