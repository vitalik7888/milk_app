#ifndef DELIVERERDATA_H
#define DELIVERERDATA_H

// Qt
#include <QString>
#include <QMetaType>


class DelivererData
{
public:
    DelivererData();
    DelivererData(const DelivererData &data);
    DelivererData(const int id, const QString &name, const int localityId, const QString &inn,
              const QString &address, const QString &phoneNumber);
    virtual ~DelivererData();

    bool isValid() const;

    QString inn() const;
    void setInn(const QString &inn);

    int id() const;
    void setId(const int id);

    int localityId() const;
    void setLocalityId(const int localityId);

    QString name() const;
    void setName(const QString &name);

    QString address() const;
    void setAddress(const QString &address);

    QString phoneNumber() const;
    void setPhoneNumber(const QString &phoneNumber);

private:
    int m_id;
    int m_localityId;
    QString m_inn;
    QString m_name;
    QString m_address;
    QString m_phoneNumber; // +9(999)999-99-99
};

Q_DECLARE_METATYPE(DelivererData)

QDebug operator<<(QDebug dbg, const DelivererData &data);

#endif // DELIVERERDATA_H
