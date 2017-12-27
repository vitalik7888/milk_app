#ifndef DATABASE_H
#define DATABASE_H

#include "DbConstants.h"
#include "LocalitiesModel.h"
#include "DeliverersModel.h"
#include "MilkPointsModel.h"
#include "MilkReceptionModel.h"
// Qt
#include <QtSql/QSqlDatabase>
#include <QSqlError>
#include <QQmlListProperty>

DB_BEGIN_NAMESPACE


class DBLIBRARYSHARED_EXPORT Database : public QObject
{
    Q_OBJECT
    Q_PROPERTY(LocalitiesModel *localities READ localities NOTIFY localitiesChanged)
    Q_PROPERTY(DeliverersModel *deliverers READ deliverers NOTIFY deliverersChanged)
    Q_PROPERTY(MilkPointsModel *milkPoints READ milkPoints NOTIFY milkPointsChanged)
    Q_PROPERTY(MilkReceptionModel *milkReception READ milkReception NOTIFY milkReceptionChanged)
    Q_PROPERTY(QString dbPath READ dbPath NOTIFY dbPathChanged)
    Q_PROPERTY(QQmlListProperty<MilkModel> models READ _models)

public:
    explicit Database(QObject *parent = nullptr);
    virtual ~Database();

    Q_INVOKABLE bool openDb(const QString &dbPath = ":memory:");
    Q_INVOKABLE QSqlError lastError() const;
    Q_INVOKABLE QString choosenDatabase() const;

    QQmlListProperty<MilkModel> _models();
    LocalitiesModel *localities() const;
    DeliverersModel *deliverers() const;
    MilkPointsModel *milkPoints() const;
    MilkReceptionModel *milkReception() const;
    int modelsCount() const;
    Q_INVOKABLE bool isModelsCreated() const;

    QString dbPath() const { return m_dbPath; }

    QSqlDatabase getSqlDb() const;

signals:
    void dbOpened();
    void localitiesChanged(LocalitiesModel * localities);
    void deliverersChanged(DeliverersModel * deliverers);
    void milkPointsChanged(MilkPointsModel * milkPoints);
    void milkReceptionChanged(MilkReceptionModel * milkReception);
    void modelsChanged(QQmlListProperty<MilkModel> _models);
    void dbPathChanged(QString dbPath);

private:
    QSqlDatabase m_db;
    QString m_dbPath;
    QList<MilkModel *> m_models;
    LocalitiesModel *m_localities;
    DeliverersModel *m_deliverers;
    MilkPointsModel *m_milkPoints;
    MilkReceptionModel *m_milkReception;
    std::unique_ptr<DaoSql> m_localitiesDao;
    std::unique_ptr<DaoSql> m_deliverersDao;
    std::unique_ptr<DaoSql> m_milkPointsDao;
    std::unique_ptr<DaoSql> m_milkReceptionDao;

    void createDb(const QString &filePath);

    void createDaos();

    void removeModels();
    void createModels();
    void refreshModels();

    void appendModel(MilkModel *table);
    void clearModels();
    MilkModel *getModel(const int position) const;

    static void _appendModel(QQmlListProperty<MilkModel> *list, MilkModel *table);
    static int _modelsCount(QQmlListProperty<MilkModel> *list);
    static MilkModel *_getModel(QQmlListProperty<MilkModel> *list, int position);
    static void _removeModels(QQmlListProperty<MilkModel> *list);

    void _error(const QString &errorDescription) const;
};

DB_END_NAMESPACE

#endif // DATABASE_H
