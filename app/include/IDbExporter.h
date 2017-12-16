#ifndef IDBUTILS_H
#define IDBUTILS_H

#include <QSqlDatabase>
#include <QtPlugin>
#include <QString>


class IDbExporter {
public:
    ~IDbExporter() {}

    virtual void setDb(const QSqlDatabase &db = QSqlDatabase()) = 0;

    virtual bool dump() const = 0;

    virtual void setType(const QString &type) = 0;
    virtual QString type() const = 0;
    virtual QStringList types() const = 0;

    virtual void setFilePath(const QString &filePath) = 0;
    virtual QString filePath() const = 0;

    virtual QStringList tables() const = 0;
    virtual void setTables(const QStringList &tables) = 0;
};

#define IDbExporter_iid "com.milk.IDbExporter"

Q_DECLARE_INTERFACE(IDbExporter, IDbExporter_iid)

#endif // IDBUTILS_H
