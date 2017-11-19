#include "SettingsConstants.h"

const QString SettingsConstants::Main::DEF_LAST_CHOOSEN_DB = QString();
const float SettingsConstants::Main::DEF_PRICE_LITER = 0.0f;
const QString SettingsConstants::Main::DEF_FIRM_NAME = QString();
const QString SettingsConstants::Main::DEF_MILK_INSPECTOR = QString();
const QString SettingsConstants::Main::DEF_MILK_INSPECTOR2 = QString();
const bool SettingsConstants::Main::DEF_IS_FETCH_TABLE_ON_REFRESH = false;

const QString SettingsConstants::Column::DEF_DISPLAY = QString();
const int SettingsConstants::Column::DEF_TYPE = -1;
const int SettingsConstants::Column::DEF_PREC = 2;
const bool SettingsConstants::Column::DEF_IS_SHOW = true;

const QFont SettingsConstants::Calc::DEF_TEXT_FONT = QFont();
const QColor SettingsConstants::Calc::DEF_TEXT_BACK_COLOR = {Qt::GlobalColor::white};
const QFont SettingsConstants::Calc::DEF_DELIV_RESULT_FONT = {};
const QColor SettingsConstants::Calc::DEF_DELIV_RESULT_COLOR = {Qt::GlobalColor::darkGray};
const QFont SettingsConstants::Calc::DEF_ALL_RESULT_FONT = {};
const QColor SettingsConstants::Calc::DEF_ALL_RESULT_COLOR = {Qt::GlobalColor::lightGray};

const QFont SettingsConstants::Print::DEF_TEXT_FONT = {"Times", 10, QFont::Normal};
const QFont SettingsConstants::Print::DEF_CAPTION_TEXT_FONT = {"Times", 12, QFont::Bold};
const QColor SettingsConstants::Print::DEF_CAPTION_COLOR = {Qt::black};
const int SettingsConstants::Print::DEF_TABLE_WIDTH = 100;
const int SettingsConstants::Print::DEF_TABLE_BORDER_WIDTH = 2;
const int SettingsConstants::Print::DEF_TABLE_BORDER_STYLE = 3;
const int SettingsConstants::Print::DEF_CELL_SPACING = 0;
const int SettingsConstants::Print::DEF_CELL_PADDING = 2;
const QColor SettingsConstants::Print::DEF_TABLE_BORDER_COLOR = {Qt::black};
const QFont  SettingsConstants::Print::DEF_TABLE_HEADER_FONT = {"Noto Sans", 10, QFont::Bold};
const QColor SettingsConstants::Print::DEF_TABLE_HEADER_COLOR = {Qt::black};
const QFont  SettingsConstants::Print::DEF_TABLE_TEXT_FONT = {"Noto Sans", 9, QFont::Normal};
const QColor SettingsConstants::Print::DEF_TABLE_TEXT_COLOR = {Qt::black};
const QFont  SettingsConstants::Print::DEF_TABLE_RESULT_FONT = {"Noto Sans", 9, QFont::Bold};
const QColor SettingsConstants::Print::DEF_TABLE_RESULT_COLOR = {Qt::black};
