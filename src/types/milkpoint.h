#ifndef MILKPOINT_H
#define MILKPOINT_H

#include "milkpointdata.h"
// Qt
#include <QObject>

class Locality;


class MilkPoint : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qlonglong milkPointId READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(Locality *locality READ locality WRITE setLocality NOTIFY localityChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)

public:
    MilkPoint(const MilkPointData &data, Locality *locality = Q_NULLPTR, QObject *parent = Q_NULLPTR);
    MilkPoint(const milk_id id, const QString &name, const QString &description,
              Locality *locality = Q_NULLPTR, QObject *parent = Q_NULLPTR);
    MilkPoint(QObject *parent = Q_NULLPTR);
    virtual ~MilkPoint();

    milk_id id() const;
    Locality *locality() const;
    QString name() const;
    QString description() const;

    Q_INVOKABLE bool isValid() const;

    MilkPointData data() const;

public slots:
    void setId(const milk_id &id);
    void setLocality(Locality * locality);
    void setName(const QString &name);
    void setDescription(const QString &description);
    void reset();

signals:
    void idChanged(qlonglong milkPointId);
    void localityChanged(Locality * locality);
    void nameChanged(QString name);
    void descriptionChanged(QString description);

private:
    MilkPointData m_data;
    Locality *m_locality;
};

#endif // MILKPOINT_H
