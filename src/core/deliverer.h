#ifndef DELIVERER_H
#define DELIVERER_H

#include "delivererdata.h"
#include "calculateditem.h"
// Qt
#include <QQmlListProperty>
#include <QWeakPointer>

class Locality;
class MilkReception;

using DelivererMilkReceptions = QList<MilkReception *>;


class Deliverer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qlonglong delivererId READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(Locality *locality READ locality WRITE setLocality NOTIFY localityChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(qlonglong inn READ inn WRITE setInn NOTIFY innChanged)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(QString phoneNumber READ phoneNumber WRITE setPhoneNumber NOTIFY phoneNumberChanged)
    Q_PROPERTY(QQmlListProperty<MilkReception> milkReceptions READ milkReceptions)

public:
    Deliverer(QObject *parent = Q_NULLPTR);
    Deliverer(const milk_id id, const QString &name, const milk_inn inn,
              const QString &address, const QString &phoneNumber,
              Locality *locality = Q_NULLPTR, QObject *parent = Q_NULLPTR);
    virtual ~Deliverer();

    milk_id id() const;
    Locality *locality() const;
    QString name() const;
    milk_inn inn() const;
    QString address() const;
    QString phoneNumber() const;

    QQmlListProperty<MilkReception> milkReceptions();
    MilkReception *milkReception(int pos) const;
    int milkReceprionsCount() const;
    void clearMilkReceptions();
    Q_INVOKABLE bool isHasMilkReceptions() const;

    CalculatedItem::Data getCalculations() const;

    Q_INVOKABLE bool isValid() const;
    // bool save(DeliverersTable *deliverers);

    DB_NAMESPACE::DelivererData data() const;

public slots:
    void setId(const milk_id &id);
    void setLocality(Locality *locality);
    void setName(const QString &name);
    void setInn(const milk_inn &inn);
    void setAddress(const QString &address);
    void setPhoneNumber(const QString &phoneNumber);

signals:
    void idChanged(qlonglong delivererId);
    void localityChanged(Locality * locality);
    void nameChanged(QString name);
    void innChanged(qlonglong inn);
    void addressChanged(QString address);
    void phoneNumberChanged(QString phoneNumber);

private:
    DB_NAMESPACE::DelivererData m_data;
    Locality *m_locality;
    DelivererMilkReceptions m_milkReceptions;

    void appendMilkReception(MilkReception *milkReception);
    static void appendMilkReception(QQmlListProperty<MilkReception> *, MilkReception *);
    static int milkReceprionsCount(QQmlListProperty<MilkReception> *);
    static MilkReception *milkReception(QQmlListProperty<MilkReception> *, int);
    static void clearMilkReceptions(QQmlListProperty<MilkReception> *);
};

#endif // DELIVERER_H
