#include "settings_plugin.h"

#include <Settings.h>
// Qt
#include <qqml.h>

void SettingsPlugin::registerTypes(const char *uri)
{
    // @uri com.milk.settings
    qmlRegisterType<Settings>(uri, 1, 0, "Settings");
    qmlRegisterType<MainSettings>(uri, 1, 0, "MainSettings");
    qmlRegisterType<CalcSettings>(uri, 1, 0, "CalcSettings");
    qmlRegisterType<PrintSettings>(uri, 1, 0, "PrintSettings");
    qmlRegisterType<SettingsColumn>(uri, 1, 0, "SettingsColumn");
}

