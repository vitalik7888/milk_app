#ifndef MILKRECEPTION_MODEL_H
#define MILKRECEPTION_MODEL_H

#include "DeliverersModel.h"
#include "MilkPointsModel.h"
#include "MilkReceptionData.h"
// Qt
#include <QDate>

DB_BEGIN_NAMESPACE
class MilkReceptionDao;
//class DeliverersModel;
//class MilkPointsModel;


class DBLIBRARYSHARED_EXPORT MilkReceptionModel : public MilkModel
{
    Q_OBJECT
    Q_PROPERTY(DeliverersModel* deliverers READ deliverers CONSTANT)
    Q_PROPERTY(MilkPointsModel* milkPoints READ milkPoints CONSTANT)

public:
    MilkReceptionModel(QObject *parent = Q_NULLPTR);
    MilkReceptionModel(DeliverersModel *deliverers, MilkPointsModel *milkPoints,
                       QObject *parent = Q_NULLPTR);

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

    DeliverersModel *deliverers() const;
    MilkPointsModel *milkPoints() const;

public slots:
    void refresh() Q_DECL_OVERRIDE;

private:
    DeliverersModel *m_deliverers;
    MilkPointsModel *m_milkPoints;

protected:
    void copyItemValues(MilkBaseItem *left, const MilkBaseItem *right) Q_DECL_OVERRIDE;
    void appendToRepository(const MilkBaseItem *item) Q_DECL_OVERRIDE;
};

DB_END_NAMESPACE

#endif // MILKRECEPTION_TABLE_H
