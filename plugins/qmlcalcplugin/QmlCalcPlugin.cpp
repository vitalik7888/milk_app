#include "QmlCalcPlugin.h"

#include "CalcItemModel.h"
// Qt
#include <qqml.h>



#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(qmlcalcplugin, QmlCalcPlugin)
#endif // QT_VERSION < 0x050000


void QmlCalcPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<CalculatedItem>(uri, 1, 0, "CalculatedItem");
    qmlRegisterType<CalcItemModel>(uri, 1, 0, "CalcItemModel");
}
