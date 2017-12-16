#ifndef TEST_CALCUTILS_H
#define TEST_CALCUTILS_H

#include <QObject>

class Test_CalcUtils : public QObject
{
    Q_OBJECT
public:
    explicit Test_CalcUtils(QObject *parent = nullptr);

private slots:
    void protein_data();
    void protein();
    void fat_data();
    void fat();
    void liters_data();
    void liters();
    void fatUnits_data();
    void fatUnits();
    void rankWeight_data();
    void rankWeight();
    void premiumForFat_data();
    void premiumForFat();
    void paymentWithOutPremium_data();
    void paymentWithOutPremium();
    void sum_data();
    void sum();
};

#endif // TEST_CALCUTILS_H
