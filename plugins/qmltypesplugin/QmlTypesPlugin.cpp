#include "QmlTypesPlugin.h"

#include <Locality.h>
#include <MilkPoint.h>
#include <Deliverer.h>
#include <MilkReception.h>
// Qt
#include <qqml.h>


#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(qmltypesplugin, QmlTypesPlugin)
#endif // QT_VERSION < 0x050000


void QmlTypesPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<Locality>(uri, 1, 0, "Locality");
    qmlRegisterType<MilkPoint>(uri, 1, 0, "MilkPoint");
    qmlRegisterType<Deliverer>(uri, 1, 0, "Deliverer");
    qmlRegisterType<MilkReception>(uri, 1, 0, "MilkReception");
}
