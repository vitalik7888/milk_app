#ifndef MILKCORE_H
#define MILKCORE_H

#include "Constants.h"
#include "src/database/base/Database.h"
#include "Settings.h"
#include "CalcItemModel.h"
// Qt
#include <QObject>

class MilkCore : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Settings* settings READ settings CONSTANT)
    Q_PROPERTY(DB_NAMESPACE::Database* db READ database CONSTANT)

public:
    explicit MilkCore(QObject *parent = Q_NULLPTR);
    virtual ~MilkCore();

    Settings *settings() const;
    DB_NAMESPACE::Database *database() const;

    CalculatedItem *getCalculations(const QString &where = "");

    Q_INVOKABLE CalcItemModel *getCalcItemModel(const qlonglong delivererId = -1,
                                                const qlonglong milkPointId = -1,
                                                const QDate &dateFrom = QDate(),
                                                const QDate &dateTo = QDate());
private:
    Settings *m_settings;
    DB_NAMESPACE::Database *m_database;
};

#endif // MILKCORE_H
