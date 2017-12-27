#include "types_plugin.h"

#include <MilkBaseItem.h>
#include <Deliverer.h>
#include <Locality.h>
#include <MilkPoint.h>
#include <MilkReception.h>
// Qt
#include <qqml.h>


void TypesPlugin::registerTypes(const char *uri)
{
    // @uri com.milk.types
    qRegisterMetaType<MILK_ID>("MILK_ID");

    qmlRegisterInterface<MilkBaseItem>("MilkBaseItem");
    qmlRegisterInterface<LocalityData>("LocalityData");
    qmlRegisterInterface<MilkPointData>("MilkPointData");
    qmlRegisterInterface<DelivererData>("DelivererData");
    qmlRegisterInterface<MilkReceptionData>("MilkReceptionData");
    qmlRegisterInterface<Locality>( "Locality");
    qmlRegisterInterface<MilkPoint>("MilkPoint");
    qmlRegisterInterface<Deliverer>("Deliverer");
    qmlRegisterInterface<MilkReception>("MilkReception");
}

