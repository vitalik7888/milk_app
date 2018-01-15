#ifndef ICALCEXPORTER_H
#define ICALCEXPORTER_H

#include <CalculatedItem.h>
// Qt
#include <QtPlugin>


class ICalcExporter {
public:
    ~ICalcExporter() {}

    virtual bool exportToCsv(/*const*/ CalculatedItem *root, const QString& path) = 0;
};

#define ICalcExporter_iid "com.milk.ICalcExporter"

Q_DECLARE_INTERFACE(ICalcExporter, ICalcExporter_iid)

#endif // ICALCEXPORTER_H
