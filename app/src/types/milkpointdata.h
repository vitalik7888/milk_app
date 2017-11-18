#ifndef MILKPOINTDATA_H
#define MILKPOINTDATA_H

#include "TypesConstants.h"
// Qt
#include <QString>


class MilkPointData
{
public:
    MilkPointData();
    MilkPointData(const TypesConstants::milk_id id, const TypesConstants::milk_id localityId, const QString &name, const QString &description);

    TypesConstants::milk_id id() const;
    void setId(const TypesConstants::milk_id &id);

    TypesConstants::milk_id localityId() const;
    void setLocalityId(const TypesConstants::milk_id &localityId);

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    bool isValid() const;

private:
    TypesConstants::milk_id m_id;
    TypesConstants::milk_id m_localityId;
    QString m_name;
    QString m_description;
};

#endif // MILKPOINTDATA_H
