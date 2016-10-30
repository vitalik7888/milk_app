#ifndef DBCONSTANTS_H
#define DBCONSTANTS_H

#include <QtGlobal>

#define DB_NAMESPACE db
#define USE_DB_NAMESPACE using namespace ::DB_NAMESPACE;
#define DB_BEGIN_NAMESPACE namespace DB_NAMESPACE {
#define DB_END_NAMESPACE }

using milk_id = qlonglong;
using milk_inn = qlonglong;

enum DeliverersTableColumns {
    DT_ID = 0,
    DT_NAME,
    DT_LOCALITY_ID,
    DT_INN,
    DT_ADDRESS,
    DT_PHONE_NUMBER
};

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

enum LocalityTableColumns {
    LT_ID = 0,
    LT_NAME,
    LT_DESCRIPTION
};

enum MilkPointsTableColumns {
    MPT_ID = 0,
    MPT_LOCALITY_ID,
    MPT_NAME,
    MPT_DESCRIPTION
};

#endif // DBCONSTANTS_H
