#ifndef TYPES_CONSTANTS_H_
#define TYPES_CONSTANTS_H_

#include "typeslibrary_global.h"
// Qt
#include <QDate>
#include <QString>

using MILK_ID = int;

class TYPESLIBRARYSHARED_EXPORT TypesConstants
{
public:
    static const int DEFAULT_ID;

    class Deliverers {
    public:
        static const QString DEF_FIRST_NAME;
        static const QString DEF_LAST_NAME;
        static const QString DEF_INN;
        static const QString DEF_ADDRESS;
        static const QString DEF_PHONE_NUMBER;
    };

    class MilkReception {
    public:
        static const QString DEF_DELIVERER_NAME;
        static const QString DEF_MILK_POINT_NAME;
        static const QDate   DEF_DELIVERY_DATE;
        static const double  DEF_PRICE_LITER;
        static const double  DEF_LITERS;
        static const double  DEF_FAT;
    };

    class Localities {
    public:
        static const QString DEF_NAME;
        static const QString DEF_DESCRIPTION;
    };

    class MilkPoints {
    public:
        static const QString DEF_NAME;
        static const QString DEF_DESCRIPTION;
    };
};

#endif // TYPESCONSTANTS_H
