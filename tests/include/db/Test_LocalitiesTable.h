#ifndef TEST_LOCALITIESTABLE_H
#define TEST_LOCALITIESTABLE_H

#include "DbTests.h"


class Test_LocalitiesTable : public DbTests
{
    Q_OBJECT
public:
    explicit Test_LocalitiesTable(QObject *parent = nullptr);

private slots:
    void initTestCase();
    void cleanupTestCase();
};

#endif // TEST_LOCALITIESTABLE_H
