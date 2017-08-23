#ifndef LOCALITY_H
#define LOCALITY_H

#include <tables/localities/localitydata.h>
// Qt
#include <QObject>

class Locality : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int f_Id READ id WRITE setId)
    Q_PROPERTY(QString f_name READ name WRITE setName)
    Q_PROPERTY(QString f_description READ description WRITE setDescription)

public:
    Locality(QObject *parent = Q_NULLPTR);
    Locality(const milk_id id, const QString &name,
             const QString &description, QObject *parent = Q_NULLPTR);
    virtual ~Locality();

    milk_id id() const;
    void setId(const milk_id &id);

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    DB_NAMESPACE::LocalityData data() const;

private:
    DB_NAMESPACE::LocalityData m_data;
};

#endif // LOCALITY_H
