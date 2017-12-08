#ifndef TYPESCONSTANTS_H
#define TYPESCONSTANTS_H

#include <QDate>
#include <QString>


class TypesConstants
{
public:
    class Deliverers {
    public:
        static const int     DEF_ID;
        static const QString DEF_NAME;
        static const int     DEF_LOCALITY_ID;
        static const QString DEF_INN;
        static const QString DEF_ADDRESS;
        static const QString DEF_PHONE_NUMBER;
    };

    class MilkReception {
    public:
        static const int     DEF_ID;
        static const int     DEF_ID_DELIVERER;
        static const QString DEF_DELIVERER_NAME;
        static const int     DEF_MILK_POINT_ID;
        static const QString DEF_MILK_POINT_NAME;
        static const QDate   DEF_DELIVERY_DATE;
        static const double  M_DEF_PRICE_LITER;
        static const double  DEF_LITERS;
        static const double  DEF_FAT;
    };

    class Localities {
    public:
        static const int     DEF_ID;
        static const QString DEF_NAME;
        static const QString DEF_DESCRIPTION;
    };

    class MilkPoints {
    public:
        static const int     DEF_ID;
        static const int     DEF_LOCALITY_ID;
        static const QString DEF_NAME;
        static const QString DEF_DESCRIPTION;
    };
};

#endif // TYPESCONSTANTS_H
