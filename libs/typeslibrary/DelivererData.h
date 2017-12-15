#ifndef DELIVERERDATA_H
#define DELIVERERDATA_H

#include "typeslibrary_global.h"
// Qt
#include <QString>
#include <QMetaType>


class TYPESLIBRARYSHARED_EXPORT DelivererData
{
public:
    DelivererData();
    DelivererData(const DelivererData &data);
    DelivererData(const int id, const QString &firstName, const QString &lastName, const int localityId,
                  const QString &inn, const QString &address, const QString &phoneNumber);
    virtual ~DelivererData();

    bool isValid() const;

    int id() const;
    void setId(const int id);

    QString firstName() const;
    void setFirstName(const QString &firstName);

    QString lastName() const;
    void setLastName(const QString &lastName);

    QString fullName() const;

    QString inn() const;
    void setInn(const QString &inn);

    int localityId() const;
    void setLocalityId(const int localityId);

    QString address() const;
    void setAddress(const QString &address);

    QString phoneNumber() const;
    void setPhoneNumber(const QString &phoneNumber);

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
