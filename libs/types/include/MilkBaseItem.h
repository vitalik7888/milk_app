#ifndef MILK_BASE_ITEM_H_
#define MILK_BASE_ITEM_H_

#include "typeslibrary_global.h"
// Qt
#include <QHash>

typedef int MILK_ID;


class TYPESLIBRARYSHARED_EXPORT MilkBaseItem
{
public:
    virtual ~MilkBaseItem() {}

    virtual MILK_ID milkId() const = 0;
    virtual void setMilkId(const MILK_ID id) = 0;

    virtual bool isValid() const { return milkId() > 0; }
    virtual void reset() { setMilkId(-1); }
};

inline bool operator==(const MilkBaseItem &left, const MilkBaseItem &right)
{
    return left.milkId() == right.milkId();
}

inline uint qHash(const MilkBaseItem &key, uint seed)
{
    return qHash(key.milkId(), seed);
}

#endif // MILKBASEITEM_H
