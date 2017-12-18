#ifndef IMILKPOINT_H
#define IMILKPOINT_H

#include "IMilkBaseType.h"


class TYPESLIBRARYSHARED_EXPORT IMilkPoint : public IMilkBaseType
{
public:
    virtual QString name() const = 0;
    virtual void setName(const QString &name) = 0;

    virtual QString description() const = 0;
    virtual void setDescription(const QString &description) = 0;

    virtual int localityId() const = 0;
    virtual void setLocalityId(const int localityId) = 0;
};

#define IMilkPoint_iid "com.milk.IMilkPoint"

#endif // IMILKPOINT_H
