#ifndef MILKPOINT_H
#define MILKPOINT_H

#include "milkpointdata.h"
// Qt
#include <QObject>

class Locality;


class MilkPoint : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qlonglong f_id READ id WRITE setId)
    Q_PROPERTY(Locality *f_locality READ locality WRITE setLocality)
    Q_PROPERTY(QString f_name READ name WRITE setName)
    Q_PROPERTY(QString f_description READ description WRITE setDescription)

public:
    MilkPoint(const DB_NAMESPACE::MilkPointData &data, QObject *parent = Q_NULLPTR);
    MilkPoint(const milk_id id, const QString &name, const QString &description,
              Locality *locality = Q_NULLPTR, QObject *parent = Q_NULLPTR);
    MilkPoint(QObject *parent = Q_NULLPTR);
    virtual ~MilkPoint();

    milk_id id() const;
    void setId(const milk_id &id);

    Locality *locality() const;
    void setLocality(Locality *locality);

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    Q_INVOKABLE bool isValid() const;

    DB_NAMESPACE::MilkPointData data() const;

private:
    DB_NAMESPACE::MilkPointData m_data;
    Locality *m_locality;
};

#endif // MILKPOINT_H
