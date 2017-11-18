#ifndef DELIVERER_H
#define DELIVERER_H

#include "delivererdata.h"
// Qt
#include <QQmlListProperty>

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
    Deliverer(const TypesConstants::milk_id id, const QString &name, const TypesConstants::milk_inn inn,
              const QString &address, const QString &phoneNumber,
              Locality *locality = Q_NULLPTR, QObject *parent = Q_NULLPTR);
    virtual ~Deliverer();

    TypesConstants::milk_id id() const;
    Locality *locality() const;
    QString name() const;
    TypesConstants::milk_inn inn() const;
    QString address() const;
    QString phoneNumber() const;

    QQmlListProperty<MilkReception> milkReceptions();
    MilkReception *milkReception(int pos) const;
    int milkReceprionsCount() const;
    Q_INVOKABLE bool isHasMilkReceptions() const;

    Q_INVOKABLE bool isValid() const;

    DelivererData data() const;

public slots:
    void setId(const TypesConstants::milk_id &id);
    void setLocality(Locality *locality);
    void setName(const QString &name);
    void setInn(const TypesConstants::milk_inn &inn);
    void setAddress(const QString &address);
    void setPhoneNumber(const QString &phoneNumber);
    void reset();

signals:
    void idChanged(qlonglong delivererId);
    void localityChanged(Locality * locality);
    void nameChanged(QString name);
    void innChanged(qlonglong inn);
    void addressChanged(QString address);
    void phoneNumberChanged(QString phoneNumber);

private:
    DelivererData m_data;
    Locality *m_locality;
    DelivererMilkReceptions m_milkReceptions;

    void appendMilkReception(MilkReception *milkReception);
    void clearMilkReceptions();
    static void appendMilkReception(QQmlListProperty<MilkReception> *, MilkReception *);
    static int milkReceprionsCount(QQmlListProperty<MilkReception> *);
    static MilkReception *milkReception(QQmlListProperty<MilkReception> *, int);
    static void clearMilkReceptions(QQmlListProperty<MilkReception> *);
};

#endif // DELIVERER_H
