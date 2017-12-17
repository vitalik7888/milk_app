#ifndef SQLITE3DBUTILSPLUGIN_H
#define SQLITE3DBUTILSPLUGIN_H

#include "IDbExporter.h"
// Qt
#include <QObject>

class QFile;


class DbExporterPlugin : public QObject, public IDbExporter
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "com.milk.IDbExporter" FILE "dbexporterplugin.json")
#endif // QT_VERSION >= 0x050000
    Q_INTERFACES(IDbExporter)

public:
    virtual void setDb(const QSqlDatabase &db) Q_DECL_OVERRIDE;
    virtual bool dump() const Q_DECL_OVERRIDE;

    virtual void setType(const QString &type) Q_DECL_OVERRIDE;
    virtual QString type() const Q_DECL_OVERRIDE;
    virtual QStringList types() const Q_DECL_OVERRIDE;

    QString filePath() const Q_DECL_OVERRIDE;
    void setFilePath(const QString &filePath) Q_DECL_OVERRIDE;

    QStringList tables() const Q_DECL_OVERRIDE;
    void setTables(const QStringList &tables) Q_DECL_OVERRIDE;

private:
    QSqlDatabase m_db;
    QString m_type;
    QString m_filePath;
    QList<QString> m_tables;

    bool toJson(QFile &file) const;
    bool toCsv( QFile &file) const;
};

#endif // SQLITE3DBUTILSPLUGIN_H
