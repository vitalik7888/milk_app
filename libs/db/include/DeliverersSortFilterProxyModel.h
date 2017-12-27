#ifndef DELIVERERSSORTFILTERPROXYMODEL_H
#define DELIVERERSSORTFILTERPROXYMODEL_H

#include "MilkSortFilterProxyModel.h"
#include "Deliverer.h"

DB_BEGIN_NAMESPACE


class DBLIBRARYSHARED_EXPORT DeliverersSortFilterProxyModel : public MilkSortFilterProxyModel
{
    using base = MilkSortFilterProxyModel;
    Q_OBJECT
    Q_PROPERTY(MILK_ID localityId READ localityId WRITE setLocalityId NOTIFY localityIdChanged)
    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName NOTIFY firstNameChanged)
    Q_PROPERTY(QString lastName READ lastName WRITE setLastName NOTIFY lastNameChanged)
    Q_PROPERTY(QString inn READ inn WRITE setInn NOTIFY innChanged)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(QString phoneNumber READ phoneNumber WRITE setPhoneNumber NOTIFY phoneNumberChanged)

public:
    DeliverersSortFilterProxyModel(QObject *parent = Q_NULLPTR);

    QString firstName() const;
    QString lastName() const;
    QString inn() const;
    MILK_ID localityId() const;
    QString address() const;
    QString phoneNumber() const;

public slots:
    void setFirstName(const QString &firstName);
    void setLastName(const QString &lastName);
    void setInn(const QString &inn);
    void setLocalityId(const MILK_ID localityId);
    void setAddress(const QString &address);
    void setPhoneNumber(const QString &phoneNumber);
    void resetFilter();

signals:
    void localityIdChanged(const MILK_ID milkId);
    void firstNameChanged(const QString &firstName);
    void lastNameChanged(const QString &lastName);
    void innChanged(const QString &inn);
    void addressChanged(const QString &address);
    void phoneNumberChanged(const QString &phoneNumber);

protected:
    virtual bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const Q_DECL_OVERRIDE;
    virtual bool lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const Q_DECL_OVERRIDE;

private:
    DelivererData *filter() const;
};

DB_END_NAMESPACE

#endif // DELIVERERSSORTFILTERPROXYMODEL_H
