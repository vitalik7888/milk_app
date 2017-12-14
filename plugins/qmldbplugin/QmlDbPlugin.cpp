#include "QmlDbPlugin.h"

#include <base/Database.h>
#include "tables/localities/LocalitiesSortFilterProxyModel.h"
#include "tables/milk_points/MilkPointsSortFilterProxyModel.h"
#include "tables/deliverers/DeliverersSortFilterProxyModel.h"
#include "tables/milk_reception/MilkReceptionSortFilterProxyModel.h"
// Qt
#include <qqml.h>

USE_DB_NAMESPACE


#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(qmldbplugin, QmlDbPlugin)
#endif // QT_VERSION < 0x050000


void QmlDbPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<Database>(uri, 1, 0, "Database");
    qmlRegisterUncreatableType<DbConstants>(uri, 1, 0, "DBC", "Can not create instance of the DB constants");
    qmlRegisterType<Table>();
    qmlRegisterType<LocalitiesTable>(uri, 1, 0, "LocalitiesTable");
    qmlRegisterType<MilkPointsTable>(uri, 1, 0, "MilkPointsTable");
    qmlRegisterType<DeliverersTable>(uri, 1, 0, "DeliverersTable");
    qmlRegisterType<MilkReceptionTable>(uri, 1, 0, "MilkReceptionTable");
    qmlRegisterType<LocalitiesSortFilterProxyModel>(uri, 1, 0, "LocalitiesSortFilterProxyModel");
    qmlRegisterType<MilkPointsSortFilterProxyModel>(uri, 1, 0, "MilkPointsSortFilterProxyModel");
    qmlRegisterType<DeliverersSortFilterProxyModel>(uri, 1, 0, "DeliverersSortFilterProxyModel");
    qmlRegisterType<MilkReceptionSortFilterProxyModel>(uri, 1, 0, "MilkReceptionSortFilterProxyModel");

}
