#ifndef UTILS
#define UTILS

#include "Constants.h"
#include "SettingsConstants.h"
#include "dbconstants.h"


namespace Utils {
class Main {
public:
    static bool isAutoIncrIdIsValid(const milk_id id);

    static QString getSelectStr(const QString &tableName, const QStringList &columns);
    static QString getPrepUpdateStr(const QString &tableName, const QStringList &columns);
    static QString getPrepInsertStr(const QString &tableName, const QStringList &columns);
};

}

#endif // UTILS

