#ifndef TEST_DELIVERER_H
#define TEST_DELIVERER_H

// Qt
#include <QObject>

class DelivererData;
class Deliverer;
class Locality;


class Test_Deliverer : public QObject
{
    Q_OBJECT
public:
    explicit Test_Deliverer(QObject *parent = nullptr);

    static void compare(const Deliverer *deliverer, const int id, const QString &firstName,
                        const QString &lastName, const Locality *locality, const QString &inn,
                        const QString &address, const QString &phoneNumber);
    static void compareDefault(const Deliverer *deliverer);
    static void compare(const Deliverer *left, const Deliverer *right);

private slots:
    void emptyConstructor();
    void copyConstructor();
    void constructor();
    void methods();
    void storingInQVariant();
    void reset();
};

#endif // TEST_DELIVERER_H
