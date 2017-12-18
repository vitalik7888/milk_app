#ifndef DELIVERER_H
#define DELIVERER_H

#include "DelivererData.h"
// Qt
#include <QQmlListProperty>

class Locality;
class MilkReception;

using DelivererMilkReceptions = QList<MilkReception *>;


class TYPESLIBRARYSHARED_EXPORT Deliverer : public QObject, public IDeliverer
{
    Q_OBJECT
    Q_PROPERTY(int delivererId READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(Locality *locality READ locality WRITE setLocality NOTIFY localityChanged)
    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName NOTIFY firstNameChanged)
    Q_PROPERTY(QString lastName READ lastName WRITE setLastName NOTIFY lastNameChanged)
    Q_PROPERTY(QString fullName READ fullName NOTIFY fullNameChanged)
    Q_PROPERTY(QString inn READ inn WRITE setInn NOTIFY innChanged)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(QString phoneNumber READ phoneNumber WRITE setPhoneNumber NOTIFY phoneNumberChanged)
    Q_PROPERTY(QQmlListProperty<MilkReception> milkReceptions READ milkReceptions)

public:
    Deliverer(QObject *parent = Q_NULLPTR);
    Deliverer(const Deliverer &deliverer);
    Deliverer(const int id, const QString &firstName, const QString &lastName, const QString &inn,
              const QString &address, const QString &phoneNumber,
              Locality *locality = Q_NULLPTR, QObject *parent = Q_NULLPTR);
    virtual ~Deliverer();

    int id() const Q_DECL_OVERRIDE;
    Locality *locality() const;
    QString firstName() const Q_DECL_OVERRIDE;
    QString lastName() const Q_DECL_OVERRIDE;
    QString fullName() const Q_DECL_OVERRIDE;
    QString inn() const Q_DECL_OVERRIDE;
    QString address() const Q_DECL_OVERRIDE;
    QString phoneNumber() const Q_DECL_OVERRIDE;
    Q_INVOKABLE bool isValid() const Q_DECL_OVERRIDE;

    QQmlListProperty<MilkReception> milkReceptions();
    DelivererMilkReceptions getMilkReceptions() const;
    MilkReception *milkReception(int pos) const;
    int milkReceprionsCount() const;
    Q_INVOKABLE bool isHasMilkReceptions() const;

    DelivererData data() const;

public slots:
    void setId(const int id);
    void setLocality(Locality *locality);
    void setFirstName(const QString &firstName);
    void setLastName(const QString &lastName);
    void setInn(const QString &inn);
    void setAddress(const QString &address);
    void setPhoneNumber(const QString &phoneNumber);
    void reset();

signals:
    void idChanged(int delivererId);
    void localityChanged(Locality * locality);
    void firstNameChanged(QString name);
    void lastNameChanged(QString name);
    void fullNameChanged(QString fullName);
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

    virtual int localityId() const Q_DECL_OVERRIDE;
    virtual void setLocalityId(const int localityId) Q_DECL_OVERRIDE;
    QString m_fullName;
};

Q_DECLARE_METATYPE(Deliverer)

#endif // DELIVERER_H
