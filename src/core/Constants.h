#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

#define BASE_PROTEIN 3.0f
#define BASE_FAT 3.4f

class Constants
{
public:
    static QString appName();
    static QString organization();

    static QString defaultMilkDbSuffix();

    static QString defaultDateFormat();

    enum class ColumnType: int {
        SerialNumber = 1,
        String,
        Double,
        Date
    };

    enum PrintColumns {
        SerialNumber = 0,
        DeliverersName,
        Liters,
        Fat,
        Protein,
        FatUnits,
        RankWeight,
        PayWithOutPrem,
        Premium,
        Sum,
        Sign
    };

    struct Version {
        Version(): vMajor(0), vMinor(0), vBuild(0) {}
        Version(const int _major, const int _minor, const int _build):
            vMajor(_major), vMinor(_minor), vBuild(_build) {}

        QString toString() {
            return QString("%1.%2.%3").arg(vMajor).arg(vMinor).arg(vBuild);
        }

        int vMajor;
        int vMinor;
        int vBuild;
    };

    static inline Version getCurrentVersion() {
        return Version(0, 0, 4);
    }
};

#endif // CONSTANTS_H
