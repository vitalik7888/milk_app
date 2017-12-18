#ifndef MILKBASETYPE_H
#define MILKBASETYPE_H

#include "typeslibrary_global.h"


class TYPESLIBRARYSHARED_EXPORT IMilkBaseType {
public:
    virtual ~IMilkBaseType() {}

    virtual int id() const = 0;
    virtual void setId(const int id) = 0;

    virtual bool isValid() const = 0;
};

#define IMilkBaseType_iid "com.milk.IMilkBaseType"

#endif // MILKBASETYPE_H
