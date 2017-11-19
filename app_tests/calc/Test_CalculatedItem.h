#ifndef TEST_CALCULATEDITEM_H
#define TEST_CALCULATEDITEM_H

#include <QObject>

class CalculatedItem;


class Test_CalculatedItem : public QObject
{
    Q_OBJECT
public:
    explicit Test_CalculatedItem(QObject *parent = nullptr);

    static void compare(CalculatedItem *ci, const double liters, const double fat,
                        const double priceForLiter);
    static void compareDefault(CalculatedItem *ci);

private slots:
    void testEmptyConstructor();
    void testConstructor();
    void calculatedResult_data();
    void calculatedResult();
    void add();
};

#endif // TEST_CALCULATEDITEM_H
