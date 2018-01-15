#ifndef CALCEXPORTER_H
#define CALCEXPORTER_H

#include "ICalcExporter.h"
// Qt
#include <QObject>

class CalcExporter : public QObject, public ICalcExporter
{
    Q_OBJECT
    Q_INTERFACES(ICalcExporter)

public:
    explicit CalcExporter(QObject *parent = nullptr);

    Q_INVOKABLE bool exportToCsv(CalculatedItem *root, const QString &path) Q_DECL_OVERRIDE;

    void setCalcExporter(ICalcExporter *calcExporter);

    Q_INVOKABLE bool isNull() const;

private:
    ICalcExporter *m_calcExporter;
};

#endif // CALCEXPORTER_H
