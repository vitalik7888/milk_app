#ifndef TEST_LOCALITIESDAO_H
#define TEST_LOCALITIESDAO_H

#include "DbTests.h"
#include <Locality.h>

DB_BEGIN_NAMESPACE
    class LocalitiesDao;
DB_END_NAMESPACE


class Test_LocalitiesDao : public DbTests
{
    Q_OBJECT
public:
    Test_LocalitiesDao(QObject *parent = Q_NULLPTR);

private slots:
    void initTestCase();
    void cleanupTestCase();

    void tableName();
    void fieldsNames();
    void primaryFieldName();
    void getCreateTableStr();
    void getSetDb();
    void createTable();

    void insert();
    void getIds();
    void getItem();
    void update();
    void updateValues();
    void remove();

private:
    DB_NAMESPACE::LocalitiesDao *m_dao;
    std::unique_ptr<Locality> m_locality;
};

#endif // TEST_LOCALITIESDAO_H
