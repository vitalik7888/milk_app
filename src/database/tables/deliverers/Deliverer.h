#ifndef DELIVERER_H
#define DELIVERER_H

#include "tables/localities/Locality.h"


class Deliverer {
public:
    Deliverer();
    Deliverer(const QString &name, const Locality &locality, const qlonglong inn = 0,
              const QString &address = QString(), const QString &phoneNumber = "+7",
              const qlonglong id = -1);

    qlonglong id() const;
    void setId(const qlonglong &id);

    Locality locality() const;

    QString name() const;
    void setName(const QString &name);

    qlonglong inn() const;
    void setInn(const qlonglong &inn);

    QString address() const;
    void setAddress(const QString &address);

    QString phoneNumber() const;
    void setPhoneNumber(const QString &phoneNumber);

    bool isNull() const;
    // bool save(DeliverersTable *deliverers);
    QString toString() const;

    static Deliverer CREATE_NULL();
private:
    qlonglong _id;
    QString _name;
    Locality _locality;
    qlonglong _inn;
    QString _address;
    QString _phoneNumber; // +9(999)999-99-99
};

#endif // DELIVERER_H
