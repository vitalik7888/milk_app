#include "CalcExporterPlugin.h"

// Qt
#include <QFile>
#include <QTextStream>


CalcExporterPlugin::CalcExporterPlugin(QObject *parent) :
    QObject(parent)
{
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(calcexporter, CalcExporterPlugin)
#endif // QT_VERSION < 0x050000


bool CalcExporterPlugin::exportToCsv(CalculatedItem *root, const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);
    auto addValues = [&out](const std::array<QString, 9> &values) {
        for (const auto &value : values) {
            out << value << ",";
        }
        out << "\n";
    };

    addValues({tr("Сдатчик"), tr("Литры"), tr("Жиры"),
               tr("Белок"), tr("Жироединицы"), tr("Зачет. вес"), tr("Оплата(без премии)"),
               tr("Премия"), tr("Сумма")});

    const int prec = 2;
    for (const auto item : root->getItems()) {
        addValues({item->delivererFullName(),
                   QString::number(item->liters(), 'f', prec),
                   QString::number(item->fat(), 'f', prec),
                   QString::number(item->protein(), 'f', prec),
                   QString::number(item->fatUnits(), 'f', prec),
                   QString::number(item->rankWeight(), 'f', prec),
                   QString::number(item->paymentWithOutPremium(), 'f', prec),
                   QString::number(item->premiumForFat(), 'f', prec),
                   QString::number(item->sum(), 'f', prec)
                  });
    }

    return true;
}
