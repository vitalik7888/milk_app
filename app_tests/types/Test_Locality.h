#ifndef TEST_LOCALITY_H
#define TEST_LOCALITY_H

#include "TypesConstants.h"
// Qt
#include <QObject>

class Locality;


class Test_Locality : public QObject
{
    Q_OBJECT
public:
    explicit Test_Locality(QObject *parent = nullptr);

    static void compare(Locality *locality, const TypesConstants::milk_id id,
                        const QString &name, const QString &description);
    static void compareDefault(Locality *locality);
    static void compare(Locality *left, Locality *right);

private slots:
    void emptyConstructor();
    void copyConstructor();
    void constructor();
    void methods();
    void reset();
    void storingInQVariant();
    void signalIdChanged();
    void signalNameChanged();
    void signalDescriptionChanged();
};

#endif // TEST_LOCALITY_H
