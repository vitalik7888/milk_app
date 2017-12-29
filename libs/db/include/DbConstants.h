#ifndef DB_CONSTANTS_H
#define DB_CONSTANTS_H

#include "dblibrary_global.h"
// Qt
#include <QObject>

#define DB_NAMESPACE db
#define USE_DB_NAMESPACE using namespace DB_NAMESPACE;
#define DB_BEGIN_NAMESPACE namespace DB_NAMESPACE {
#define DB_END_NAMESPACE }


class DBLIBRARYSHARED_EXPORT DbConstants {
    Q_GADGET
public:
    static QString dropTableIfExistsSql(const QString &tableName);
    static QString dropIndexIfExistsSql(const QString &indexName);

    static const QString INDEX_RECEPT_DELIV;
    static const QString INDEX_RECEPT_POINT;

    enum DeliverersTableColumns {
        TD_ID = 0,
        TD_FIRST_NAME,
        TD_LAST_NAME,
        TD_LOCALITY_ID,
        TD_INN,
        TD_ADDRESS,
        TD_PHONE_NUMBER
    };
    Q_ENUM(DeliverersTableColumns)
    enum class DeliverersRoles {
        MilkIdRole = Qt::UserRole + 1,
        DM_FirstNameRole,
        DM_LastNameRole,
        DM_FullNameRole,
        DM_InnRole,
        DM_LocalityIdRole,
        DM_LocalityNameRole,
        DM_AddressRole,
        DM_PhoneNumberRole
    };
    Q_ENUM(DeliverersRoles)
    static const QString TD_TABLE_NAME;
    static const QString TD_FN_ID;
    static const QString TD_FN_FIRST_NAME;
    static const QString TD_FN_LAST_NAME;
    static const QString TD_FN_LOCALITY_ID;
    static const QString TD_FN_INN;
    static const QString TD_FN_ADDRESS;
    static const QString TD_FN_PHONE_NUMBER;
    static const QString TD_CREATE_TABLE_SQL;

    enum ReceptionMilkTableColumns {
        TMR_ID = 0,
        TMR_ID_DELIVERER,
        TMR_DELIVERER_FNAME,
        TMR_DELIVERER_LNAME,
        TMR_MILK_POINT_ID,
        TMR_MILK_POINT_NAME,
        TMR_DELIVERY_DATE,
        TMR_PRICE_LITER,
        TMR_LITERS,
        TMR_FAT
    };
    Q_ENUM(ReceptionMilkTableColumns)
    enum class MilkReceptionRoles {
        MilkIdRole = Qt::UserRole + 1,
        MR_DelivererIdRole,
        MR_DelivererFullNameRole,
        MR_MilkPointIdRole,
        MR_MilkPointNameRole,
        MR_DeliveryDateRole,
        MR_PriceLiterRole,
        MR_LitersRole,
        MR_FatRole
    };
    Q_ENUM(MilkReceptionRoles)
    static const QString TMR_TABLE_NAME;
    static const QString TMR_FN_ID;
    static const QString TMR_FN_ID_DELIVERER;
    static const QString TMR_FN_DELIVERER_FNAME;
    static const QString TMR_FN_DELIVERER_LNAME;
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
    enum class LocalitiesRoles {
        MilkIdRole = Qt::UserRole + 1,
        NameRole,
        DescriptionRole,
    };
    Q_ENUM(LocalitiesRoles)
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
    enum class MilkPointRoles {
        MilkIdRole = Qt::UserRole + 1,
        MP_NameRole,
        MP_DescriptionRole,
        MP_LocalityIdRole,
        MP_LocalityNameRole,
    };
    Q_ENUM(MilkPointRoles)
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
