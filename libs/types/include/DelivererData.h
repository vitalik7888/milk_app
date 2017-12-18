#ifndef DELIVERERDATA_H
#define DELIVERERDATA_H

#include "IDeliverer.h"
// Qt
#include <QString>
#include <QMetaType>


class TYPESLIBRARYSHARED_EXPORT DelivererData : public IDeliverer
{
public:
    DelivererData();
    DelivererData(const DelivererData &data);
    DelivererData(const int id, const QString &firstName, const QString &lastName, const int localityId,
                  const QString &inn, const QString &address, const QString &phoneNumber);
    virtual ~DelivererData();

    bool isValid() const Q_DECL_OVERRIDE;

    int id() const Q_DECL_OVERRIDE;
    void setId(const int id) Q_DECL_OVERRIDE;

    QString firstName() const Q_DECL_OVERRIDE;
    void setFirstName(const QString &firstName) Q_DECL_OVERRIDE;

    QString lastName() const Q_DECL_OVERRIDE;
    void setLastName(const QString &lastName) Q_DECL_OVERRIDE;

    QString fullName() const Q_DECL_OVERRIDE;

    QString inn() const Q_DECL_OVERRIDE;
    void setInn(const QString &inn) Q_DECL_OVERRIDE;

    int localityId() const Q_DECL_OVERRIDE;
    void setLocalityId(const int localityId) Q_DECL_OVERRIDE;

    QString address() const Q_DECL_OVERRIDE;
    void setAddress(const QString &address) Q_DECL_OVERRIDE;

    QString phoneNumber() const Q_DECL_OVERRIDE;
    void setPhoneNumber(const QString &phoneNumber) Q_DECL_OVERRIDE;

private:
    int m_id;
    int m_localityId;
    QString m_inn;
    QString m_firstName;
    QString m_lastName;
    QString m_address;
    QString m_phoneNumber; // +9(999)999-99-99
};

Q_DECLARE_METATYPE(DelivererData)

QDebug operator<<(QDebug dbg, const DelivererData &data);

#endif // DELIVERERDATA_H
