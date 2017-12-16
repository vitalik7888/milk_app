#include "calc_plugin.h"

#include <include/CalcItemModel.h>
// Qt
#include <qqml.h>


void CalcPlugin::registerTypes(const char *uri)
{
    // @uri com.milk.calc
    qmlRegisterType<CalculatedItem>(uri, 1, 0, "CalculatedItem");
    qmlRegisterType<CalcItemModel>(uri, 1, 0, "CalcItemModel");
}

