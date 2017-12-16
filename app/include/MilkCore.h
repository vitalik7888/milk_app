#ifndef MILKCORE_H
#define MILKCORE_H

#include "Constants.h"
#include "Database.h"
#include "Settings.h"
#include "CalcItemModel.h"
#include "MilkPlugins.h"

USE_DB_NAMESPACE


class MilkCore : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Settings* settings READ settings CONSTANT)
    Q_PROPERTY(Database* db READ database CONSTANT)
    Q_PROPERTY(MilkPlugins* plugins READ plugins CONSTANT)

public:
    explicit MilkCore(QObject *parent = Q_NULLPTR);
    virtual ~MilkCore();

    Settings *settings() const;
    Database *database() const;

    Q_INVOKABLE CalculatedItem *getCalculations(const QString &where = "");

    Q_INVOKABLE CalcItemModel *getCalcItemModel(const qlonglong delivererId = -1,
                                                const qlonglong milkPointId = -1,
                                                const QDate &dateFrom = QDate(),
                                                const QDate &dateTo = QDate());

    Q_INVOKABLE void printHtml(const QString &html, bool isShowPreview = true);
    Q_INVOKABLE void printCalculations(CalculatedItem *calcItem, bool isShowPreview = true);

    MilkPlugins *plugins() const;

private:
    Settings *m_settings;
    Database *m_database;

    MilkPlugins *m_plugins;
};

#endif // MILKCORE_H
