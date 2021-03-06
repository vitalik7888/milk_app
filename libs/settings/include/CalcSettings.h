#ifndef CALCSETTINGS_H
#define CALCSETTINGS_H

#include "SettingsConstants.h"
// Qt
#include <QVector>
#include <QQmlListProperty>
#include <QColor>
#include <QFont>

class SettingsColumn;


class SETTINGSLIBRARYSHARED_EXPORT CalcSettings : public QObject {
    Q_OBJECT
    Q_PROPERTY(QFont textFont READ textFont WRITE setTextFont NOTIFY textFontChanged RESET resetTextFont)
    Q_PROPERTY(QColor textBackColor READ textBackColor WRITE setTextBackColor NOTIFY textBackColorChanged RESET resetTextBackColor)
    Q_PROPERTY(QFont delivResultFont READ delivResultFont WRITE setDelivResultFont NOTIFY delivResultFontChanged RESET resetDelivResultFont)
    Q_PROPERTY(QColor delivResultColor READ delivResultColor WRITE setDelivResultColor NOTIFY delivResultColorChanged RESET resetDelivResultColor)
    Q_PROPERTY(QFont allResultFont READ allResultFont WRITE setAllResultFont NOTIFY allResultFontChanged RESET resetAllResultFont)
    Q_PROPERTY(QColor allResultColor READ allResultColor WRITE setAllResultColor NOTIFY allResultColorChanged RESET resetAllResultColor)
    Q_PROPERTY(QString dateFormat READ dateFormat WRITE setDateFormat NOTIFY dateFormatChanged RESET resetDateFormat)
    Q_PROPERTY(QQmlListProperty<SettingsColumn> columns READ columns RESET resetColumns)

public:
    explicit CalcSettings(QObject *parent = Q_NULLPTR);

    QFont textFont() const { return m_textFont; }
    QColor textBackColor() const { return m_textBackColor; }
    QFont delivResultFont() const { return m_delivResultFont; }
    QColor delivResultColor() const { return m_delivResultColor; }
    QFont allResultFont() const { return m_allResultFont; }
    QColor allResultColor() const { return m_allResultColor; }
    QString dateFormat() const { return m_dateFormat; }
    QQmlListProperty<SettingsColumn> columns();

    SettingsConstants::SettingsColumns getColumns() const;
    void appendSettingsColumn(SettingsColumn *column);
    void appendSettingsColumns(const SettingsConstants::SettingsColumns &columns);
    void setSettingsColumns(const SettingsConstants::SettingsColumns &columns);
    int settingsColumnsCount() const;
    SettingsColumn *settingColumn(int position) const;
    void clearSettingsColumns();

public slots:
    void setTextFont(const QFont &textFont);
    void setTextBackColor(const QColor &textBackColor);
    void setDelivResultFont(const QFont &delivResultFont);
    void setDelivResultColor(const QColor &delivResultColor);
    void setAllResultFont(const QFont &allResultFont);
    void setAllResultColor(const QColor &allResultColor);
    void setDateFormat(const QString &dateFormat);
    void reset();

signals:
    void textFontChanged(QFont textFont);
    void textBackColorChanged(QColor textBackColor);
    void delivResultFontChanged(QFont delivResultFont);
    void delivResultColorChanged(QColor delivResultColor);
    void allResultFontChanged(QFont allResultFont);
    void allResultColorChanged(QColor allResultColor);
    void dateFormatChanged(QString dateFormat);

private:
    QFont m_textFont;
    QColor m_textBackColor;
    QFont m_delivResultFont;
    QColor m_delivResultColor;
    QFont m_allResultFont;
    QColor m_allResultColor;
    QString m_dateFormat;
    SettingsConstants::SettingsColumns m_columns;

    static void appendSettingsColumn(QQmlListProperty<SettingsColumn> *list, SettingsColumn *column);
    static int settingsColumnsCount(QQmlListProperty<SettingsColumn> *list);
    static SettingsColumn* settingColumn(QQmlListProperty<SettingsColumn> *list, int position);
    static void clearSettingsColumns(QQmlListProperty<SettingsColumn> *list);

    void resetTextFont();
    void resetTextBackColor();
    void resetDelivResultFont();
    void resetDelivResultColor();
    void resetAllResultFont();
    void resetAllResultColor();
    void resetDateFormat();
    void resetColumns();
};

#endif // CALCSETTINGS_H
