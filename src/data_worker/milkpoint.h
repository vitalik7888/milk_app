#ifndef MILKPOINT_H
#define MILKPOINT_H

#include <tables/milk_points/milkpointdata.h>

class Locality;


class MilkPoint {
public:
    MilkPoint();
    MilkPoint(const milk_id id, Locality *locality, const QString &name, const QString &description);
    MilkPoint(const MilkPoint &milkPoint);
    ~MilkPoint();

    milk_id id() const;
    void setId(const milk_id &id);

    Locality *locality() const;
    void setLocality(Locality *locality);

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    bool isValid() const;

    DB_NAMESPACE::MilkPointData data() const;

private:
    DB_NAMESPACE::MilkPointData m_data;
    Locality *m_locality;
};

#endif // MILKPOINT_H
