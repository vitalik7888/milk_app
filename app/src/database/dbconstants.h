#ifndef DBCONSTANTS_H
#define DBCONSTANTS_H

#include <QtGlobal>

#define DB_NAMESPACE db
#define USE_DB_NAMESPACE using namespace ::DB_NAMESPACE;
#define DB_BEGIN_NAMESPACE namespace DB_NAMESPACE {
#define DB_END_NAMESPACE }

using milk_id = qlonglong;
using milk_inn = qlonglong;

class DbConstants {
public:
    static QString dropTableIfExistsSql(const QString &tableName);
    static QString dropIndexIfExistsSql(const QString &indexName);

    static const QString INDEX_RECEPT_DELIV;
    static const QString INDEX_RECEPT_POINT;

    class Deliverers {
    public:
        enum DeliverersTableColumns {
            DT_ID = 0,
            DT_NAME,
            DT_LOCALITY_ID,
            DT_INN,
            DT_ADDRESS,
            DT_PHONE_NUMBER
        };

        static const QString TABLE_NAME;
        static const QString FN_ID;
        static const QString FN_NAME;
        static const QString FN_LOCALITY_ID;
        static const QString FN_INN;
        static const QString FN_ADDRESS;
        static const QString FN_PHONE_NUMBER;

        static const QString CREATE_TABLE_SQL;
    };

    class MilkReception {
    public:
        enum ReceptionMilkTableColumns {
            RMT_ID = 0,
            RMT_ID_DELIVERER,
            RMT_DELIVERER_NAME,
            RMT_MILK_POINT_ID,
            RMT_MILK_POINT_NAME,
            RMT_DELIVERY_DATE,
            RMT_PRICE_LITER,
            RMT_LITERS,
            RMT_FAT
        };

        static const QString TABLE_NAME;
        static const QString FN_ID;
        static const QString FN_ID_DELIVERER;
        static const QString FN_DELIVERER_NAME;
        static const QString FN_MILK_POINT_ID;
        static const QString FN_MILK_POINT_NAME;
        static const QString FN_DELIVERY_DATE;
        static const QString FN_PRICE_LITER;
        static const QString FN_LITERS;
        static const QString FN_FAT;

        static const QString CREATE_TABLE_SQL;
    };

    class Localities {
    public:
        enum LocalityTableColumns {
            LT_ID = 0,
            LT_NAME,
            LT_DESCRIPTION
        };

        static const QString TABLE_NAME;
        static const QString FN_ID;
        static const QString FN_NAME;
        static const QString FN_DESCRIPTION;

        static const QString CREATE_TABLE_SQL;
    };

    class MilkPoints {
    public:
        enum MilkPointsTableColumns {
            MPT_ID = 0,
            MPT_LOCALITY_ID,
            MPT_NAME,
            MPT_DESCRIPTION
        };

        static const QString TABLE_NAME;
        static const QString FN_ID;
        static const QString FN_LOCALITY_ID;
        static const QString FN_NAME;
        static const QString FN_DESCRIPTION;

        static const QString CREATE_TABLE_SQL;
    };

    static const QString CREATE_INDEX_RECEPT_DELIV_SQL;
    static const QString CREATE_INDEX_RECEPT_POINT_SQL;
};

#endif // DBCONSTANTS_H
