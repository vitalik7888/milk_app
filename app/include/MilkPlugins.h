#ifndef MILKPLUGINS_H
#define MILKPLUGINS_H

#include <DbExporter.h>
#include <CalcExporter.h>
// Qt
#include <QObject>


class MilkPlugins : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DbExporter* dbExporter READ dbExporter CONSTANT)
    Q_PROPERTY(CalcExporter* calcExporter READ calcExporter CONSTANT)

public:
    explicit MilkPlugins(QObject *parent = nullptr);

    DbExporter *dbExporter() const { return m_dbExporter; }
    CalcExporter *calcExporter() const { return m_calcExporter; }

public slots:
    void load();

private:
    DbExporter *m_dbExporter;
    CalcExporter *m_calcExporter;
};

#endif // MILKPLUGINS_H
