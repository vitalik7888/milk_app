#ifndef TEST_LOCALITIESTABLE_H
#define TEST_LOCALITIESTABLE_H

#include "DbTests.h"

DB_BEGIN_NAMESPACE
class LocalitiesModel;
DB_END_NAMESPACE

class Test_LocalitiesModel : public DbTests
{
    Q_OBJECT
public:
    explicit Test_LocalitiesModel(QObject *parent = nullptr);

private slots:
    void initTestCase();
    void cleanupTestCase();

    void setGetDao();
    void append_data();
    void append();
    void getPositionById();
    void getItemByIndex();
    void getItemById();
    void getItemsByIds();
    void update();
    void removeById();

    void refresh();
    void clear();

private:
    DB_NAMESPACE::LocalitiesModel *m_model;
};

#endif // TEST_LOCALITIESTABLE_H
