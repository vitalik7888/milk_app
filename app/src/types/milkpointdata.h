#ifndef MILKPOINTDATA_H
#define MILKPOINTDATA_H

#include "dbconstants.h"
// Qt
#include <QString>


class MilkPointData
{
public:
    MilkPointData();
    MilkPointData(const milk_id id, const milk_id localityId, const QString &name, const QString &description);

    milk_id id() const;
    void setId(const milk_id &id);

    milk_id localityId() const;
    void setLocalityId(const milk_id &localityId);

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    bool isValid() const;

private:
    milk_id m_id;
    milk_id m_localityId;
    QString m_name;
    QString m_description;
};

#endif // MILKPOINTDATA_H
