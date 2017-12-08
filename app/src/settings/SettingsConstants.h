#ifndef SETTINGSCONSTANTS_H
#define SETTINGSCONSTANTS_H

#include <QColor>
#include <QFont>
#include <QString>


class SettingsColumn;


class SettingsConstants
{
//    Q_GADGET
//    Q_PROPERTY(QString defaultDateFormat READ defaultDateFormat CONSTANT)

public:
    static inline QString defaultDateFormat() { return "yyyy-MM-dd"; }

    enum SettingsColumnType {
        SerialNumber = 1,
        String,
        Double,
        Date
    };

    using SettingsColumns = QVector<SettingsColumn *>;

    static const QString M_DEF_LAST_CHOOSEN_DB;
    static const float M_DEF_PRICE_LITER;
    static const QString M_DEF_FIRM_NAME;
    static const QString M_DEF_MILK_INSPECTOR;
    static const QString M_M_DEF_MILK_INSPECTOR2;
    static const bool M_DEF_IS_FETCH_TABLE_ON_REFRESH;

    static const QString COL_DEF_DISPLAY;
    static const int COL_DEF_TYPE;
    static const int COL_DEF_PREC;
    static const bool COL_DEF_IS_SHOW;

    static const QFont C_DEF_TEXT_FONT;
    static const QColor C_DEF_TEXT_BACK_COLOR;
    static const QFont C_DEF_DELIV_RESULT_FONT;
    static const QColor C_DEF_DELIV_RESULT_COLOR;
    static const QFont C_DEF_ALL_RESULT_FONT;
    static const QColor C_DEF_ALL_RESULT_COLOR;

    static const QFont P_DEF_TEXT_FONT;
    static const QFont P_DEF_CAPTION_TEXT_FONT;
    static const QColor P_DEF_CAPTION_COLOR;
    static const int P_DEF_TABLE_WIDTH;
    static const int P_DEF_TABLE_BORDER_WIDTH;
    static const int P_DEF_TABLE_BORDER_STYLE;
    static const int P_DEF_CELL_SPACING;
    static const int P_DEF_CELL_PADDING;
    static const QColor P_DEF_TABLE_BORDER_COLOR;
    static const QFont P_DEF_TABLE_HEADER_FONT;
    static const QColor P_DEF_TABLE_HEADER_COLOR;
    static const QFont P_DEF_TABLE_TEXT_FONT;
    static const QColor P_DEF_TABLE_TEXT_COLOR;
    static const QFont P_DEF_TABLE_RESULT_FONT;
    static const QColor P_DEF_TABLE_RESULT_COLOR;
};

#endif // SETTINGSCONSTANTS_H
