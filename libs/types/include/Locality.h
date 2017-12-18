#ifndef LOCALITY_H
#define LOCALITY_H

#include "LocalityData.h"
// Qt
#include <QObject>


class TYPESLIBRARYSHARED_EXPORT Locality : public QObject, public ILocality
{
    Q_OBJECT
    Q_PROPERTY(int localityId READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)

public:
    Locality(const LocalityData &data, QObject *parent = Q_NULLPTR);
    Locality(const Locality &locality);
    Locality(QObject *parent = Q_NULLPTR);

    int id() const Q_DECL_OVERRIDE;
    QString name() const Q_DECL_OVERRIDE;
    QString description() const Q_DECL_OVERRIDE;
    virtual bool isValid() const Q_DECL_OVERRIDE;

    LocalityData data() const;

public slots:
    void setId(const int id);
    void setName(const QString &name);
    void setDescription(const QString &description);
    void reset();

signals:
    void idChanged(int localityId);
    void nameChanged(QString name);
    void descriptionChanged(QString description);

private:
    LocalityData m_data;
};

Q_DECLARE_METATYPE(Locality)

#endif // LOCALITY_H
