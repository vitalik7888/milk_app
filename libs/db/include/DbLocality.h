#ifndef DB_LOCALITY_H_
#define DB_LOCALITY_H_

#include "MilkBaseDbObject.h"
#include <LocalitiesModel.h>
#include <Locality.h>

DB_BEGIN_NAMESPACE


class DBLIBRARYSHARED_EXPORT DbLocality : public MilkBaseDbObject
{
    using base = MilkBaseDbObject;
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)

public:
    DbLocality(QObject *parent = Q_NULLPTR);

    QString name() const;
    QString description() const;

public slots:
    void setItem(const MilkBaseItem *item) Q_DECL_OVERRIDE;
    void setName(const QString &name);
    void setDescription(const QString &description);

signals:
    void nameChanged(const QString &name);
    void descriptionChanged(const QString &description);

private:
    Locality *locality() const;
};

DB_END_NAMESPACE

#endif // DBLOCALITY_H
