#ifndef DBCONSTANTS_H
#define DBCONSTANTS_H

#include <QtGlobal>

#define DB_NAMESPACE db
#define USE_DB_NAMESPACE using namespace ::DB_NAMESPACE;
#define DB_BEGIN_NAMESPACE namespace DB_NAMESPACE {
#define DB_END_NAMESPACE }

using milk_id = qlonglong;
using milk_inn = qlonglong;

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
