#ifndef GENERICPLUGIN_H
#define GENERICPLUGIN_H

#include <ICalcExporter.h>
// Qt
#include <QObject>


class CalcExporterPlugin : public QObject, public ICalcExporter
{
    Q_OBJECT

#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QGenericPluginFactoryInterface" FILE "calcexporter.json")
#endif // QT_VERSION >= 0x050000

    Q_INTERFACES(ICalcExporter)

public:
    CalcExporterPlugin(QObject *parent = Q_NULLPTR);

    Q_INVOKABLE bool exportToCsv(CalculatedItem *root, const QString &path) Q_DECL_OVERRIDE;
};

#endif // GENERICPLUGIN_H
