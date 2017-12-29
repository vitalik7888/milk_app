#ifndef DBTESTS_H
#define DBTESTS_H

#include <DbConstants.h>
#include <memory>
// Qt
#include <QObject>
#include <QSqlDatabase>


class DbTests : public QObject
{
    Q_OBJECT
public:
    explicit DbTests(QObject *parent = nullptr);

protected:
    QSqlDatabase m_db;

    void initDb();
    void execVerifyQuery(const QString &query) const;
};

#endif // DBTESTS_H
