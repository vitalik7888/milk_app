#ifndef TEST_DBLOCALITY_H
#define TEST_DBLOCALITY_H

#include "DbTests.h"

DB_BEGIN_NAMESPACE
    class LocalitiesModel;
    class DbLocality;
DB_END_NAMESPACE


class Test_DbLocality : public DbTests
{
    Q_OBJECT
public:
    explicit Test_DbLocality(QObject *parent = nullptr);

private slots:
    void initTestCase();
    void cleanupTestCase();

    void setGetModel();
    void setItem();
    void loadData();
    void getPositionInModel();
    void setMilkId();
    void setName();
    void setDescription();
    void reset();
    void save();
    void saveValues();
    void remove();
    void append();

private:
    DB_NAMESPACE::DbLocality *m_dbItem;
    DB_NAMESPACE::LocalitiesModel *m_model;
};

#endif // TEST_DBLOCALITY_H
