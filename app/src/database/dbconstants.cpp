#include "dbconstants.h"

// Qt
#include <QString>

const QString DbConstants::INDEX_RECEPT_DELIV = "receptDelivIndex";
const QString DbConstants::INDEX_RECEPT_POINT = "receptPointIndex";

const QString DbConstants::Deliverers::TABLE_NAME = "deliverers";
const QString DbConstants::Deliverers::FN_ID = "id";
const QString DbConstants::Deliverers::FN_NAME = "name";
const QString DbConstants::Deliverers::FN_LOCALITY_ID = "locality_id";
const QString DbConstants::Deliverers::FN_INN = "inn";
const QString DbConstants::Deliverers::FN_ADDRESS = "address";
const QString DbConstants::Deliverers::FN_PHONE_NUMBER = "phone_number";

const QString DbConstants::Localities::TABLE_NAME = "localities";
const QString DbConstants::Localities::FN_ID = "id";
const QString DbConstants::Localities::FN_NAME = "name";
const QString DbConstants::Localities::FN_DESCRIPTION = "description";

const QString DbConstants::MilkPoints::TABLE_NAME = "milk_points";
const QString DbConstants::MilkPoints::FN_ID = "id";
const QString DbConstants::MilkPoints::FN_LOCALITY_ID = "locality_id";
const QString DbConstants::MilkPoints::FN_NAME = "name";
const QString DbConstants::MilkPoints::FN_DESCRIPTION = "description";

const QString DbConstants::MilkReception::TABLE_NAME = "milk_reception";
const QString DbConstants::MilkReception::FN_ID = "id";
const QString DbConstants::MilkReception::FN_ID_DELIVERER = "id_deliverer";
const QString DbConstants::MilkReception::FN_DELIVERER_NAME = "deliverer_name";
const QString DbConstants::MilkReception::FN_MILK_POINT_ID = "milk_point_id";
const QString DbConstants::MilkReception::FN_MILK_POINT_NAME = "milk_point_name";
const QString DbConstants::MilkReception::FN_DELIVERY_DATE = "delivery_date";
const QString DbConstants::MilkReception::FN_PRICE_LITER = "price_liter";
const QString DbConstants::MilkReception::FN_LITERS = "liters";
const QString DbConstants::MilkReception::FN_FAT = "fat";

const QString DbConstants::Deliverers::CREATE_TABLE_SQL =
        QString(
            "CREATE TABLE %1 ("
            "%2 INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE,"
            "%3 TEXT    NOT NULL,"
            "%4 INTEGER REFERENCES %8 (%9) ON DELETE CASCADE ON UPDATE CASCADE NOT NULL,"
            "%5 INTEGER DEFAULT '0',"
            "%6 TEXT    DEFAULT '',"
            "%7 TEXT    DEFAULT ('+7'));")
        .arg(DbConstants::Deliverers::TABLE_NAME)
        .arg(DbConstants::Deliverers::FN_ID)
        .arg(DbConstants::Deliverers::FN_NAME)
        .arg(DbConstants::Deliverers::FN_LOCALITY_ID)
        .arg(DbConstants::Deliverers::FN_INN)
        .arg(DbConstants::Deliverers::FN_ADDRESS)
        .arg(DbConstants::Deliverers::FN_PHONE_NUMBER)
        .arg(DbConstants::Localities::TABLE_NAME)
        .arg(DbConstants::Localities::FN_ID);

const QString DbConstants::Localities::CREATE_TABLE_SQL =
        QString("CREATE TABLE %1 ("
                "%2 INTEGER NOT NULL UNIQUE,"
                "%3 TEXT    NOT NULL,"
                "%4 TEXT    DEFAULT (''), PRIMARY KEY ( id ) );")
        .arg(DbConstants::Localities::TABLE_NAME)
        .arg(DbConstants::Localities::FN_ID)
        .arg(DbConstants::Localities::FN_NAME)
        .arg(DbConstants::Localities::FN_DESCRIPTION);

const QString DbConstants::MilkPoints::CREATE_TABLE_SQL =
        QString("CREATE TABLE %1 ("
                "%2 INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
                "%3 INTEGER NOT NULL CONSTRAINT "
                "locPoint REFERENCES %6 (%7) ON DELETE CASCADE ON UPDATE CASCADE,"
                "%4 TEXT    NOT NULL,"
                "%5 TEXT    DEFAULT '' );")
        .arg(DbConstants::MilkPoints::TABLE_NAME)
        .arg(DbConstants::MilkPoints::FN_ID)
        .arg(DbConstants::MilkPoints::FN_LOCALITY_ID)
        .arg(DbConstants::MilkPoints::FN_NAME)
        .arg(DbConstants::MilkPoints::FN_DESCRIPTION)
        .arg(DbConstants::Localities::TABLE_NAME)
        .arg(DbConstants::Localities::FN_ID);

const QString DbConstants::MilkReception::CREATE_TABLE_SQL =
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
        .arg(DbConstants::MilkReception::TABLE_NAME)
        .arg(DbConstants::MilkReception::FN_ID)
        .arg(DbConstants::MilkReception::FN_ID_DELIVERER)
        .arg(DbConstants::MilkReception::FN_MILK_POINT_ID)
        .arg(DbConstants::MilkReception::FN_DELIVERY_DATE)
        .arg(DbConstants::MilkReception::FN_PRICE_LITER)
        .arg(DbConstants::MilkReception::FN_LITERS)
        .arg(DbConstants::MilkReception::FN_FAT)
        .arg(DbConstants::Deliverers::TABLE_NAME)
        .arg(DbConstants::Deliverers::FN_ID)
        .arg(DbConstants::Localities::TABLE_NAME)
        .arg(DbConstants::Localities::FN_ID);

const QString DbConstants::CREATE_INDEX_RECEPT_DELIV_SQL =
        QString("CREATE INDEX %1 ON %2 ( %3, %4 );")
        .arg(DbConstants::INDEX_RECEPT_DELIV)
        .arg(DbConstants::MilkReception::TABLE_NAME)
        .arg(DbConstants::MilkReception::FN_ID_DELIVERER)
        .arg(DbConstants::MilkReception::FN_MILK_POINT_ID);

const QString DbConstants::CREATE_INDEX_RECEPT_POINT_SQL =
        QString("CREATE INDEX %1 ON %2 ( %3 );")
        .arg(DbConstants::INDEX_RECEPT_POINT)
        .arg(DbConstants::MilkReception::TABLE_NAME)
        .arg(DbConstants::MilkReception::FN_MILK_POINT_ID);

QString DbConstants::dropTableIfExistsSql(const QString &tableName)
{
    return "DROP TABLE IF EXISTS " + tableName + ";";
}

QString DbConstants::dropIndexIfExistsSql(const QString &indexName)
{
    return "DROP INDEX IF EXISTS " + indexName + ";";
}
