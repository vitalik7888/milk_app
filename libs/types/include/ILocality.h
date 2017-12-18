#ifndef ILOCALITY_H
#define ILOCALITY_H

#include "IMilkBaseType.h"


class TYPESLIBRARYSHARED_EXPORT ILocality : public IMilkBaseType
{
public:
    virtual QString name() const = 0;
    virtual void setName(const QString &name) = 0;

    virtual QString description() const = 0;
    virtual void setDescription(const QString &description) = 0;
};

#define ILocality_iid "com.milk.ILocality"

#endif // ILOCALITY_H
