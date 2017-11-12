#ifndef CONSTANTS_H
#define CONSTANTS_H

// Qt
#include <QString>


class Constants
{
public:
    static inline QString appName() { return "MilkApp"; }
    static inline QString organization() { return "VitaliyDev"; }

    static inline QString defaultMilkDbSuffix() { return "mdb"; }

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
        return { 0, 3, 0 };
    }
};

#endif // CONSTANTS_H
