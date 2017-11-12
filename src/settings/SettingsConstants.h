#ifndef SETTINGSCONSTANTS_H
#define SETTINGSCONSTANTS_H

#include <QColor>
#include <QFont>
#include <QString>

class SettingsConstants
{
public:
    constexpr static double BASE_PROTEIN = 3.0;
    constexpr static double BASE_FAT = 3.4;

    static inline QString defaultDateFormat() { return "yyyy-MM-dd"; }

    enum SettingsColumnType {
        SerialNumber = 1,
        String,
        Double,
        Date
    };

    static const QString DEF_LAST_CHOOSEN_DB;
    static const float DEF_PRICE_LITER;
    static const QString DEF_FIRM_NAME;
    static const QString DEF_MILK_INSPECTOR;
    static const QString DEF_MILK_INSPECTOR2;
    static const bool DEF_IS_FETCH_TABLE_ON_REFRESH;

    class Column {
      public:
        static const QString DEF_DISPLAY;
        static const int DEF_TYPE;
        static const int DEF_PREC;
        static const bool DEF_IS_SHOW;
    };

    class Calc {
    public:
        static const QFont DEF_TEXT_FONT;
        static const QColor DEF_TEXT_BACK_COLOR;
        static const QFont DEF_DELIV_RESULT_FONT;
        static const QColor DEF_DELIV_RESULT_COLOR;
        static const QFont DEF_ALL_RESULT_FONT;
        static const QColor DEF_ALL_RESULT_COLOR;
    };


    class Print {
      public:
        static const QFont DEF_TEXT_FONT;
        static const QFont DEF_CAPTION_TEXT_FONT;
        static const QColor DEF_CAPTION_COLOR;
        static const int DEF_TABLE_WIDTH;
        static const int DEF_TABLE_BORDER_WIDTH;
        static const int DEF_TABLE_BORDER_STYLE;
        static const int DEF_CELL_SPACING;
        static const int DEF_CELL_PADDING;
        static const QColor DEF_TABLE_BORDER_COLOR;
        static const QFont DEF_TABLE_HEADER_FONT;
        static const QColor DEF_TABLE_HEADER_COLOR;
        static const QFont DEF_TABLE_TEXT_FONT;
        static const QColor DEF_TABLE_TEXT_COLOR;
        static const QFont DEF_TABLE_RESULT_FONT;
        static const QColor DEF_TABLE_RESULT_COLOR;
    };
};

#endif // SETTINGSCONSTANTS_H
