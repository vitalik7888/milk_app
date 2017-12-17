#include "qmldb_plugin.h"

#include "Database.h"
#include "LocalitiesSortFilterProxyModel.h"
#include "MilkPointsSortFilterProxyModel.h"
#include "DeliverersSortFilterProxyModel.h"
#include "MilkReceptionSortFilterProxyModel.h"
// Qt
#include <qqml.h>

USE_DB_NAMESPACE


void QmldbpluginPlugin::registerTypes(const char *uri)
{
    // @uri com.milk.db
    qmlRegisterUncreatableType<DbConstants>(uri, 1, 0, "DBC", "Can not create instance of the DB constants");
    qmlRegisterType<LocalitiesTable>(uri, 1, 0, "LocalitiesTable");
    qmlRegisterType<MilkPointsTable>(uri, 1, 0, "MilkPointsTable");
    qmlRegisterType<DeliverersTable>(uri, 1, 0, "DeliverersTable");
    qmlRegisterType<MilkReceptionTable>(uri, 1, 0, "MilkReceptionTable");
    qmlRegisterInterface<Table>("Table");
    qmlRegisterType<LocalitiesSortFilterProxyModel>(uri, 1, 0, "LocalitiesSortFilterProxyModel");
    qmlRegisterType<MilkPointsSortFilterProxyModel>(uri, 1, 0, "MilkPointsSortFilterProxyModel");
    qmlRegisterType<DeliverersSortFilterProxyModel>(uri, 1, 0, "DeliverersSortFilterProxyModel");
    qmlRegisterType<MilkReceptionSortFilterProxyModel>(uri, 1, 0, "MilkReceptionSortFilterProxyModel");
    qmlRegisterType<Database>(uri, 1, 0, "Database");
}

