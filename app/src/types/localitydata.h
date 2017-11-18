#ifndef LOCALITYDATA_H
#define LOCALITYDATA_H

#include "TypesConstants.h"
// Qt
#include <QString>

class LocalityData {
public:
    LocalityData();
    LocalityData(const TypesConstants::milk_id id, const QString &name, const QString &description);
    LocalityData(const LocalityData &data);
    ~LocalityData();

    TypesConstants::milk_id id() const;
    void setId(const TypesConstants::milk_id &id);

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    bool isValid() const;

private:
    TypesConstants::milk_id m_id;
    QString m_name;
    QString m_description;
};

#endif // LOCALITYDATA_H
