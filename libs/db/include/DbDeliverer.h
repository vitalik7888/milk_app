#ifndef _DB_DELIVERER_H
#define _DB_DELIVERER_H

#include "DbLocality.h"
#include <DeliverersModel.h>
// Qt
#include <QQmlListProperty>

class Deliverer;
DB_BEGIN_NAMESPACE
    class DbMilkReception;

using DelivererMilkReceptions = QList<DbMilkReception *>;

class DBLIBRARYSHARED_EXPORT MilkReceptionRepository
{
public:
    void append(DbMilkReception *milkReception);
    void clear();

    DelivererMilkReceptions getAll() const;
    DbMilkReception *get(const int position) const;
    int count() const;
    bool isEmpty() const;

private:
    DelivererMilkReceptions m_items;
};

class DBLIBRARYSHARED_EXPORT DbDeliverer : public MilkBaseDbObject
{
    using base = MilkBaseDbObject;
    Q_OBJECT
    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName NOTIFY firstNameChanged)
    Q_PROPERTY(QString lastName READ lastName WRITE setLastName NOTIFY lastNameChanged)
    Q_PROPERTY(QString fullName READ fullName NOTIFY fullNameChanged)
    Q_PROPERTY(QString inn READ inn WRITE setInn NOTIFY innChanged)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(QString phoneNumber READ phoneNumber WRITE setPhoneNumber NOTIFY phoneNumberChanged)
    Q_PROPERTY(DbLocality* locality READ locality CONSTANT)
    Q_PROPERTY(QQmlListProperty<DbMilkReception> milkReceptions READ _milkReceptions)

public:
    explicit DbDeliverer(QObject *parent = nullptr);

    QString firstName() const;
    QString lastName() const;
    QString fullName() const;
    QString inn() const;
    QString address() const;
    QString phoneNumber() const;
    DbLocality *locality() const { return m_locality; }
    QQmlListProperty<DbMilkReception> _milkReceptions();

    MilkReceptionRepository repository() { return m_repository; }

signals:
    void firstNameChanged(const QString &firstName);
    void lastNameChanged(const QString &lastName);
    void fullNameChanged(const QString &fullName);
    void innChanged(const QString &inn);
    void addressChanged(const QString &address);
    void phoneNumberChanged(const QString &phoneNumber);

public slots:
    void setItem(const MilkBaseItem *item) Q_DECL_OVERRIDE;
    void setFirstName(const QString &firstName);
    void setLastName(const QString &lastName);
    void setInn(const QString &inn);
    void setAddress(const QString &address);
    void setPhoneNumber(const QString &phoneNumber);
    bool saveMilkId();

private:
    DbLocality* m_locality;
    MilkReceptionRepository m_repository;

    Deliverer *deliverer() const;

    static void _appendMilkReception(QQmlListProperty<DbMilkReception> *list, DbMilkReception *milkReception);
    static int _milkReceprionsCount(QQmlListProperty<DbMilkReception> *list);
    static DbMilkReception *_milkReception(QQmlListProperty<DbMilkReception> *list, const int position);
    static void _clearMilkReceptions(QQmlListProperty<DbMilkReception> *list);
};

DB_END_NAMESPACE

#endif // DBDELIVERER_H
