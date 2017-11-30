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

    static void compare(MilkPoint *mp,const int id, const QString &name, const QString &description,
                        Locality *locality);
    static void compareDefault(MilkPoint *mp);
    static void compare(MilkPoint *left, MilkPoint *right);

private slots:
    void emptyConstructor();
    void copyConstructor();
    void constructor();
    void methods();
    void reset();
    void storingInQVariant();
    void signalIdChanged();
    void signalLocalityChanged();
    void signalNameChanged();
    void signalDescriptionChanged();
};

#endif // TEST_MILKPOINT_H
