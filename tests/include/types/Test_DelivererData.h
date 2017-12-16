#ifndef TEST_DELIVERERDATA_H
#define TEST_DELIVERERDATA_H

// Qt
#include <QObject>

class DelivererData;


class Test_DelivererData : public QObject
{
    Q_OBJECT
public:
    explicit Test_DelivererData(QObject *parent = nullptr);

    static void compare(DelivererData *deliverer, const int id, const QString &firstName, const QString &lastName,
                        const int localityId, const QString &inn, const QString &address, const QString &phoneNumber);
    static void compareDefault(DelivererData *deliverer);
    static void compare(DelivererData *left, DelivererData *right);

private slots:
    void emptyConstructor();
    void constructor();
    void copyConstructor();
    void methods();
    void storingInQVariant();
};

#endif // TEST_DELIVERERDATA_H
