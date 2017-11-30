#ifndef LOCALITIESSORTFILTERPROXYMODEL_H
#define LOCALITIESSORTFILTERPROXYMODEL_H


#include <Locality.h>
#include <base/MilkSortFilterProxyModel.h>


DB_BEGIN_NAMESPACE

class LocalitiesSortFilterProxyModel : public MilkSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(Locality* locality READ locality CONSTANT RESET resetLocality)
    Q_PROPERTY(bool enableLocalityDynamicFilter READ isLocalityDynamicFilterEnabled WRITE setLocalityDynamicFilter NOTIFY localityDynamicFilterChanged)

public:
    LocalitiesSortFilterProxyModel(QObject *parent = Q_NULLPTR);

    Locality* locality() const { return m_locality; }
    bool isLocalityDynamicFilterEnabled() const { return m_isLocalityDynamicFilterEnabled; }

public slots:
    void invalidateTheFilter();
    void resetLocality();
    void setLocalityDynamicFilter(bool isEnable);

signals:
    void localityDynamicFilterChanged(bool isEnabled);

protected:
    virtual bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const Q_DECL_OVERRIDE;
    virtual bool lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const Q_DECL_OVERRIDE;

private:
    Locality* m_locality;
    bool m_isLocalityDynamicFilterEnabled;

    void localityConnect();
    void localityDisconnect();

    LocalityData getLocalityFromSourceModel(int sourceRow, const QModelIndex &sourceParent) const;

    bool isFilterAcceptRowById(const int id) const;
    bool isFilterAcceptRowByName(const QString &name) const;
    bool isFilterAcceptRowByDescription(const QString &description) const;
    bool isFilterAcceptRowByLocality(const LocalityData &data) const;
};

DB_END_NAMESPACE

#endif // LOCALITIESSORTFILTERPROXYMODEL_H
