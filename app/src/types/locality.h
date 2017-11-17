#ifndef LOCALITY_H
#define LOCALITY_H

#include "localitydata.h"
// Qt
#include <QObject>

class Locality : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qlonglong localityId READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)

public:
    Locality(const LocalityData &data, QObject *parent = Q_NULLPTR);
    Locality(QObject *parent = Q_NULLPTR);
    virtual ~Locality();

    milk_id id() const;
    QString name() const;
    QString description() const;
    LocalityData data() const;

public slots:
    void setId(const milk_id &id);
    void setName(const QString &name);
    void setDescription(const QString &description);
    void reset();

signals:
    void idChanged(qlonglong localityId);
    void nameChanged(QString name);
    void descriptionChanged(QString description);

private:
    LocalityData m_data;
};

#endif // LOCALITY_H
