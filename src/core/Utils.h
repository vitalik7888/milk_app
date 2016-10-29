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
    CalcResult(): protein(.0f), fatUnits(.0f), rankWeight(.0f),
        paymentWithOutPremium(.0f), premiumForFat(.0f), sum(.0f) {}

    float protein;
    float fatUnits;
    float rankWeight;
    float paymentWithOutPremium;
    float premiumForFat;
    float sum;
};

static inline float protein(const float fat)
{
    if(fat <= 0)
        return 0.0f;

    return fat * BASE_PROTEIN / BASE_FAT;
}

static inline float fat(const float fatUnits, const float liters) {
    if (fatUnits <= .0f || liters <= .0f)
        return .0f;
    return fatUnits / liters;
}

static inline float liters(const float fatUnits, const float fat) {
    if (fatUnits <= .0f || fat <= .0f)
        return .0f;
    return fatUnits / fat;
}

static inline float fatUnits(const float liters, const float fat)
{
    return liters * fat;
}

static inline float rankWeight(const float fatUnits)
{
    if(fatUnits <= 0)
        return 0.0f;

    return fatUnits / BASE_FAT; //qRound(fatUnits / BASE_FAT);
}

static inline float premiumForFat(const float fat, const float paymentWithOutPremium)
{
    if(fat <= 0)
        return 0.0f;

    return (fat / BASE_FAT - 1) * paymentWithOutPremium;
}

static inline float paymentWithOutPremium(const float liters, const float price)
{
    return liters * price;
}

static inline float sum(const float rankWeight, const float price)
{
    return rankWeight * price;
}
static inline CalcResult getCalculations(const float liters, const float fat, const float price) {
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

