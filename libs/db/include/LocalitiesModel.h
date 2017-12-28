#ifndef LOCALITIES_MODEL_H
#define LOCALITIES_MODEL_H

#include "DbConstants.h"
#include "MilkModel.h"
#include "LocalityData.h"

DB_BEGIN_NAMESPACE
    class LocalitiesDao;


class DBLIBRARYSHARED_EXPORT LocalitiesModel : public MilkModel
{
    Q_OBJECT

public:
    LocalitiesModel(QObject *parent = Q_NULLPTR);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

protected:
    void copyItemValues(MilkBaseItem *left, const MilkBaseItem *right) Q_DECL_OVERRIDE;
    void appendToRepository(const MilkBaseItem *item) Q_DECL_OVERRIDE;
};

DB_END_NAMESPACE

#endif
