#ifndef DELIVERER_H
#define DELIVERER_H

#include "delivererdata.h"
#include "tables/localities/Locality.h"

DB_BEGIN_NAMESPACE

class Deliverer {
public:
    Deliverer();
    Deliverer(const milk_id id, const QString &name, const milk_inn inn, const QString &address,
              const QString &phoneNumber, const Locality &locality = Locality());
    Deliverer(const Deliverer &deliverer);

    milk_id id() const;
    void setId(const milk_id &id);

    Locality locality() const;
    void setLocality(const Locality &locality);

    QString name() const;
    void setName(const QString &name);

    milk_inn inn() const;
    void setInn(const milk_inn &inn);

    QString address() const;
    void setAddress(const QString &address);

    QString phoneNumber() const;
    void setPhoneNumber(const QString &phoneNumber);

    bool isValid() const;
    // bool save(DeliverersTable *deliverers);

    DelivererData data() const;

private:
    DelivererData m_data;
    Locality m_locality;
};

DB_END_NAMESPACE

#endif // DELIVERER_H
