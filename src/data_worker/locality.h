#ifndef LOCALITY_H
#define LOCALITY_H

#include <tables/localities/localitydata.h>

class Locality
{
public:
    Locality();
    Locality(const milk_id id, const QString &name, const QString &description);
    Locality(const Locality &locality);
    ~Locality();

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
