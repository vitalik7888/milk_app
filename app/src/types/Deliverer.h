#ifndef DELIVERER_H
#define DELIVERER_H

#include "DelivererData.h"
// Qt
#include <QQmlListProperty>

class Locality;
class MilkReception;

using DelivererMilkReceptions = QList<MilkReception *>;


class Deliverer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int delivererId READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(Locality *locality READ locality WRITE setLocality NOTIFY localityChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString inn READ inn WRITE setInn NOTIFY innChanged)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(QString phoneNumber READ phoneNumber WRITE setPhoneNumber NOTIFY phoneNumberChanged)
    Q_PROPERTY(QQmlListProperty<MilkReception> milkReceptions READ milkReceptions)

public:
    Deliverer(QObject *parent = Q_NULLPTR);
    Deliverer(const Deliverer &deliverer);
    Deliverer(const int id, const QString &name, const QString &inn,
              const QString &address, const QString &phoneNumber,
              Locality *locality = Q_NULLPTR, QObject *parent = Q_NULLPTR);
    virtual ~Deliverer();

    int id() const;
    Locality *locality() const;
    QString name() const;
    QString inn() const;
    QString address() const;
    QString phoneNumber() const;

    QQmlListProperty<MilkReception> milkReceptions();
    DelivererMilkReceptions getMilkReceptions() const;
    MilkReception *milkReception(int pos) const;
    int milkReceprionsCount() const;
    Q_INVOKABLE bool isHasMilkReceptions() const;

    Q_INVOKABLE bool isValid() const;

    DelivererData data() const;

public slots:
    void setId(const int id);
    void setLocality(Locality *locality);
    void setName(const QString &name);
    void setInn(const QString &inn);
    void setAddress(const QString &address);
    void setPhoneNumber(const QString &phoneNumber);
    void reset();

signals:
    void idChanged(int delivererId);
    void localityChanged(Locality * locality);
    void nameChanged(QString name);
    void innChanged(QString inn);
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

Q_DECLARE_METATYPE(Deliverer)

#endif // DELIVERER_H
