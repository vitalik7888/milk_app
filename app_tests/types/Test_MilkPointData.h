#ifndef TEST_MILKPOINTDATA_H
#define TEST_MILKPOINTDATA_H

#include "TypesConstants.h"
// Qt
#include <QObject>

class MilkPointData;


class Test_MilkPointData : public QObject
{
    Q_OBJECT
public:
    explicit Test_MilkPointData(QObject *parent = nullptr);

    static void compare(const MilkPointData &mpd, const TypesConstants::milk_id id,
                        const TypesConstants::milk_id localityId, const QString &name, const QString &description);
    static void compareDefault(const MilkPointData &mpd);
    static void compare(const MilkPointData &left, const MilkPointData &right);

private slots:
    void emptyConstructor();
    void constructor();
    void copyConstructor();
    void methods();
    void storingInQVariant();
};

#endif // TEST_MILKPOINTDATA_H
