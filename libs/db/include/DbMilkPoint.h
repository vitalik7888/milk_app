#ifndef DB_MILKPOINT_H_
#define DB_MILKPOINT_H_

#include <DbLocality.h>
#include "MilkPointsModel.h"
#include <MilkPoint.h>

DB_BEGIN_NAMESPACE


class DBLIBRARYSHARED_EXPORT DbMilkPoint : public MilkBaseDbObject
{
    using base = MilkBaseDbObject;
    Q_OBJECT
    Q_PROPERTY(DbLocality* locality READ locality CONSTANT)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)

public:
    explicit DbMilkPoint(QObject *parent = nullptr);

    QString name() const;
    QString description() const;
    DbLocality *locality() const { return m_locality; }

signals:
    void nameChanged(const QString &name);
    void descriptionChanged(const QString &description);

public slots:
    void setItem(const MilkBaseItem *item);
    void setName(const QString &name);
    void setDescription(const QString &description);

private:
    DbLocality* m_locality;

    MilkPoint *milkPoint() const;
};

DB_END_NAMESPACE

#endif // DBMILKPOINT_H
