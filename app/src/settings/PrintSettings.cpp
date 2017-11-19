#include "PrintSettings.h"

#include "SettingsColumn.h"

using SC = SettingsConstants;
using SCP = SC::Print;


PrintSettings::PrintSettings(QObject *parent) :
    QObject(parent),
    m_textFont(SCP::DEF_TEXT_FONT),
    m_captionTextFont(SCP::DEF_CAPTION_TEXT_FONT),
    m_captionColor(SCP::DEF_CAPTION_COLOR),
    m_tableWidth(SCP::DEF_TABLE_WIDTH),
    m_tableBorderWidth(SCP::DEF_TABLE_BORDER_WIDTH),
    m_tableBorderStyle(SCP::DEF_TABLE_BORDER_STYLE),
    m_cellSpacing(SCP::DEF_CELL_SPACING),
    m_cellPadding(SCP::DEF_CELL_PADDING),
    m_tableBorderColor(SCP::DEF_TABLE_BORDER_COLOR),
    m_tableHeaderFont(SCP::DEF_TABLE_HEADER_FONT),
    m_tableHeaderColor(SCP::DEF_TABLE_HEADER_COLOR),
    m_tableTextFont(SCP::DEF_TABLE_TEXT_FONT),
    m_tableTextColor(SCP::DEF_TABLE_TEXT_COLOR),
    m_tableResultFont(SCP::DEF_TABLE_RESULT_FONT),
    m_tableResultColor(SCP::DEF_TABLE_RESULT_COLOR)
{

}

PrintSettings::~PrintSettings() {}

void PrintSettings::setTextFont(const QFont &textFont)
{
    if (m_textFont == textFont)
        return;

    m_textFont = textFont;
    emit textFontChanged(m_textFont);
}

void PrintSettings::setCaptionTextFont(const QFont &captionTextFont)
{
    if (m_captionTextFont == captionTextFont)
        return;

    m_captionTextFont = captionTextFont;
    emit captionTextFontChanged(m_captionTextFont);
}

void PrintSettings::setCaptionColor(const QColor &captionColor)
{
    if (m_captionColor == captionColor)
        return;

    m_captionColor = captionColor;
    emit captionColorChanged(m_captionColor);
}

void PrintSettings::setTableWidth(int tableWidth)
{
    if (m_tableWidth == tableWidth)
        return;

    m_tableWidth = tableWidth;
    emit tableWidthChanged(m_tableWidth);
}

void PrintSettings::setTableBorderWidth(int tableBorderWidth)
{
    if (m_tableBorderWidth == tableBorderWidth)
        return;

    m_tableBorderWidth = tableBorderWidth;
    emit tableBorderWidthChanged(m_tableBorderWidth);
}

void PrintSettings::setTableBorderStyle(int tableBorderStyle)
{
    if (m_tableBorderStyle == tableBorderStyle)
        return;

    m_tableBorderStyle = tableBorderStyle;
    emit tableBorderStyleChanged(m_tableBorderStyle);
}

void PrintSettings::setCellSpacing(int cellSpacing)
{
    if (m_cellSpacing == cellSpacing)
        return;

    m_cellSpacing = cellSpacing;
    emit cellSpacingChanged(m_cellSpacing);
}

void PrintSettings::setCellPadding(int cellPadding)
{
    if (m_cellPadding == cellPadding)
        return;

    m_cellPadding = cellPadding;
    emit cellPaddingChanged(m_cellPadding);
}

void PrintSettings::setTableBorderColor(const QColor &tableBorderColor)
{
    if (m_tableBorderColor == tableBorderColor)
        return;

    m_tableBorderColor = tableBorderColor;
    emit tableBorderColorChanged(m_tableBorderColor);
}

void PrintSettings::setTableHeaderFont(const QFont &tableHeaderFont)
{
    if (m_tableHeaderFont == tableHeaderFont)
        return;

    m_tableHeaderFont = tableHeaderFont;
    emit tableHeaderFontChanged(m_tableHeaderFont);
}

void PrintSettings::setTableHeaderColor(const QColor &tableHeaderColor)
{
    if (m_tableHeaderColor == tableHeaderColor)
        return;

    m_tableHeaderColor = tableHeaderColor;
    emit tableHeaderColorChanged(m_tableHeaderColor);
}

void PrintSettings::setTableTextFont(const QFont &tableTextFont)
{
    if (m_tableTextFont == tableTextFont)
        return;

    m_tableTextFont = tableTextFont;
    emit tableTextFontChanged(m_tableTextFont);
}

void PrintSettings::setTableTextColor(const QColor &tableTextColor)
{
    if (m_tableTextColor == tableTextColor)
        return;

    m_tableTextColor = tableTextColor;
    emit tableTextColorChanged(m_tableTextColor);
}

void PrintSettings::setTableResultFont(const QFont &tableResultFont)
{
    if (m_tableResultFont == tableResultFont)
        return;

    m_tableResultFont = tableResultFont;
    emit tableResultFontChanged(m_tableResultFont);
}

void PrintSettings::setTableResultColor(const QColor &tableResultColor)
{
    if (m_tableResultColor == tableResultColor)
        return;

    m_tableResultColor = tableResultColor;
    emit tableResultColorChanged(m_tableResultColor);
}

void PrintSettings::appendSettingsColumn(SettingsColumn *column)
{
    m_columns.append(column);
}

void PrintSettings::appendSettingsColumns(const SettingsConstants::SettingsColumns &columns)
{
    m_columns.append(columns);
}

void PrintSettings::setSettingsColumns(const SettingsConstants::SettingsColumns &columns)
{
    m_columns = columns;
}

int PrintSettings::settingsColumnsCount() const
{
    return m_columns.size();
}

SettingsColumn *PrintSettings::settingColumn(int position) const
{
    return m_columns.at(position);
}

void PrintSettings::clearSettingsColumns()
{
    m_columns.clear();
}

QQmlListProperty<SettingsColumn> PrintSettings::columns()
{
    return QQmlListProperty<SettingsColumn>(this, this,
                                            &PrintSettings::appendSettingsColumn,
                                            &PrintSettings::settingsColumnsCount,
                                            &PrintSettings::settingColumn,
                                            &PrintSettings::clearSettingsColumns);
}

SettingsConstants::SettingsColumns PrintSettings::getColumns() const
{
    return m_columns;
}

void PrintSettings::appendSettingsColumn(QQmlListProperty<SettingsColumn> *list, SettingsColumn *column)
{
    reinterpret_cast< PrintSettings * >(list->data)->appendSettingsColumn(column);
}

int PrintSettings::settingsColumnsCount(QQmlListProperty<SettingsColumn> *list)
{
    return reinterpret_cast< PrintSettings * >(list->data)->settingsColumnsCount();
}

SettingsColumn *PrintSettings::settingColumn(QQmlListProperty<SettingsColumn> *list, int position)
{
    return reinterpret_cast< PrintSettings * >(list->data)->settingColumn(position);
}

void PrintSettings::clearSettingsColumns(QQmlListProperty<SettingsColumn> *list)
{
    reinterpret_cast< PrintSettings * >(list->data)->clearSettingsColumns();
}

void PrintSettings::resetTextFont()
{
    m_textFont = SCP::DEF_TEXT_FONT;
}

void PrintSettings::resetCaptionTextFont()
{
    m_captionTextFont = SCP::DEF_CAPTION_TEXT_FONT;
}

void PrintSettings::resetCaptionColor()
{
    m_captionColor = SCP::DEF_CAPTION_COLOR;
}

void PrintSettings::resetTableWidth()
{
    m_tableWidth = SCP::DEF_TABLE_WIDTH;
}

void PrintSettings::resetTableBorderWidth()
{
    m_tableBorderWidth = SCP::DEF_TABLE_BORDER_WIDTH;
}

void PrintSettings::resetTableBorderStyle()
{
    m_tableBorderStyle = SCP::DEF_TABLE_BORDER_STYLE;
}

void PrintSettings::resetCellSpacing()
{
    m_cellSpacing = SCP::DEF_CELL_SPACING;
}

void PrintSettings::resetCellPadding()
{
    m_cellPadding = SCP::DEF_CELL_PADDING;
}

void PrintSettings::resetTableBorderColor()
{
    m_tableBorderColor = SCP::DEF_TABLE_BORDER_COLOR;
}

void PrintSettings::resetTableHeaderFont()
{
    m_tableHeaderFont = SCP::DEF_TABLE_HEADER_FONT;
}

void PrintSettings::resetTableHeaderColor()
{
    m_tableHeaderColor = SCP::DEF_TABLE_HEADER_COLOR;
}

void PrintSettings::resetTableTextFont()
{
    m_tableTextFont = SCP::DEF_TABLE_TEXT_FONT;
}

void PrintSettings::resetTableTextColor()
{
    m_tableTextColor = SCP::DEF_TABLE_TEXT_COLOR;
}

void PrintSettings::resetTableResultFont()
{
    m_tableResultFont = SCP::DEF_TABLE_RESULT_FONT;
}

void PrintSettings::resetTableResultColor()
{
    m_tableResultColor = SCP::DEF_TABLE_RESULT_COLOR;
}

void PrintSettings::resetColumns()
{
    for (SettingsColumn *column : m_columns)
        column->reset();
}

void PrintSettings::reset()
{
    resetTextFont();
    resetCaptionTextFont();
    resetCaptionColor();
    resetTableWidth();
    resetTableBorderWidth();
    resetTableBorderStyle();
    resetCellSpacing();
    resetCellPadding();
    resetTableBorderColor();
    resetTableHeaderFont();
    resetTableHeaderColor();
    resetTableTextFont();
    resetTableTextColor();
    resetTableResultFont();
    resetTableResultColor();
    resetColumns();
}
