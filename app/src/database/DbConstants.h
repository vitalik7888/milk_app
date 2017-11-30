#ifndef DBCONSTANTS_H
#define DBCONSTANTS_H

#include <QObject>

#define DB_NAMESPACE db
#define USE_DB_NAMESPACE using namespace ::DB_NAMESPACE;
#define DB_BEGIN_NAMESPACE namespace DB_NAMESPACE {
#define DB_END_NAMESPACE }


class DbConstants {
    Q_GADGET
public:
    static QString dropTableIfExistsSql(const QString &tableName);
    static QString dropIndexIfExistsSql(const QString &indexName);

    static const QString INDEX_RECEPT_DELIV;
    static const QString INDEX_RECEPT_POINT;

    enum DeliverersTableColumns {
        TD_ID = 0,
        TD_NAME,
        TD_LOCALITY_ID,
        TD_INN,
        TD_ADDRESS,
        TD_PHONE_NUMBER
    };
    Q_ENUM(DeliverersTableColumns)
    static const QString TD_TABLE_NAME;
    static const QString TD_FN_ID;
    static const QString TD_FN_NAME;
    static const QString TD_FN_LOCALITY_ID;
    static const QString TD_FN_INN;
    static const QString TD_FN_ADDRESS;
    static const QString TD_FN_PHONE_NUMBER;
    static const QString TD_CREATE_TABLE_SQL;

    enum ReceptionMilkTableColumns {
        TMR_ID = 0,
        TMR_ID_DELIVERER,
        TMR_DELIVERER_NAME,
        TMR_MILK_POINT_ID,
        TMR_MILK_POINT_NAME,
        TMR_DELIVERY_DATE,
        TMR_PRICE_LITER,
        TMR_LITERS,
        TMR_FAT
    };
    Q_ENUM(ReceptionMilkTableColumns)
    static const QString TMR_TABLE_NAME;
    static const QString TMR_FN_ID;
    static const QString TMR_FN_ID_DELIVERER;
    static const QString TMR_FN_DELIVERER_NAME;
    static const QString TMR_FN_MILK_POINT_ID;
    static const QString TMR_FN_MILK_POINT_NAME;
    static const QString TMR_FN_DELIVERY_DATE;
    static const QString TMR_FN_PRICE_LITER;
    static const QString TMR_FN_LITERS;
    static const QString TMR_FN_FAT;
    static const QString TMR_CREATE_TABLE_SQL;

    enum LocalityTableColumns {
        TL_ID = 0,
        TL_NAME,
        TL_DESCRIPTION
    };
    Q_ENUM(LocalityTableColumns)
    static const QString TL_TABLE_NAME;
    static const QString TL_FN_ID;
    static const QString TL_FN_NAME;
    static const QString TL_FN_DESCRIPTION;
    static const QString TL_CREATE_TABLE_SQL;

    enum MilkPointsTableColumns {
        TMP_ID = 0,
        TMP_LOCALITY_ID,
        TMP_NAME,
        TMP_DESCRIPTION
    };
    Q_ENUM(MilkPointsTableColumns)
    static const QString TMP_TABLE_NAME;
    static const QString TMP_FN_ID;
    static const QString TMP_FN_LOCALITY_ID;
    static const QString TMP_FN_NAME;
    static const QString TMP_FN_DESCRIPTION;
    static const QString TMP_CREATE_TABLE_SQL;

    static const QString CREATE_INDEX_RECEPT_DELIV_SQL;
    static const QString CREATE_INDEX_RECEPT_POINT_SQL;
};

#endif // DBCONSTANTS_H
