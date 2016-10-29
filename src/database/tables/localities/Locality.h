#ifndef LOCALITY_H
#define LOCALITY_H

#include "dbconstants.h"
// Qt
#include <QString>

DB_BEGIN_NAMESPACE

class Locality {
public:
    Locality();
    Locality(const milk_id id, const QString &name, const QString &description);

    milk_id id() const;
    void setId(const milk_id &id);

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    bool isValid() const;

private:
    milk_id m_id;
    QString m_name;
    QString m_description;
};

DB_END_NAMESPACE

#endif // LOCALITY_H
