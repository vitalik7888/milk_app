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

    static void compare(Deliverer *deliverer, const int id, const QString &firstName, const QString &lastName,
                        Locality *locality, const QString &inn, const QString &address, const QString &phoneNumber);
    static void compareDefault(Deliverer *deliverer);
    static void compare(Deliverer *left, Deliverer *right);

private slots:
    void emptyConstructor();
    void copyConstructor();
    void constructor();
    void methods();
    void storingInQVariant();
    void reset();
    void signalIdChanged();
    void signalLocalityChanged();
    void signalFirstNameChanged();
    void signalLastNameChanged();
    void signalInnChanged();
    void signalAddressChanged();
    void signalPhoneNumberChanged();
};

#endif // TEST_DELIVERER_H
