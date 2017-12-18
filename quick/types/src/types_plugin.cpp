#include "types_plugin.h"

#include <Locality.h>
#include <MilkPoint.h>
#include <Deliverer.h>
#include <MilkReception.h>
// Qt
#include <qqml.h>


void TypesPlugin::registerTypes(const char *uri)
{
    // @uri com.milk.types
    qmlRegisterInterface<IMilkBaseType>("IMilkBaseType");
    qmlRegisterInterface<IDeliverer>("IDeliverer");
    qmlRegisterType<Locality>(uri, 1, 0, "Locality");
    qmlRegisterType<MilkPoint>(uri, 1, 0, "MilkPoint");
    qmlRegisterType<Deliverer>(uri, 1, 0, "Deliverer");
    qmlRegisterType<MilkReception>(uri, 1, 0, "MilkReception");
}

