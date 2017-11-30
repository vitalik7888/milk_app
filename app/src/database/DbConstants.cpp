#include "DbConstants.h"

// Qt
#include <QString>

const QString DbConstants::INDEX_RECEPT_DELIV = "receptDelivIndex";
const QString DbConstants::INDEX_RECEPT_POINT = "receptPointIndex";

const QString DbConstants::TD_TABLE_NAME = "deliverers";
const QString DbConstants::TD_FN_ID = "id";
const QString DbConstants::TD_FN_NAME = "name";
const QString DbConstants::TD_FN_LOCALITY_ID = "locality_id";
const QString DbConstants::TD_FN_INN = "inn";
const QString DbConstants::TD_FN_ADDRESS = "address";
const QString DbConstants::TD_FN_PHONE_NUMBER = "phone_number";

const QString DbConstants::TL_TABLE_NAME = "localities";
const QString DbConstants::TL_FN_ID = "id";
const QString DbConstants::TL_FN_NAME = "name";
const QString DbConstants::TL_FN_DESCRIPTION = "description";

const QString DbConstants::TMP_TABLE_NAME = "milk_points";
const QString DbConstants::TMP_FN_ID = "id";
const QString DbConstants::TMP_FN_LOCALITY_ID = "locality_id";
const QString DbConstants::TMP_FN_NAME = "name";
const QString DbConstants::TMP_FN_DESCRIPTION = "description";

const QString DbConstants::TMR_TABLE_NAME = "milk_reception";
const QString DbConstants::TMR_FN_ID = "id";
const QString DbConstants::TMR_FN_ID_DELIVERER = "id_deliverer";
const QString DbConstants::TMR_FN_DELIVERER_NAME = "deliverer_name";
const QString DbConstants::TMR_FN_MILK_POINT_ID = "milk_point_id";
const QString DbConstants::TMR_FN_MILK_POINT_NAME = "milk_point_name";
const QString DbConstants::TMR_FN_DELIVERY_DATE = "delivery_date";
const QString DbConstants::TMR_FN_PRICE_LITER = "price_liter";
const QString DbConstants::TMR_FN_LITERS = "liters";
const QString DbConstants::TMR_FN_FAT = "fat";

const QString DbConstants::TD_CREATE_TABLE_SQL =
        QString(
            "CREATE TABLE %1 ("
            "%2 INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE,"
            "%3 TEXT    NOT NULL,"
            "%4 INTEGER REFERENCES %8 (%9) ON DELETE CASCADE ON UPDATE CASCADE NOT NULL,"
            "%5 INTEGER DEFAULT '0',"
            "%6 TEXT    DEFAULT '',"
            "%7 TEXT    DEFAULT ('+7'));")
        .arg(DbConstants::TD_TABLE_NAME)
        .arg(DbConstants::TD_FN_ID)
        .arg(DbConstants::TD_FN_NAME)
        .arg(DbConstants::TD_FN_LOCALITY_ID)
        .arg(DbConstants::TD_FN_INN)
        .arg(DbConstants::TD_FN_ADDRESS)
        .arg(DbConstants::TD_FN_PHONE_NUMBER)
        .arg(DbConstants::TL_TABLE_NAME)
        .arg(DbConstants::TL_FN_ID);

const QString DbConstants::TL_CREATE_TABLE_SQL =
        QString("CREATE TABLE %1 ("
                "%2 INTEGER NOT NULL UNIQUE,"
                "%3 TEXT    NOT NULL,"
                "%4 TEXT    DEFAULT (''), PRIMARY KEY ( id ) );")
        .arg(DbConstants::TL_TABLE_NAME)
        .arg(DbConstants::TL_FN_ID)
        .arg(DbConstants::TL_FN_NAME)
        .arg(DbConstants::TL_FN_DESCRIPTION);

const QString DbConstants::TMP_CREATE_TABLE_SQL =
        QString("CREATE TABLE %1 ("
                "%2 INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
                "%3 INTEGER NOT NULL CONSTRAINT "
                "locPoint REFERENCES %6 (%7) ON DELETE CASCADE ON UPDATE CASCADE,"
                "%4 TEXT    NOT NULL,"
                "%5 TEXT    DEFAULT '' );")
        .arg(DbConstants::TMP_TABLE_NAME)
        .arg(DbConstants::TMP_FN_ID)
        .arg(DbConstants::TMP_FN_LOCALITY_ID)
        .arg(DbConstants::TMP_FN_NAME)
        .arg(DbConstants::TMP_FN_DESCRIPTION)
        .arg(DbConstants::TL_TABLE_NAME)
        .arg(DbConstants::TL_FN_ID);

const QString DbConstants::TMR_CREATE_TABLE_SQL =
        QString("CREATE TABLE %1 ("
                "%2 INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE,"
                "%3 INTEGER NOT NULL REFERENCES %9 (%10) ON DELETE CASCADE ON UPDATE CASCADE,"
                "%4 INTEGER CONSTRAINT "
                "receptPoint REFERENCES %11 (%12) ON DELETE CASCADE ON UPDATE CASCADE NOT NULL,"
                "%5 NUMERIC NOT NULL,"
                "%6 REAL    NOT NULL,"
                "%7 REAL    NOT NULL,"
                "%8 REAL    NOT NULL,"
                "FOREIGN KEY ( %3 ) REFERENCES %9 (%10) ON DELETE CASCADE ON UPDATE CASCADE );")
        .arg(DbConstants::TMR_TABLE_NAME)
        .arg(DbConstants::TMR_FN_ID)
        .arg(DbConstants::TMR_FN_ID_DELIVERER)
        .arg(DbConstants::TMR_FN_MILK_POINT_ID)
        .arg(DbConstants::TMR_FN_DELIVERY_DATE)
        .arg(DbConstants::TMR_FN_PRICE_LITER)
        .arg(DbConstants::TMR_FN_LITERS)
        .arg(DbConstants::TMR_FN_FAT)
        .arg(DbConstants::TD_TABLE_NAME)
        .arg(DbConstants::TD_FN_ID)
        .arg(DbConstants::TL_TABLE_NAME)
        .arg(DbConstants::TL_FN_ID);

const QString DbConstants::CREATE_INDEX_RECEPT_DELIV_SQL =
        QString("CREATE INDEX %1 ON %2 ( %3, %4 );")
        .arg(DbConstants::INDEX_RECEPT_DELIV)
        .arg(DbConstants::TMR_TABLE_NAME)
        .arg(DbConstants::TMR_FN_ID_DELIVERER)
        .arg(DbConstants::TMR_FN_MILK_POINT_ID);

const QString DbConstants::CREATE_INDEX_RECEPT_POINT_SQL =
        QString("CREATE INDEX %1 ON %2 ( %3 );")
        .arg(DbConstants::INDEX_RECEPT_POINT)
        .arg(DbConstants::TMR_TABLE_NAME)
        .arg(DbConstants::TMR_FN_MILK_POINT_ID);

QString DbConstants::dropTableIfExistsSql(const QString &tableName)
{
    return "DROP TABLE IF EXISTS " + tableName + ";";
}

QString DbConstants::dropIndexIfExistsSql(const QString &indexName)
{
    return "DROP INDEX IF EXISTS " + indexName + ";";
}
