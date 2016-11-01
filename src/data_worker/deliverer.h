#ifndef DELIVERER_H
#define DELIVERER_H

#include <tables/deliverers/delivererdata.h>
// Qt
#include <QWeakPointer>

class Locality;


class Deliverer {
public:
    Deliverer();
    Deliverer(const milk_id id, const QString &name, const milk_inn inn, const QString &address,
              const QString &phoneNumber, const QWeakPointer<Locality> &locality = QWeakPointer<Locality>());
    Deliverer(const Deliverer &deliverer);
    ~Deliverer();

    milk_id id() const;
    void setId(const milk_id &id);

    QWeakPointer<Locality> locality() const;
    void setLocality(const QWeakPointer<Locality> &locality);

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

    DB_NAMESPACE::DelivererData data() const;

private:
    DB_NAMESPACE::DelivererData m_data;
    QWeakPointer<Locality> m_locality;
};

#endif // DELIVERER_H
