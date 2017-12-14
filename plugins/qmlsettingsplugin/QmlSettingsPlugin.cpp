#include "QmlSettingsPlugin.h"

#include <Settings.h>
// Qt
#include <qqml.h>


#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(qmlsettingsplugin, QmlSettingsPlugin)
#endif // QT_VERSION < 0x050000


void QmlSettingsPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<Settings>(uri, 1, 0, "Settings");
    qmlRegisterType<MainSettings>(uri, 1, 0, "MainSettings");
    qmlRegisterType<CalcSettings>(uri, 1, 0, "CalcSettings");
    qmlRegisterType<PrintSettings>(uri, 1, 0, "PrintSettings");
    qmlRegisterType<SettingsColumn>(uri, 1, 0, "SettingsColumn");
}
