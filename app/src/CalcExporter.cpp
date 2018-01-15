#include "include/CalcExporter.h"

CalcExporter::CalcExporter(QObject *parent) :
    QObject(parent),
    m_calcExporter(Q_NULLPTR)
{

}

bool CalcExporter::exportToCsv(CalculatedItem *root, const QString &path)
{
    if (!m_calcExporter)
        return false;

    return m_calcExporter->exportToCsv(root, path);
}

void CalcExporter::setCalcExporter(ICalcExporter *calcExporter)
{
    m_calcExporter = calcExporter;
}

bool CalcExporter::isNull() const
{
    return m_calcExporter == Q_NULLPTR;
}
