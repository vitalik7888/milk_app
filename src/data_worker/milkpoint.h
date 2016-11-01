#ifndef MILKPOINT_H
#define MILKPOINT_H

#include <tables/milk_points/milkpointdata.h>
// Qt
#include <QWeakPointer>

class Locality;


class MilkPoint {
public:
    MilkPoint();
    MilkPoint(const milk_id id, const QString &name, const QString &description,
              const QWeakPointer<Locality> &locality = QWeakPointer<Locality>());
    MilkPoint(const MilkPoint &milkPoint);
    ~MilkPoint();

    milk_id id() const;
    void setId(const milk_id &id);

    QWeakPointer<Locality> locality() const;
    void setLocality(const QWeakPointer<Locality> &locality);

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    bool isValid() const;

    DB_NAMESPACE::MilkPointData data() const;

private:
    DB_NAMESPACE::MilkPointData m_data;
    QWeakPointer<Locality> m_locality;
};

#endif // MILKPOINT_H
