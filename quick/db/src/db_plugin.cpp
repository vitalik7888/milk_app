#include "db_plugin.h"

#include "Database.h"
#include <DaoSql.h>
#include <DbMilkReception.h>
#include <MilkReceptionModel.h>
#include <LocalitiesSortFilterProxyModel.h>
#include <MilkPointsSortFilterProxyModel.h>
#include <DeliverersSortFilterProxyModel.h>
#include <MilkReceptionSortFilterProxyModel.h>
#include "LocalitiesDao.h"
#include "DeliverersDao.h"
#include "MilkpointsDao.h"
#include "MilkReceprionDao.h"
// Qt
#include <qqml.h>

USE_DB_NAMESPACE


void DbPlugin::registerTypes(const char *uri)
{
    // @uri com.milk.db
    qmlRegisterUncreatableType<DbConstants>(uri, 1, 0, "DBC", "Can not create instance of the DB constants");
    qmlRegisterInterface<DaoSql>("DaoSql");
    qmlRegisterInterface<MilkModel>("MilkModel");
    qmlRegisterInterface<MilkBaseDbObject>("MilkBaseDbObject");
    qmlRegisterType<LocalitiesDao>(uri, 1, 0, "LocalitiesDao");
    qmlRegisterType<DeliverersDao>(uri, 1, 0, "DeliverersDao");
    qmlRegisterType<MilkPointDao>(uri, 1, 0, "MilkPointDao");
    qmlRegisterType<MilkReceptionDao>(uri, 1, 0, "MilkReceptionDao");
    qmlRegisterType<DbLocality>(uri, 1, 0, "DbLocality");
    qmlRegisterType<DbMilkPoint>(uri, 1, 0, "DbMilkPoint");
    qmlRegisterType<DbDeliverer>(uri, 1, 0, "DbDeliverer");
    qmlRegisterType<DbMilkReception>(uri, 1, 0, "DbMilkReception");
    qmlRegisterType<LocalitiesModel>(uri, 1, 0, "LocalitiesModel");
    qmlRegisterType<MilkPointsModel>(uri, 1, 0, "MilkPointsModel");
    qmlRegisterType<DeliverersModel>(uri, 1, 0, "DeliverersModel");
    qmlRegisterType<MilkReceptionModel>(uri, 1, 0, "MilkReceptionModel");
    qmlRegisterType<LocalitiesSortFilterProxyModel>(uri, 1, 0, "LocalitiesSortFilterProxyModel");
    qmlRegisterType<MilkPointsSortFilterProxyModel>(uri, 1, 0, "MilkPointsSortFilterProxyModel");
    qmlRegisterType<DeliverersSortFilterProxyModel>(uri, 1, 0, "DeliverersSortFilterProxyModel");
    qmlRegisterType<MilkReceptionSortFilterProxyModel>(uri, 1, 0, "MilkReceptionSortFilterProxyModel");
    qmlRegisterType<Database>(uri, 1, 0, "Database");
}

