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

    static void compare(const DelivererData *deliverer, const int id, const QString &firstName, const QString &lastName,
                        const int localityId, const QString &inn, const QString &address, const QString &phoneNumber);
    static void compareDefault(const DelivererData *deliverer);
    static void compare(const DelivererData *left, const DelivererData *right);

private slots:
    void emptyConstructor();
    void constructor();
    void copyConstructor();
    void methods();
    void storingInQVariant();
};

#endif // TEST_DELIVERERDATA_H
