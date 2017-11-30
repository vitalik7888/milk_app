#ifndef MILKPOINT_H
#define MILKPOINT_H

#include "MilkPointData.h"
// Qt
#include <QObject>

class Locality;


class MilkPoint : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int milkPointId READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(Locality *locality READ locality WRITE setLocality NOTIFY localityChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)

public:
    MilkPoint(const int id, const QString &name, const QString &description,
              Locality *locality = Q_NULLPTR, QObject *parent = Q_NULLPTR);
    MilkPoint(const MilkPoint &milkPoint);
    MilkPoint(QObject *parent = Q_NULLPTR);
    virtual ~MilkPoint();

    int id() const;
    Locality *locality() const;
    QString name() const;
    QString description() const;

    Q_INVOKABLE bool isValid() const;

    MilkPointData data() const;

public slots:
    void setId(const int id);
    void setLocality(Locality * locality);
    void setName(const QString &name);
    void setDescription(const QString &description);
    void reset();

signals:
    void idChanged(int milkPointId);
    void localityChanged(Locality * locality);
    void nameChanged(QString name);
    void descriptionChanged(QString description);

private:
    MilkPointData m_data;
    Locality *m_locality;
};

Q_DECLARE_METATYPE(MilkPoint)

#endif // MILKPOINT_H
