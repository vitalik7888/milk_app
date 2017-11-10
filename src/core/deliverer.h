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
    Q_PROPERTY(qlonglong f_id READ id WRITE setId)
    Q_PROPERTY(Locality *f_locality READ locality WRITE setLocality)
    Q_PROPERTY(QString f_name READ name WRITE setName)
    Q_PROPERTY(qlonglong inn READ inn WRITE setInn)
    Q_PROPERTY(QString address READ address WRITE setAddress)
    Q_PROPERTY(QString phoneNumber READ phoneNumber WRITE setPhoneNumber)
    Q_PROPERTY(QQmlListProperty<MilkReception> milkReceptions READ milkReceptions)

public:
    Deliverer(QObject *parent = Q_NULLPTR);
    Deliverer(const milk_id id, const QString &name, const milk_inn inn,
              const QString &address, const QString &phoneNumber,
              Locality *locality = Q_NULLPTR, QObject *parent = Q_NULLPTR);
    virtual ~Deliverer();

    milk_id id() const;
    void setId(const milk_id &id);

    Locality *locality() const;
    void setLocality(Locality *locality);

    QString name() const;
    void setName(const QString &name);

    milk_inn inn() const;
    void setInn(const milk_inn &inn);

    QString address() const;
    void setAddress(const QString &address);

    QString phoneNumber() const;
    void setPhoneNumber(const QString &phoneNumber);

    Q_INVOKABLE bool isHasMilkReceptions() const;
    QQmlListProperty<MilkReception> milkReceptions();

    void appendMilkReception(MilkReception *milkReception);
    int milkReceprionsCount() const;
    MilkReception *milkReception(int pos) const;
    void clearMilkReceptions();

    CalculatedItem::Data getCalculations() const;

    Q_INVOKABLE bool isValid() const;
    // bool save(DeliverersTable *deliverers);

    DB_NAMESPACE::DelivererData data() const;

private:
    DB_NAMESPACE::DelivererData m_data;
    static void appendMilkReception(QQmlListProperty<MilkReception> *, MilkReception *);
    static int milkReceprionsCount(QQmlListProperty<MilkReception> *);
    static MilkReception *milkReception(QQmlListProperty<MilkReception> *, int);
    static void clearMilkReceptions(QQmlListProperty<MilkReception> *);

    Locality *m_locality;

    DelivererMilkReceptions m_milkReceptions;
};

#endif // DELIVERER_H
