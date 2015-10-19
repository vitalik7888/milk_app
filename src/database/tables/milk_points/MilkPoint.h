#ifndef MILKPOINT_H
#define MILKPOINT_H

#include "tables/localities/Locality.h"


class MilkPoint {
public:
    MilkPoint();
    MilkPoint(const Locality &locality, const QString &name,
              const QString &description = "", const qlonglong id = -1);

    qlonglong id() const;
    void setId(const qlonglong &id);

    Locality locality() const;

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    bool isNull() const;

    QString toString() const;

    static MilkPoint CREATE_NULL();

private:
    qlonglong _id;
    Locality _locality;
    QString _name;
    QString _description;
};

#endif // MILKPOINT_H
