#ifndef QMLSETTINGSPLUGIN_H
#define QMLSETTINGSPLUGIN_H

#include <QQmlExtensionPlugin>


class QmlDbPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)
#endif // QT_VERSION >= 0x050000

public:
    virtual void registerTypes(const char *uri) Q_DECL_OVERRIDE;
};

#endif // QMLSETTINGSPLUGIN_H
