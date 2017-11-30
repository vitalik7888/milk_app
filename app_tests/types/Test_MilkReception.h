#ifndef TEST_MILKRECEPTION_H
#define TEST_MILKRECEPTION_H

// Qt
#include <QObject>

class MilkReceptionData;
class MilkReception;
class MilkPoint;
class Deliverer;


class Test_MilkReception : public QObject
{
    Q_OBJECT
public:
    explicit Test_MilkReception(QObject *parent = nullptr);

    static void compare(MilkReception *mr,const int id, const QDate deliveryDate,
                        const double priceLiter, const double liters, const double fat,
                        Deliverer *deliverer, MilkPoint *milkPoint);
    static void compareDefault(MilkReception *mr);
    static void compare(MilkReception *left, MilkReception *right);

private slots:
    void emptyConstructor();
    void constructor();
    void copyConstructor();
    void methods();
    void reset();
    void storingInQVariant();
    void signalIdChanged();
    void signalDeliveryDateChanged();
    void signalPriceLiterChanged();
    void signalLitersChanged();
    void signalFatChanged();
    void signalDelivererChanged();
    void signalMilkPointChanged();
};

#endif // TEST_MILKRECEPTION_H
