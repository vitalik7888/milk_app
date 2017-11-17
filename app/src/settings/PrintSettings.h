#ifndef PRINTSETTINGS_H
#define PRINTSETTINGS_H

// Qt
#include <QVector>
#include <QQmlListProperty>
#include <QColor>
#include <QFont>

class SettingsColumn;


class PrintSettings : public QObject {
    Q_OBJECT
    Q_PROPERTY(QFont textFont READ textFont WRITE setTextFont NOTIFY textFontChanged RESET resetTextFont)
    Q_PROPERTY(QFont captionTextFont READ captionTextFont WRITE setCaptionTextFont NOTIFY captionTextFontChanged RESET resetCaptionTextFont)
    Q_PROPERTY(QColor captionColor READ captionColor WRITE setCaptionColor NOTIFY captionColorChanged RESET resetCaptionColor RESET resetCaptionColor)
    Q_PROPERTY(int tableWidth READ tableWidth WRITE setTableWidth NOTIFY tableWidthChanged RESET resetTableWidth RESET resetTableWidth)
    Q_PROPERTY(int tableBorderWidth READ tableBorderWidth WRITE setTableBorderWidth NOTIFY tableBorderWidthChanged RESET resetTableBorderWidth)
    Q_PROPERTY(int tableBorderStyle READ tableBorderStyle WRITE setTableBorderStyle NOTIFY tableBorderStyleChanged RESET resetTableBorderStyle)
    Q_PROPERTY(int cellSpacing READ cellSpacing WRITE setCellSpacing NOTIFY cellSpacingChanged RESET resetCellSpacing)
    Q_PROPERTY(int cellPadding READ cellPadding WRITE setCellPadding NOTIFY cellPaddingChanged RESET resetCellPadding)
    Q_PROPERTY(QColor tableBorderColor READ tableBorderColor WRITE setTableBorderColor NOTIFY tableBorderColorChanged RESET resetTableBorderColor)
    Q_PROPERTY(QFont tableHeaderFont READ tableHeaderFont WRITE setTableHeaderFont NOTIFY tableHeaderFontChanged RESET resetTableHeaderFont)
    Q_PROPERTY(QColor tableHeaderColor READ tableHeaderColor WRITE setTableHeaderColor NOTIFY tableHeaderColorChanged RESET resetTableHeaderColor)
    Q_PROPERTY(QFont tableTextFont READ tableTextFont WRITE setTableTextFont NOTIFY tableTextFontChanged RESET resetTableTextFont)
    Q_PROPERTY(QColor tableTextColor READ tableTextColor WRITE setTableTextColor NOTIFY tableTextColorChanged RESET resetTableTextColor)
    Q_PROPERTY(QFont tableResultFont READ tableResultFont WRITE setTableResultFont NOTIFY tableResultFontChanged RESET resetTableResultFont)
    Q_PROPERTY(QColor tableResultColor READ tableResultColor WRITE setTableResultColor NOTIFY tableResultColorChanged RESET resetTableResultColor)
    Q_PROPERTY(QQmlListProperty<SettingsColumn> columns READ columns RESET resetColumns)

public:
    explicit PrintSettings(QObject *parent = Q_NULLPTR);
    virtual ~PrintSettings();

    QFont textFont() const { return m_textFont; }
    QFont captionTextFont() const { return m_captionTextFont; }
    QColor captionColor() const { return m_captionColor; }
    int tableWidth() const { return m_tableWidth; }
    int tableBorderWidth() const { return m_tableBorderWidth; }
    int tableBorderStyle() const { return m_tableBorderStyle; }
    int cellSpacing() const { return m_cellSpacing; }
    int cellPadding() const { return m_cellPadding; }
    QColor tableBorderColor() const { return m_tableBorderColor; }
    QFont tableHeaderFont() const { return m_tableHeaderFont; }
    QColor tableHeaderColor() const { return m_tableHeaderColor; }
    QFont tableTextFont() const { return m_tableTextFont; }
    QColor tableTextColor() const { return m_tableTextColor; }
    QFont tableResultFont() const { return m_tableResultFont; }
    QColor tableResultColor() const { return m_tableResultColor; }
    QQmlListProperty<SettingsColumn> columns();

    void appendSettingsColumn(SettingsColumn *column);
    int settingsColumnsCount() const;
    SettingsColumn *settingColumn(int position) const;
    void clearSettingsColumns();

public slots:
    void setTextFont(const QFont &textFont);
    void setCaptionTextFont(const QFont &captionTextFont);
    void setCaptionColor(const QColor &captionColor);
    void setTableWidth(int tableWidth);
    void setTableBorderWidth(int tableBorderWidth);
    void setTableBorderStyle(int tableBorderStyle);
    void setCellSpacing(int cellSpacing);
    void setCellPadding(int cellPadding);
    void setTableBorderColor(const QColor &tableBorderColor);
    void setTableHeaderFont(const QFont &tableHeaderFont);
    void setTableHeaderColor(const QColor &tableHeaderColor);
    void setTableTextFont(const QFont &tableTextFont);
    void setTableTextColor(const QColor &tableTextColor);
    void setTableResultFont(const QFont &tableResultFont);
    void setTableResultColor(const QColor &tableResultColor);
    void reset();

signals:
    void textFontChanged(QFont textFont);
    void captionTextFontChanged(QFont captionTextFont);
    void captionColorChanged(QColor captionColor);
    void tableWidthChanged(int tableWidth);
    void tableBorderWidthChanged(int tableBorderWidth);
    void tableBorderStyleChanged(int tableBorderStyle);
    void cellSpacingChanged(int cellSpacing);
    void cellPaddingChanged(int cellPadding);
    void tableBorderColorChanged(QColor tableBorderColor);
    void tableHeaderFontChanged(QFont tableHeaderFont);
    void tableHeaderColorChanged(QColor tableHeaderColor);
    void tableTextFontChanged(QFont tableTextFont);
    void tableTextColorChanged(QColor tableTextColor);
    void tableResultFontChanged(QFont tableResultFont);
    void tableResultColorChanged(QColor tableResultColor);

private:
    QFont m_textFont;
    QFont m_captionTextFont;
    QColor m_captionColor;
    int m_tableWidth;
    int m_tableBorderWidth;
    int m_tableBorderStyle;
    int m_cellSpacing;
    int m_cellPadding;
    QColor m_tableBorderColor;
    QFont m_tableHeaderFont;
    QColor m_tableHeaderColor;
    QFont m_tableTextFont;
    QColor m_tableTextColor;
    QFont m_tableResultFont;
    QColor m_tableResultColor;
    QVector<SettingsColumn *> m_columns;

    static void appendSettingsColumn(QQmlListProperty<SettingsColumn> *list, SettingsColumn *column);
    static int settingsColumnsCount(QQmlListProperty<SettingsColumn> *list);
    static SettingsColumn* settingColumn(QQmlListProperty<SettingsColumn> *list, int position);
    static void clearSettingsColumns(QQmlListProperty<SettingsColumn> *list);

    void resetTextFont();
    void resetCaptionTextFont();
    void resetCaptionColor();
    void resetTableWidth();
    void resetTableBorderWidth();
    void resetTableBorderStyle();
    void resetCellSpacing();
    void resetCellPadding();
    void resetTableBorderColor();
    void resetTableHeaderFont();
    void resetTableHeaderColor();
    void resetTableTextFont();
    void resetTableTextColor();
    void resetTableResultFont();
    void resetTableResultColor();
    void resetColumns();
};

#endif // PRINTSETTINGS_H
