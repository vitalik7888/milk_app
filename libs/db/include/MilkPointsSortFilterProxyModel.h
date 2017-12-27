#ifndef MILKPOINTSSORTFILTERPROXYMODEL_H
#define MILKPOINTSSORTFILTERPROXYMODEL_H


#include "MilkPointData.h"
#include "MilkSortFilterProxyModel.h"

DB_BEGIN_NAMESPACE


class DBLIBRARYSHARED_EXPORT MilkPointsSortFilterProxyModel : public MilkSortFilterProxyModel
{
    using base = MilkSortFilterProxyModel;
    Q_OBJECT
    Q_PROPERTY(MILK_ID localityId READ localityId WRITE setLocalityId NOTIFY localityIdChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)

public:
    explicit MilkPointsSortFilterProxyModel(QObject *parent = nullptr);

    QString name() const;
    QString description();
    MILK_ID localityId() const;

public slots:
    void setName(const QString &name);
    void setDescription(const QString &description);
    void setLocalityId(const MILK_ID localityId);
    void resetFilter() Q_DECL_OVERRIDE;

signals:
    void nameChanged(const QString &name);
    void descriptionChanged(QString description);
    void localityIdChanged(const MILK_ID localityId);

protected:
    virtual bool filterAcceptsRow(int source_row, const QModelIndex &sourceParent) const Q_DECL_OVERRIDE;
    virtual bool lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const Q_DECL_OVERRIDE;

    MilkPointData *filter() const;
};

DB_END_NAMESPACE

#endif // MILKPOINTSSORTFILTERPROXYMODEL_H
