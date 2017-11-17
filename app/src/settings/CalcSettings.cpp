#include "CalcSettings.h"

#include "SettingsColumn.h"
#include "SettingsConstants.h"

using SC = SettingsConstants;
using SCC = SC::Calc;


CalcSettings::CalcSettings(QObject *parent):
    QObject(parent),
    m_textFont(SCC::DEF_TEXT_FONT),
    m_textBackColor(SCC::DEF_TEXT_BACK_COLOR),
    m_delivResultFont(SCC::DEF_DELIV_RESULT_FONT),
    m_delivResultColor(SCC::DEF_DELIV_RESULT_COLOR),
    m_allResultFont(SCC::DEF_ALL_RESULT_FONT),
    m_allResultColor(SCC::DEF_ALL_RESULT_COLOR),
    m_dateFormat(SC::defaultDateFormat())
{

}

void CalcSettings::setTextFont(const QFont &textFont)
{
    if (m_textFont == textFont)
        return;

    m_textFont = textFont;
    emit textFontChanged(m_textFont);
}

void CalcSettings::setTextBackColor(const QColor &textBackColor)
{
    if (m_textBackColor == textBackColor)
        return;

    m_textBackColor = textBackColor;
    emit textBackColorChanged(m_textBackColor);
}

void CalcSettings::setDelivResultFont(const QFont &delivResultFont)
{
    if (m_delivResultFont == delivResultFont)
        return;

    m_delivResultFont = delivResultFont;
    emit delivResultFontChanged(m_delivResultFont);
}

void CalcSettings::setDelivResultColor(const QColor &delivResultColor)
{
    if (m_delivResultColor == delivResultColor)
        return;

    m_delivResultColor = delivResultColor;
    emit delivResultColorChanged(m_delivResultColor);
}

void CalcSettings::setAllResultFont(const QFont &allResultFont)
{
    if (m_allResultFont == allResultFont)
        return;

    m_allResultFont = allResultFont;
    emit allResultFontChanged(m_allResultFont);
}

void CalcSettings::setAllResultColor(const QColor &allResultColor)
{
    if (m_allResultColor == allResultColor)
        return;

    m_allResultColor = allResultColor;
    emit allResultColorChanged(m_allResultColor);
}

void CalcSettings::setDateFormat(const QString &dateFormat)
{
    if (m_dateFormat == dateFormat)
        return;

    m_dateFormat = dateFormat;
    emit dateFormatChanged(m_dateFormat);
}

void CalcSettings::appendSettingsColumn(SettingsColumn *column)
{
    m_columns.append(column);
}

int CalcSettings::settingsColumnsCount() const
{
    return m_columns.size();
}

SettingsColumn *CalcSettings::settingColumn(int position) const
{
    return m_columns.at(position);
}

void CalcSettings::clearSettingsColumns()
{
    m_columns.clear();
}

QQmlListProperty<SettingsColumn> CalcSettings::columns()
{
    return QQmlListProperty<SettingsColumn>(this, this,
                                            &CalcSettings::appendSettingsColumn,
                                            &CalcSettings::settingsColumnsCount,
                                            &CalcSettings::settingColumn,
                                            &CalcSettings::clearSettingsColumns);
}

void CalcSettings::appendSettingsColumn(QQmlListProperty<SettingsColumn> *list, SettingsColumn *column)
{
    reinterpret_cast< CalcSettings * >(list->data)->appendSettingsColumn(column);
}

int CalcSettings::settingsColumnsCount(QQmlListProperty<SettingsColumn> *list)
{
    return reinterpret_cast< CalcSettings * >(list->data)->settingsColumnsCount();
}

SettingsColumn *CalcSettings::settingColumn(QQmlListProperty<SettingsColumn> *list, int position)
{
    return reinterpret_cast< CalcSettings * >(list->data)->settingColumn(position);
}

void CalcSettings::clearSettingsColumns(QQmlListProperty<SettingsColumn> *list)
{
    reinterpret_cast< CalcSettings * >(list->data)->clearSettingsColumns();
}

void CalcSettings::resetTextFont()
{
    m_textFont = SCC::DEF_TEXT_FONT;
}

void CalcSettings::resetTextBackColor()
{
    m_textBackColor = SCC::DEF_TEXT_BACK_COLOR;
}

void CalcSettings::resetDelivResultFont()
{
    m_delivResultFont = SCC::DEF_DELIV_RESULT_FONT;
}

void CalcSettings::resetDelivResultColor()
{
    m_delivResultColor = SCC::DEF_DELIV_RESULT_COLOR;
}

void CalcSettings::resetAllResultFont()
{
    m_allResultFont = SCC::DEF_ALL_RESULT_FONT;
}

void CalcSettings::resetAllResultColor()
{
    m_allResultColor = SCC::DEF_ALL_RESULT_COLOR;
}

void CalcSettings::resetDateFormat()
{
    m_dateFormat = SC::defaultDateFormat();
}

void CalcSettings::resetColumns()
{
    for (SettingsColumn *column : m_columns)
        column->reset();
}

void CalcSettings::reset()
{
    resetTextFont();
    resetTextBackColor();
    resetDelivResultFont();
    resetDelivResultColor();
    resetAllResultFont();
    resetAllResultColor();
    resetDateFormat();
}
