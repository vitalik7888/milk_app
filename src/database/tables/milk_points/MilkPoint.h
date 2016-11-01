#ifndef MILKPOINT_H
#define MILKPOINT_H

#include "milkpointdata.h"
#include "tables/localities/localitydata.h"

DB_BEGIN_NAMESPACE


class MilkPoint {
public:
    MilkPoint();
    MilkPoint(const milk_id id, const LocalityData &locality, const QString &name, const QString &description);
    MilkPoint(const MilkPoint &milkPoint);
    ~MilkPoint();

    milk_id id() const;
    void setId(const milk_id &id);

    LocalityData locality() const;
    void setLocality(const LocalityData &locality);

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    bool isValid() const;

    MilkPointData data() const;

private:
    MilkPointData m_data;
    LocalityData m_locality;
};

DB_END_NAMESPACE

#endif // MILKPOINT_H
