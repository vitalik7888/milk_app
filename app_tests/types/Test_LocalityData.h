#ifndef TEST_LOCALITYDATA_H
#define TEST_LOCALITYDATA_H

#include "TypesConstants.h"
// Qt
#include <QObject>

class LocalityData;


class Test_LocalityData : public QObject
{
    Q_OBJECT
public:
    explicit Test_LocalityData(QObject *parent = nullptr);

    static void compare(const LocalityData &localityData, const TypesConstants::milk_id id,
                        const QString &name, const QString &description);
    static void compareDefault(const LocalityData &localityData);
    static void compare(const LocalityData &left, const LocalityData &right);

private slots:
    void emptyConstructor();
    void constructor();
    void copyConstructor();
    void methods();
    void storingInQVariant();
};

#endif // TEST_LOCALITYDATA_H
