#ifndef LOCALITYDATA_H
#define LOCALITYDATA_H

#include "dbconstants.h"
// Qt
#include <QString>

DB_BEGIN_NAMESPACE

class LocalityData {
public:
    LocalityData();
    LocalityData(const milk_id id, const QString &name, const QString &description);
    LocalityData(const LocalityData &data);
    ~LocalityData();

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

#endif // LOCALITYDATA_H
