#ifndef DIALOGPRINTSETTINGS_H
#define DIALOGPRINTSETTINGS_H

#include <QDialog>
#include "Settings.h"

namespace Ui {
class DialogSettings;
}
class QGridLayout;
class MainWindow;
class QCheckBox;
class QLabel;
class QLineEdit;
class QSpinBox;


class DialogSettings : public QDialog
{
    Q_OBJECT

    struct Column {
        Column(): lineEditDisplay(nullptr), checkBoxIsShow(nullptr), spinBoxPrec(nullptr) {}

        Column(QLineEdit *_lineEditDisplay, QCheckBox *_checkBoxIsShow, QSpinBox *_spinBoxPrec):
            lineEditDisplay(_lineEditDisplay), checkBoxIsShow(_checkBoxIsShow), spinBoxPrec(_spinBoxPrec)
        {}

        QLineEdit *lineEditDisplay;
        QCheckBox *checkBoxIsShow;
        QSpinBox *spinBoxPrec;
    };

    enum class Pages: int {
        Main = 0,
        Calc,
        Print
    };

public:
    explicit DialogSettings(MainWindow *parent = nullptr);
    ~DialogSettings();

    void setCurPagePrintPage();
    void setCurPageCalcPage();

public slots:
    void accept() Q_DECL_OVERRIDE;
    int exec() Q_DECL_OVERRIDE;

private slots:
    void setDefaultMain();
    void setDefaultCalc();
    void setDefaultPrint();

    void setTableBorderColor();
    void setTableHeaderTextColor();
    void setTableTextColor();
    void setCaptionColor();
    void setTableResultColor();
    void setCalcTextColor();
    void setCalcDelivResColor();
    void setCalcAllResultColor();

    void setTableHeaderFont();
    void setTableTextFont();
    void setTextFont();
    void setCaptionFont();
    void setTableResultFont();
    void setCalcTextFont();
    void setCalcDelivResultFont();
    void setCalcAllResultsFont();

private:
    Ui::DialogSettings *ui;
    QGridLayout *m_gridLayoutCalc;
    QGridLayout *m_gridLayoutPrint;
    MainWindow *m_mainWindow;

    Settings *m_settings;

    QVector<DialogSettings::Column> m_columnCalc;
    QVector<DialogSettings::Column> m_columnPrint;

    void addWidgetsColumns(QGridLayout *gl, QVector<DialogSettings::Column> &columns,
                           const QVector<Settings::Column> &setColumns);
    void writeWidgetColumn(DialogSettings::Column &widgCol, const Settings::Column &setCol);
    void writeSettingsColumn(const DialogSettings::Column &widgCol, Settings::Column &setCol);

    void addCalcColumns();
    void setLabelColor(QLabel *label, const QColor &color);

    void addPrintColumns();

    void readSettings();
    void readMainSettingsToUi();
    void readCalcSettingsToUi();
    void readPrintSettingsToUi();

    void readMainSettingsFromUi();
    void readCalcSettingsFromUi();
    void readPrintSettingsFromUi();

    void getFontFromDialog(const QFont &fontStart, QLineEdit *le, QFont &fontToChange);
    void getColorFromDialog(const QColor &colorStart, QLabel *label, QColor &colorToChange);
};

#endif // DIALOGPRINTSETTINGS_H
