#ifndef DELIVERERSDAO_H
#define DELIVERERSDAO_H

#include "dbconstants.h"
// Qt
#include <QSqlDatabase>

DB_BEGIN_NAMESPACE

class DeliverersDao {
public:
    DeliverersDao(const QSqlDatabase db = QSqlDatabase()) {}

private:
    QSqlDatabase m_db;
};

DB_END_NAMESPACE

#endif // DELIVERERSDAO_H
