#include "DialogSettings.h"
#include "ui_DialogSettings.h"

#include "MainWindow.h"
#include "Constants.h"
// qt
#include <QCheckBox>
#include <QGridLayout>
#include <QColorDialog>
#include <QFontDialog>
#include <QDebug>

#define COL_NAME_POS 0
#define COL_PREC_POS 1
#define COL_SHOW_POS 2


DialogSettings::DialogSettings(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::DialogSettings),
    m_gridLayoutCalc(nullptr),
    m_gridLayoutPrint(nullptr),
    m_mainWindow(parent),
    m_settings(m_mainWindow->getSettings())
{
    ui->setupUi(this);

    m_gridLayoutCalc = new QGridLayout(ui->groupBoxCalcColumns);
    m_gridLayoutPrint = new QGridLayout(ui->groupBoxTableColumns);

    addCalcColumns();
    addPrintColumns();

    connect(ui->toolButtonChooseColorTableBorder, SIGNAL(clicked(bool)), SLOT(setTableBorderColor()));
    connect(ui->toolButtonChooseColorTableHeader, SIGNAL(clicked(bool)), SLOT(setTableHeaderTextColor()));
    connect(ui->toolButtonChooseColorTableText, SIGNAL(clicked(bool)), SLOT(setTableTextColor()));
    connect(ui->toolButtonChooseCaptionColor, SIGNAL(clicked(bool)), SLOT(setCaptionColor()));
    connect(ui->toolButtonChooseTabResColor, SIGNAL(clicked(bool)), SLOT(setTableResultColor()));
    connect(ui->toolButtonCalcChooseTextColor, SIGNAL(clicked(bool)), SLOT(setCalcTextColor()));
    connect(ui->toolButtonCalcChooseDelResColor, SIGNAL(clicked(bool)), SLOT(setCalcDelivResColor()));
    connect(ui->toolButtonCalcChooseAllResColor, SIGNAL(clicked(bool)), SLOT(setCalcAllResultColor()));

    connect(ui->toolButtonChooseFontTableHeaders, SIGNAL(clicked(bool)), SLOT(setTableHeaderFont()));
    connect(ui->toolButtonTableTextFont, SIGNAL(clicked(bool)), SLOT(setTableTextFont()));
    connect(ui->toolButtonChooseTextFont, SIGNAL(clicked(bool)), SLOT(setTextFont()));
    connect(ui->toolButtonChooseCaptionFont, SIGNAL(clicked(bool)), SLOT(setCaptionFont()));
    connect(ui->toolButtonChooseTabResFont, SIGNAL(clicked(bool)), SLOT(setTableResultFont()));
    connect(ui->toolButtonCalcChooseTextFont, SIGNAL(clicked(bool)), SLOT(setCalcTextFont()));
    connect(ui->toolButtonCalcChooseDelResFont, SIGNAL(clicked(bool)), SLOT(setCalcDelivResultFont()));
    connect(ui->toolButtonCalcChooseAllResFont, SIGNAL(clicked(bool)), SLOT(setCalcAllResultsFont()));

    connect(ui->pushButtonDefaultCalc, &QPushButton::clicked, this, &DialogSettings::setDefaultCalc);
    connect(ui->pushButtonDefaultPrint, &QPushButton::clicked, this, &DialogSettings::setDefaultPrint);
    connect(ui->pushButtonMainDefaults, &QPushButton::clicked, this, &DialogSettings::setDefaultMain);
}

DialogSettings::~DialogSettings()
{
    delete ui;
}

void DialogSettings::setCurPagePrintPage()
{
    ui->stackedWidget->setCurrentIndex((int)Pages::Print);
}

void DialogSettings::setCurPageCalcPage()
{
    ui->stackedWidget->setCurrentIndex((int)Pages::Calc);
}

void DialogSettings::addCalcColumns()
{
    m_gridLayoutCalc->addWidget(new QLabel(tr("Название")), 0, COL_NAME_POS);
    m_gridLayoutCalc->addWidget(new QLabel(tr("")), 0, COL_PREC_POS);
    m_gridLayoutCalc->addWidget(new QLabel(tr("Отображать")), 0, COL_SHOW_POS);

    addWidgetsColumns(m_gridLayoutCalc, m_columnCalc, m_mainWindow->getSettings()->getCalc().columns);
}

void DialogSettings::setLabelColor(QLabel *label, const QColor &color)
{
    QPixmap pm(36, 36);
    pm.fill(color);
    label->setPixmap(pm);
}

void DialogSettings::addPrintColumns()
{
    m_gridLayoutPrint->addWidget(new QLabel(tr("Название")), 0, COL_NAME_POS);
    m_gridLayoutPrint->addWidget(new QLabel(tr("")), 0, COL_PREC_POS);
    m_gridLayoutPrint->addWidget(new QLabel(tr("Отображать")), 0, COL_SHOW_POS);

    addWidgetsColumns(m_gridLayoutPrint, m_columnPrint, m_mainWindow->getSettings()->getPrint().columns);
}

void DialogSettings::addWidgetsColumns(QGridLayout *gl, QVector<DialogSettings::Column> &columns,
                                       const QVector<Settings::Column> &setColumns)
{
    for (int i = 0; i < setColumns.size(); i++) {
        const auto &col = setColumns[i];
        const auto row = i + 1;

        QSpinBox *sb = nullptr;

        auto le = new QLineEdit();
        auto chb = new QCheckBox;

        if (col.type == (int)Constants::ColumnType::Double) {
            sb = new QSpinBox;
            sb->setMinimum(0);
            sb->setMaximum(4);
            gl->addWidget(sb, row, COL_PREC_POS);
        }

        gl->addWidget(le, row, COL_NAME_POS);
        gl->addWidget(chb, row, COL_SHOW_POS);

        columns.append(DialogSettings::Column(le, chb, sb));
    }
}

void DialogSettings::writeWidgetColumn(DialogSettings::Column &widgCol, const Settings::Column &setCol)
{
    widgCol.lineEditDisplay->setText(setCol.display);
    widgCol.checkBoxIsShow->setChecked(setCol.isShow);
    if (widgCol.spinBoxPrec)
        widgCol.spinBoxPrec->setValue(setCol.prec);
}

void DialogSettings::writeSettingsColumn(const DialogSettings::Column &widgCol, Settings::Column &setCol)
{
    setCol.display = widgCol.lineEditDisplay->text();
    setCol.isShow = widgCol.checkBoxIsShow->isChecked();
    if (widgCol.spinBoxPrec)
        setCol.prec = widgCol.spinBoxPrec->value();
}

void DialogSettings::readSettings()
{
    m_settings->readMainSettings();
    readMainSettingsToUi();

    m_settings->readCalcSettings();
    readCalcSettingsToUi();

    m_settings->readPrintSettings();
    readPrintSettingsToUi();
}

void DialogSettings::readMainSettingsToUi()
{
    ui->lineEditFirmName->setText(m_settings->getMain().firmName);
    ui->lineEditMilkInspector->setText(m_settings->getMain().milkInspector);
    ui->lineEditMilkInspector_2->setText(m_settings->getMain().milkInspector_2);
    ui->checkBoxTablesFetchOnRefresh->setChecked(m_settings->getMain().isFetchTablesOnRefresh);
}

void DialogSettings::readCalcSettingsToUi()
{
    const auto &calc = m_settings->getCalc();

    // color
    setLabelColor(ui->labelCalcTextColor, calc.textBackColor);
    setLabelColor(ui->labelCalcDelivResColor, calc.delivResultColor);
    setLabelColor(ui->labelCalcAllResColor, calc.allResultColor);
    // font
    ui->lineEditCalcTextFont->setText(calc.textFont.toString());
    ui->lineEditCalcDelivResFont->setText(calc.delivResultFont.toString());
    ui->lineEditCalcAllResFont->setText(calc.allResultFont.toString());
    // other
    ui->lineEditDateFormat->setText(calc.dateFormat);

    const auto &columns = calc.columns;
    for (int i = 0; i < columns.size(); i++)
        writeWidgetColumn(m_columnCalc[i], columns[i]);
}

void DialogSettings::readPrintSettingsToUi()
{
    const auto &print = m_settings->getPrint();
    // color
    setLabelColor(ui->labelColorTableBorder, print.tableBorderColor);
    setLabelColor(ui->labelColorTableHeader, print.tableHeaderColor);
    setLabelColor(ui->labelColorTableText, print.tableTextColor);
    setLabelColor(ui->labelCaptionColor, print.captionColor);
    setLabelColor(ui->labelTabelResultColor, print.tableResultColor);
    // font
    ui->lineEditTableHeadersFont->setText(print.tableHeaderFont.toString());
    ui->lineEditTableTextFont->setText(print.tableTextFont.toString());
    ui->lineEditCaptionFont->setText(print.captionTextFont.toString());
    ui->lineEditTextFont->setText(print.textFont.toString());
    ui->lineEditTabResFont->setText(print.tableResultFont.toString());
    // other
    ui->spinBoxTableWidth->setValue(print.tableWidth);
    ui->spinBoxTableBorderWidth->setValue(print.tableBorderWidth);
    ui->comboBoxTableBorderStyle->setCurrentIndex(print.tableBorderStyle);

    ui->spinBoxCellSpacing->setValue(print.cellSpacing);
    ui->spinBoxCellPadding->setValue(print.cellPadding);

    const auto &columns = print.columns;
    for (int i = 0; i < columns.size(); i++)
        writeWidgetColumn(m_columnPrint[i], columns[i]);
}

void DialogSettings::readMainSettingsFromUi()
{
    m_settings->setMain().firmName = ui->lineEditFirmName->text();
    m_settings->setMain().milkInspector = ui->lineEditMilkInspector->text();
    m_settings->setMain().milkInspector_2 = ui->lineEditMilkInspector_2->text();
    m_settings->setMain().isFetchTablesOnRefresh = ui->checkBoxTablesFetchOnRefresh->isChecked();
}

void DialogSettings::readCalcSettingsFromUi()
{
    auto &calc = m_settings->setCalc();

    calc.dateFormat = ui->lineEditDateFormat->text();

    auto &calcColumns = calc.columns;
    for (int i = 0; i < calcColumns.size(); i++)
        writeSettingsColumn(m_columnCalc[i], calcColumns[i]);
}

void DialogSettings::readPrintSettingsFromUi()
{
    auto &print = m_settings->setPrint();

    print.tableWidth = ui->spinBoxTableWidth->value();
    print.tableBorderWidth = ui->spinBoxTableBorderWidth->value();
    print.tableBorderStyle = ui->comboBoxTableBorderStyle->currentIndex();
    print.cellSpacing = ui->spinBoxCellSpacing->value();
    print.cellPadding = ui->spinBoxCellPadding->value();

    auto &calcColumns = print.columns;
    for (int i = 0; i < calcColumns.size(); i++)
        writeSettingsColumn(m_columnPrint[i], calcColumns[i]);
}

void DialogSettings::getFontFromDialog(const QFont &fontStart, QLineEdit *le, QFont &fontToChange)
{
    QFontDialog dialog(fontStart, this);
    if (dialog.exec() == QDialog::Accepted) {
        const auto choosenFont = dialog.currentFont();
        le->setText(choosenFont.toString());
        fontToChange = choosenFont;
    }
}

void DialogSettings::getColorFromDialog(const QColor &colorStart, QLabel *label, QColor &colorToChange)
{
    QColorDialog dialog(colorStart, this);
    if (dialog.exec() == QDialog::Accepted) {
        const auto choosenColor = dialog.currentColor();
        setLabelColor(label, choosenColor);
        colorToChange = choosenColor;
    }
}

void DialogSettings::accept()
{
    readMainSettingsFromUi();
    readCalcSettingsFromUi();
    readPrintSettingsFromUi();

    m_settings->writeMainSettings();
    m_settings->writeCalcSettings();
    m_settings->writePrintSettings();

    QDialog::accept();
}

void DialogSettings::setDefaultCalc()
{
    m_settings->setDefaultCalcSettings();
    readCalcSettingsToUi();
}

void DialogSettings::setDefaultPrint()
{
    m_settings->setDefaultPrintSettings();
    readPrintSettingsToUi();
}

void DialogSettings::setTableBorderColor()
{
    getColorFromDialog(m_settings->getPrint().tableBorderColor,
                       ui->labelColorTableBorder,
                       m_settings->setPrint().tableBorderColor);
}

void DialogSettings::setTableHeaderTextColor()
{
    getColorFromDialog(m_settings->getPrint().tableHeaderColor,
                        ui->labelColorTableHeader,
                        m_settings->setPrint().tableHeaderColor);
}

void DialogSettings::setTableTextColor()
{
    getColorFromDialog(m_settings->getPrint().tableTextColor,
                       ui->labelColorTableText,
                       m_settings->setPrint().tableTextColor);
}

void DialogSettings::setCaptionColor()
{
    getColorFromDialog(m_settings->getPrint().captionColor,
                        ui->labelCaptionColor,
                        m_settings->setPrint().captionColor);
}

void DialogSettings::setTableResultColor()
{
    getColorFromDialog(m_settings->getPrint().tableResultColor,
                       ui->labelTabelResultColor,
                       m_settings->setPrint().tableResultColor);
}

void DialogSettings::setCalcTextColor()
{
    getColorFromDialog(m_settings->getCalc().textBackColor,
                        ui->labelCalcTextColor,
                        m_settings->setCalc().textBackColor);
}

void DialogSettings::setCalcDelivResColor()
{
    getColorFromDialog(m_settings->getCalc().delivResultColor,
                       ui->labelCalcDelivResColor,
                       m_settings->setCalc().delivResultColor);
}

void DialogSettings::setCalcAllResultColor()
{
    getColorFromDialog(m_settings->getCalc().allResultColor,
                       ui->labelCalcAllResColor,
                       m_settings->setCalc().allResultColor);
}

void DialogSettings::setTableHeaderFont()
{
    getFontFromDialog(m_settings->getPrint().tableHeaderFont,
                      ui->lineEditTableHeadersFont,
        m_settings->setPrint().tableHeaderFont);
}

void DialogSettings::setTableTextFont()
{
    getFontFromDialog(m_settings->getPrint().tableTextFont,
                      ui->lineEditTableTextFont,
        m_settings->setPrint().tableTextFont);
}

void DialogSettings::setTextFont()
{
    getFontFromDialog(m_settings->getPrint().textFont,
                      ui->lineEditTextFont,
        m_settings->setPrint().textFont);
}

void DialogSettings::setCaptionFont()
{
    getFontFromDialog(m_settings->getPrint().captionTextFont,
                      ui->lineEditCaptionFont,
                      m_settings->setPrint().captionTextFont);
}

void DialogSettings::setTableResultFont()
{
    getFontFromDialog(m_settings->getPrint().tableResultFont,
                      ui->lineEditTabResFont,
                      m_settings->setPrint().tableResultFont);
}

void DialogSettings::setCalcTextFont()
{
    getFontFromDialog(m_settings->getCalc().textFont,
                      ui->lineEditCalcTextFont,
                      m_settings->setCalc().textFont);
}

void DialogSettings::setCalcDelivResultFont()
{
    getFontFromDialog(m_settings->getCalc().delivResultFont,
                      ui->lineEditCalcDelivResFont,
                      m_settings->setCalc().delivResultFont);
}

void DialogSettings::setCalcAllResultsFont()
{
    getFontFromDialog(m_settings->getCalc().allResultFont,
                      ui->lineEditCalcAllResFont,
                      m_settings->setCalc().allResultFont);
}

int DialogSettings::exec()
{
    readSettings();

    return QDialog::exec();
}

void DialogSettings::setDefaultMain()
{
    m_settings->setDefaultMainSettings();
    readMainSettingsToUi();
}
