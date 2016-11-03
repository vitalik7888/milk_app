#ifndef UTILS
#define UTILS

#include <QtAlgorithms>
#include <QVariant>
#include "Constants.h"
#include "dbconstants.h"

DB_BEGIN_NAMESPACE
    class Table;
DB_END_NAMESPACE
class QToolButton;
class QWidget;
class QAbstractItemView;
class QComboBox;


namespace Utils {
class Main {
public:
    static bool isAutoIncrIdIsValid(const milk_id id);
    static bool yesNoWarnMsgBox(QWidget *parent, const QString &question);
    static bool showWarnMsgIfNoRows(QWidget *parent, const QString &title, DB_NAMESPACE::Table *table);
    static bool isNeesAddItem(QWidget *parent, DB_NAMESPACE::Table *table);
    static milk_id getIdFromDialog(DB_NAMESPACE::Table *table, const QString &title = QString(),
                                     QWidget *parent = nullptr);
    static QModelIndex getIndexFromModelById(DB_NAMESPACE::Table *table, const int column, const milk_id id);
    static QVariant getCurValueFromComboBoxModel(const QComboBox *combobox, const int column);
    static QVariant getCurValueFromItemViewModel(const QAbstractItemView *itemView, const int column);

    static QString getSelectStr(const QString &tableName, const QStringList &columns);
    static QString getPrepUpdateStr(const QString &tableName, const QStringList &columns);
    static QString getPrepInsertStr(const QString &tableName, const QStringList &columns);

    static void showMsgIfDbNotChoosed(QWidget *parent);
    //    QString selectColumns(const int count, ...) const;
};

namespace Calc {

struct CalcResult {
    CalcResult(): protein(.0), fatUnits(.0), rankWeight(.0),
        paymentWithOutPremium(.0), premiumForFat(.0), sum(.0) {}

    double protein;
    double fatUnits;
    double rankWeight;
    double paymentWithOutPremium;
    double premiumForFat;
    double sum;
};

static inline double protein(const double fat)
{
    if(fat <= 0)
        return 0.0;

    return fat * BASE_PROTEIN / BASE_FAT;
}

static inline double fat(const double fatUnits, const double liters) {
    if (fatUnits <= .0 || liters <= .0)
        return .0;
    return fatUnits / liters;
}

static inline double liters(const double fatUnits, const double fat) {
    if (fatUnits <= .0 || fat <= .0)
        return .0;
    return fatUnits / fat;
}

static inline double fatUnits(const double liters, const double fat)
{
    return liters * fat;
}

static inline double rankWeight(const double fatUnits)
{
    if(fatUnits <= 0)
        return 0.0;

    return fatUnits / BASE_FAT; //qRound(fatUnits / BASE_FAT);
}

static inline double premiumForFat(const double fat, const double paymentWithOutPremium)
{
    if(fat <= 0)
        return 0.0;

    return (fat / BASE_FAT - 1) * paymentWithOutPremium;
}

static inline double paymentWithOutPremium(const double liters, const double price)
{
    return liters * price;
}

static inline double sum(const double rankWeight, const double price)
{
    return rankWeight * price;
}
static inline CalcResult getCalculations(const double liters, const double fat, const double price) {
    CalcResult calc;

    calc.protein = Utils::Calc::protein(fat);
    calc.fatUnits = Utils::Calc::fatUnits(liters, fat);
    calc.rankWeight = Utils::Calc::rankWeight(calc.fatUnits);
    calc.paymentWithOutPremium = Utils::Calc::paymentWithOutPremium(liters, price);
    calc.premiumForFat = Utils::Calc::premiumForFat(fat, calc.paymentWithOutPremium);
    calc.sum = Utils::Calc::sum(calc.rankWeight, price);

    return calc;
}
}
}

#endif // UTILS

