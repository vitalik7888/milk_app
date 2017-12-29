#ifndef TEST_LOCALITY_H
#define TEST_LOCALITY_H

// Qt
#include <QObject>

class Locality;


class Test_Locality : public QObject
{
    Q_OBJECT
public:
    explicit Test_Locality(QObject *parent = nullptr);

    static void compare(const Locality *locality, const int id, const QString &name, const QString &description);
    static void compareDefault(const Locality *locality);
    static void compare(const Locality *left, const Locality *right);

private slots:
    void emptyConstructor();
    void copyConstructor();
    void constructor();
    void methods();
    void reset();
    void storingInQVariant();
};

#endif // TEST_LOCALITY_H
