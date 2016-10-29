#ifndef MILKPOINT_H
#define MILKPOINT_H

#include "milkpointdata.h"
#include "tables/localities/Locality.h"

DB_BEGIN_NAMESPACE


class MilkPoint {
public:
    MilkPoint();
    MilkPoint(const milk_id id, const Locality &locality, const QString &name, const QString &description);
    MilkPoint(const MilkPoint &milkPoint);
    ~MilkPoint();

    milk_id id() const;
    void setId(const milk_id &id);

    Locality locality() const;
    void setLocality(const Locality &locality);

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    bool isValid() const;

    MilkPointData data() const;

private:
    MilkPointData m_data;
    Locality m_locality;
};

DB_END_NAMESPACE

#endif // MILKPOINT_H
