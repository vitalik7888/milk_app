#ifndef LOCALITIESSORTFILTERPROXYMODEL_H
#define LOCALITIESSORTFILTERPROXYMODEL_H


#include "MilkSortFilterProxyModel.h"

class Locality;

DB_BEGIN_NAMESPACE

class DBLIBRARYSHARED_EXPORT LocalitiesSortFilterProxyModel : public MilkSortFilterProxyModel
{
    using base = MilkSortFilterProxyModel;
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)

public:
    LocalitiesSortFilterProxyModel(QObject *parent = Q_NULLPTR);

    QString name() const;
    QString description();

public slots:
    void setName(const QString &name);
    void setDescription(const QString &description);
    void resetFilter() Q_DECL_OVERRIDE;

signals:
    void nameChanged(const QString &name);
    void descriptionChanged(QString description);

protected:
    virtual bool filterAcceptsRow(int source_row, const QModelIndex &sourceParent) const Q_DECL_OVERRIDE;
    virtual bool lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const Q_DECL_OVERRIDE;

private:
    Locality *filter() const;
};

DB_END_NAMESPACE

#endif // LOCALITIESSORTFILTERPROXYMODEL_H
