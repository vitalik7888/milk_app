#ifndef DELIVERER_H
#define DELIVERER_H

#include <tables/deliverers/delivererdata.h>
// Qt
#include <QWeakPointer>

class Locality;
class MilkReception;

using WpLocality = QWeakPointer<Locality>;
using WpMilkRecep = QWeakPointer<MilkReception>;
using DelivererMilkReceptions = QList< WpMilkRecep >;


class Deliverer {
public:
    Deliverer();
    Deliverer(const milk_id id, const QString &name, const milk_inn inn, const QString &address,
              const QString &phoneNumber, const WpLocality &locality = WpLocality());
    Deliverer(const Deliverer &deliverer);
    ~Deliverer();

    milk_id id() const;
    void setId(const milk_id &id);

    WpLocality locality() const;
    void setLocality(const WpLocality &locality);

    QString name() const;
    void setName(const QString &name);

    milk_inn inn() const;
    void setInn(const milk_inn &inn);

    QString address() const;
    void setAddress(const QString &address);

    QString phoneNumber() const;
    void setPhoneNumber(const QString &phoneNumber);

    bool isHasMilkReceptions() const;
    DelivererMilkReceptions milkReceptions() const;
    void addMilkReception(const WpMilkRecep &milkReception);


    bool isValid() const;
    // bool save(DeliverersTable *deliverers);

    DB_NAMESPACE::DelivererData data() const;

private:
    DB_NAMESPACE::DelivererData m_data;

    WpLocality m_locality;

    DelivererMilkReceptions m_milkReceptions;
};

#endif // DELIVERER_H
