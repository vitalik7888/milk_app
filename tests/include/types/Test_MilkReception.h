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

    static void compare(const MilkReception *mr,const int id, const QDate deliveryDate,
                        const double priceLiter, const double liters, const double fat,
                        const Deliverer *deliverer, const MilkPoint *milkPoint);
    static void compareDefault(const MilkReception *mr);
    static void compare(const MilkReception *left, const MilkReception *right);

private slots:
    void emptyConstructor();
    void constructor();
    void copyConstructor();
    void methods();
    void reset();
    void storingInQVariant();
};

#endif // TEST_MILKRECEPTION_H
