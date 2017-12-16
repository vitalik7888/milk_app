#ifndef SQLITE3DBUTILS_H
#define SQLITE3DBUTILS_H

#include <IDbExporter.h>
// Qt
#include <QObject>
#include <QQmlListProperty>


class DbExporter : public QObject, public IDbExporter
{
    Q_OBJECT
    Q_INTERFACES(IDbExporter)
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged)
    Q_PROPERTY(QStringList types READ types CONSTANT)
    Q_PROPERTY(QStringList tables READ tables WRITE setTables NOTIFY tablesChanges)

public:
    explicit DbExporter(QObject *parent = nullptr);

    void setDbExporter(IDbExporter *dbExporter);
    Q_INVOKABLE bool isNull() const;

    virtual void setDb(const QSqlDatabase &db) Q_DECL_OVERRIDE;

    Q_INVOKABLE bool dump() const Q_DECL_OVERRIDE;

    virtual QString type() const Q_DECL_OVERRIDE;
    virtual QStringList types() const Q_DECL_OVERRIDE;

    QString filePath() const Q_DECL_OVERRIDE;

    QStringList tables() const Q_DECL_OVERRIDE;

public slots:
    void setType(const QString &type) Q_DECL_OVERRIDE;
    void setFilePath(const QString &filePath) Q_DECL_OVERRIDE;
    void setTables(const QStringList &tables) Q_DECL_OVERRIDE;

signals:
    void typeChanged(QString type);
    void filePathChanged(QString filePath);
    void tablesChanges(QStringList tables);

private:
    IDbExporter *m_dbExporter;
    QStringList m_tables;
};

#endif // SQLITE3DBUTILS_H
