#ifndef MILKPLUGINS_H
#define MILKPLUGINS_H

#include <DbExporter.h>
// Qt
#include <QObject>


class MilkPlugins : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DbExporter* dbExporter READ dbExporter CONSTANT)

public:
    explicit MilkPlugins(QObject *parent = nullptr);

    DbExporter *dbExporter() const;

public slots:
    void load();

private:
    DbExporter *m_dbExporter;
};

#endif // MILKPLUGINS_H
