#ifndef TEST_MILKPOINT_H
#define TEST_MILKPOINT_H

// Qt
#include <QObject>

class MilkPoint;
class MilkPointData;
class Locality;


class Test_MilkPoint : public QObject
{
    Q_OBJECT
public:
    explicit Test_MilkPoint(QObject *parent = nullptr);

    static void compare(const MilkPoint *mp,const int id, const QString &name, const QString &description,
                        const Locality *locality);
    static void compareDefault(const MilkPoint *mp);
    static void compare(const MilkPoint *left, const MilkPoint *right);

private slots:
    void emptyConstructor();
    void copyConstructor();
    void constructor();
    void methods();
    void reset();
    void storingInQVariant();
};

#endif // TEST_MILKPOINT_H
