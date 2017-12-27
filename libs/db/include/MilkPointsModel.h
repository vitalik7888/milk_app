#ifndef MILKPOINTS_MODEL_H
#define MILKPOINTS_MODEL_H

#include "MilkModel.h"
#include "MilkPointData.h"
#include "LocalitiesModel.h"

DB_BEGIN_NAMESPACE
    class MilkPointDao;
//    class LocalitiesModel;

class DBLIBRARYSHARED_EXPORT MilkPointsModel: public MilkModel
{
    Q_OBJECT
    Q_PROPERTY(LocalitiesModel* localities READ localities CONSTANT)

public:
    MilkPointsModel(QObject *parent = Q_NULLPTR);
    MilkPointsModel(LocalitiesModel *localities, QObject *parent = Q_NULLPTR);

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

    LocalitiesModel *localities() const;

public slots:
    void refresh() Q_DECL_OVERRIDE;

private:
    LocalitiesModel *m_localities;

protected:
    void copyItemValues(MilkBaseItem *left, const MilkBaseItem *right) Q_DECL_OVERRIDE;
    void appendToRepository(const MilkBaseItem *item) Q_DECL_OVERRIDE;

};

DB_END_NAMESPACE

#endif // MILKPOINTS_TABLE_H
