#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

using price = double;


class Constants
{
public:
    constexpr static double BASE_PROTEIN = 3.0;
    constexpr static double BASE_FAT = 3.4;

    static inline QString appName() { return "MilkApp"; }
    static inline QString organization() { return "VitaliyDev"; }

    static inline QString defaultMilkDbSuffix() { return "mdb"; }

    static inline QString defaultDateFormat() { return "yyyy-MM-dd"; }

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
        QString toString() const {
            return QString("%1.%2.%3").arg(vMajor).arg(vMinor).arg(vBuild);
        }

        int vMajor = 0;
        int vMinor = 0;
        int vBuild = 0;
    };

    static const inline Version getCurrentVersion() {
        return { 0, 2, 1 };
    }
};

#endif // CONSTANTS_H
