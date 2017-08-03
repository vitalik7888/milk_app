#include "CalcFrame.h"
#include "ui_CalcFrame.h"

#include "MainWindow.h"
#include "base/Database.h"
#include "PrintTableWidget.h"
#include "Settings.h"
#include "DialogSettings.h"
#include "Constants.h"
#include "ViewUtils.h"
#include "src/core/Utils.h"
#include <dataworker.h>
// Qt
#include <QtMath>
#include <QMap>
#include <QMessageBox>
#include <QDir>
#include <QTextTable>
#include <QTextDocument>
#include <QDebug>
//--------------------------------------------------------------------------------------------------
TableWidgetItemBuilder::TableWidgetItemBuilder() {}

TableWidgetItemBuilder *TableWidgetItemBuilder::setNum(const double value, const char f, const int prec) {
    m_text = QString::number(value, f, prec);
    return this;
}

TableWidgetItemBuilder *TableWidgetItemBuilder::setFont(const QFont &font)
{
    m_font = font;
    return this;
}

TableWidgetItemBuilder *TableWidgetItemBuilder::setBackColor(const QColor &backColor)
{
    m_backColor = backColor;
    return this;
}

TableWidgetItemBuilder *TableWidgetItemBuilder::setText(const QString &text)
{
    m_text = text;
    return this;
}

TableWidgetItemBuilder *TableWidgetItemBuilder::reset() {
    m_text = QString();
    m_backColor = Qt::white;
    m_font = QFont();

    return this;
}

QTableWidgetItem *TableWidgetItemBuilder::get() {
    auto item = new QTableWidgetItem(m_text);
    item->setBackgroundColor(m_backColor);
    item->setFont(m_font);
    return item;
}

//--------------------------------------------------------------------------------------------------
CalcFrame::CalcFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CalcFrame),
    m_mainWindow(nullptr)
{
    ui->setupUi(this);

    ui->dateEditFilterStart->setDate(QDate::currentDate());;
    ui->dateEditFilterEnd->setDate(ui->dateEditFilterStart->date());

    connect(ui->pushButtonCalc, &QPushButton::clicked, this, &CalcFrame::calc);
    connect(ui->dateEditFilterStart, &QDateEdit::dateChanged, this, &CalcFrame::chooseDate);
    connect(ui->dateEditFilterEnd, &QDateEdit::dateChanged, this, &CalcFrame::chooseDate);
    connect(ui->pushButtonPrint, &QPushButton::clicked, this, &CalcFrame::printCalc);
    connect(ui->toolButtonPrintSetup, &QToolButton::clicked, this, [this]() {
        m_mainWindow->getDialogSettings()->setCurPagePrintPage();
        m_mainWindow->getDialogSettings()->exec();
    });
    connect(ui->toolButtonCalcSetup, &QToolButton::clicked, this, [this]() {
        m_mainWindow->getDialogSettings()->setCurPageCalcPage();
        m_mainWindow->getDialogSettings()->exec();
    });
}

CalcFrame::~CalcFrame()
{
    delete ui;
}

void CalcFrame::setup()
{
    const auto deliverers = m_mainWindow->database()->deliverers();
    const auto milkPoints = m_mainWindow->database()->milkPoints();

    ui->comboBoxFilterDeliverers->setModel(m_mainWindow->database()->deliverers());
    ui->comboBoxFilterDeliverers->setModelColumn(DT_NAME);
    ui->comboBoxFilterMilkPoints->setModel(m_mainWindow->database()->milkPoints());
    ui->comboBoxFilterMilkPoints->setModelColumn(MPT_NAME);

    if (deliverers->rowCount() > 0) {
        ui->comboBoxFilterDeliverers->setCurrentIndex(0);
    }
    if (milkPoints->rowCount() > 0) {
        ui->comboBoxFilterMilkPoints->setCurrentIndex(0);
    }

    refreshTableWidgetCalc();
}

void CalcFrame::calc()
{
    auto milkReception = m_mainWindow->database()->milkReception();
    if (!milkReception) {
        ViewUtils::showMsgIfDbNotChoosed(this);
        return;
    }

    refreshTableWidgetCalc();

    DataWorker dw(m_mainWindow->database());
    try {
        dw.loadMilkReceptions(getWhereQuery());
    } catch (const QString &err) {
        QMessageBox::critical(this, tr("Расчеты"), tr("Произошла ошибка во время подгрузки данных: ") + err);
    }
    if (dw.getMilkReceptions().empty()) {
            QMessageBox::information(this, tr("Расчеты"), tr("Отсутствуют данные для расчетов"));
            return;
    }
    const auto settings = m_mainWindow->settings();
    const auto deliverers = dw.getDeliverers().values();
    const auto itemsCount = dw.getMilkReceptions().size() + deliverers.size() + 1; // FIXME
    ui->tableWidgetCalc->setRowCount(itemsCount);
    int row = 0;

    TableWidgetItemBuilder itemBuilder;
    CalculatedItem::Data allResult;
    const Settings::Calc settingsCalc = settings->getCalc();
    const char f = 'f';
    const Settings::Column nameCol = settingsCalc.columns[toInt(Columns::Name)],
            mpNameCol = settingsCalc.columns[toInt(Columns::MilkPointName)],
            dateCol = settingsCalc.columns[toInt(Columns::Date)],
            priceCol = settingsCalc.columns[toInt(Columns::PriceLiter)],
            litersCol = settingsCalc.columns[toInt(Columns::Liters)],
            fatCol = settingsCalc.columns[toInt(Columns::Fat)],
            proteinCol = settingsCalc.columns[toInt(Columns::Protein)],
            fatUnitsCol = settingsCalc.columns[toInt(Columns::FatUnits)],
            rankWeightCol = settingsCalc.columns[toInt(Columns::RankWeight)],
            payCol = settingsCalc.columns[toInt(Columns::PayWithOutPrem)],
            premiumCol = settingsCalc.columns[toInt(Columns::Premium)],
            sumCol = settingsCalc.columns[toInt(Columns::Sum)];
    const auto dateFromat = settingsCalc.dateFormat;

    auto addCalcItems = [&](const QString &name, const QString &milkPoint,
            const QString &delivDate, const CalculatedItem::Data &calcItem)
    {
        int c = 0;
        if (nameCol.isShow)
            ui->tableWidgetCalc->setItem(row, c++, itemBuilder.setText(name)->get());
        if (mpNameCol.isShow)
            ui->tableWidgetCalc->setItem(row, c++, itemBuilder.setText(milkPoint)->get());
        if (dateCol.isShow)
            ui->tableWidgetCalc->setItem(row, c++, itemBuilder.setText(delivDate)->get());
        if (priceCol.isShow) {
            const QString priceValue = calcItem.priceForLiter <= .0 ? "-" : QString::number(calcItem.priceForLiter, f, priceCol.prec);
            ui->tableWidgetCalc->setItem(row, c++, itemBuilder.setText(priceValue)->get());
        }
        if (litersCol.isShow)
            ui->tableWidgetCalc->setItem(row, c++, itemBuilder.setNum(calcItem.liters, f, litersCol.prec)->get());
        if (fatCol.isShow)
            ui->tableWidgetCalc->setItem(row, c++, itemBuilder.setNum(calcItem.fat, f, fatCol.prec)->get());
        if (proteinCol.isShow)
            ui->tableWidgetCalc->setItem(row, c++, itemBuilder.setNum(calcItem.protein, f, proteinCol.prec)->get());
        if (fatUnitsCol.isShow)
            ui->tableWidgetCalc->setItem(row, c++, itemBuilder.setNum(calcItem.fatUnits, f, fatUnitsCol.prec)->get());
        if (rankWeightCol.isShow)
            ui->tableWidgetCalc->setItem(row, c++, itemBuilder.setNum(calcItem.rankWeight, f, rankWeightCol.prec)->get());
        if (payCol.isShow)
            ui->tableWidgetCalc->setItem(row, c++, itemBuilder.setNum(calcItem.paymentWithOutPremium, f, payCol.prec)->get());
        if (premiumCol.isShow)
            ui->tableWidgetCalc->setItem(row, c++, itemBuilder.setNum(calcItem.premiumForFat, f, premiumCol.prec)->get());
        if (sumCol.isShow) {
            ui->tableWidgetCalc->setItem(row, c++, itemBuilder.setNum(calcItem.sum, f, sumCol.prec)->get());
        }
    };

    for (const auto &deliverer: deliverers) {
        CalculatedItem::Data delivererResult;
        itemBuilder.setBackColor(settingsCalc.textBackColor);
        itemBuilder.setFont(settingsCalc.textFont);

        for (const auto &milkReception: deliverer->milkReceptions()) {
            const auto mr = milkReception.data();
            const CalculatedItem::Data calcItem = mr->getCalculations().data();

            addCalcItems(deliverer->name(), mr->milkPoint().data()->name(),
                         mr->deliveryDate().toString(dateFromat), calcItem);

            delivererResult += calcItem;
            ++row;
        }

        itemBuilder.setBackColor(settingsCalc.delivResultColor);
        itemBuilder.setFont(settingsCalc.delivResultFont);

        addCalcItems(deliverer->name(), "-", "-", delivererResult);

        allResult += delivererResult;
        ++row;
    }

    itemBuilder.setBackColor(settingsCalc.allResultColor);
    itemBuilder.setFont(settingsCalc.allResultFont);
    addCalcItems("Итого", "-", "-", allResult);
}

void CalcFrame::setMainWindow(MainWindow *mainWindow)
{
    m_mainWindow = mainWindow;
}

bool CalcFrame::isCalcByDeliverer() const
{
    return ui->groupBoxFilterDeliverers->isChecked();
}

bool CalcFrame::isCalcByDate() const
{
    return ui->groupBoxFilterDate->isChecked();
}

bool CalcFrame::isCalcByMilkPoint() const
{
    return ui->groupBoxFilterMilkPoints->isChecked();
}

void CalcFrame::chooseDate()
{
    if (ui->dateEditFilterEnd->date() <= ui->dateEditFilterStart->date())
        ui->dateEditFilterEnd->setDate(ui->dateEditFilterStart->date());
}

void CalcFrame::printCalc()
{
    const auto milkReception = m_mainWindow->database()->milkReception();

        if (!milkReception) {
            ViewUtils::showMsgIfDbNotChoosed(this);
            return;
        }
        DataWorker dw(m_mainWindow->database());
        try {
            dw.loadMilkReceptions(getWhereQuery());
        } catch (const QString &err) {
            QMessageBox::critical(this, tr("Расчеты"), tr("Произошла ошибка во время подгрузки данных: ") + err);
        }
        const auto deliverers = dw.getDeliverers().values();

        if (deliverers.isEmpty())
        {
            QMessageBox::information(this, tr("Печать"), tr("Отсутствуют данные для печати"));
            return;
        }

        const char f = 'f';
        int row = 0;
        const auto settings = m_mainWindow->settings();
        const auto printColumns = m_mainWindow->settings()->getPrint().columns;

        QStringList columns;
        for (int i = 0; i < printColumns.size(); ++i) {
            const auto &col = printColumns[i];
            if (col.isShow)
                columns.append(printColumns[i].display);
        }

        const int columnsCount = columns.size();
        if (columnsCount <= 0) {
            QMessageBox::information(this, tr("Печать сдачи молока"), tr("Не выбрана ни одна колонка для печати"));
            return;
        }

        const Settings::Column snCol = printColumns[Constants::PrintColumns::SerialNumber],
                delivNameCol = printColumns[Constants::PrintColumns::DeliverersName],
                litersCol = printColumns[Constants::PrintColumns::Liters],
                fatCol = printColumns[Constants::PrintColumns::Fat],
                proteinCol = printColumns[Constants::PrintColumns::Protein],
                fatUnitsCol = printColumns[Constants::PrintColumns::FatUnits],
                rankWeightCol = printColumns[Constants::PrintColumns::RankWeight],
                payCol = printColumns[Constants::PrintColumns::PayWithOutPrem],
                permiumCol = printColumns[Constants::PrintColumns::Premium],
                sumCol = printColumns[Constants::PrintColumns::Sum],
                signCol = printColumns[Constants::PrintColumns::Sign];

        auto itemToPrintRow = [&](const QString &delivName, const CalculatedItem::Data &item,
                const int rowPos = -1) -> QStringList
        {
            QStringList row;

            if (snCol.isShow)
                row.append(rowPos >= 0 ? QString::number(rowPos) : QString());
            if (delivNameCol.isShow)
                row.append(delivName);
            if (litersCol.isShow)
                row.append(QString::number(item.liters, f, litersCol.prec));
            if (fatCol.isShow)
                row.append(QString::number(item.fat, f, fatCol.prec));
            if (proteinCol.isShow)
                row.append(QString::number(item.protein, f, proteinCol.prec));
            if (fatUnitsCol.isShow)
                row.append(QString::number(item.fatUnits, f, fatCol.prec));
            if (rankWeightCol.isShow)
                row.append(QString::number(item.rankWeight, f, rankWeightCol.prec));
            if (payCol.isShow)
                row.append(QString::number(item.paymentWithOutPremium, f, payCol.prec));
            if (permiumCol.isShow)
                row.append(QString::number(item.premiumForFat, f, permiumCol.prec));
            if (sumCol.isShow)
                row.append(QString::number(floor(item.sum), f, sumCol.prec));
            if (signCol.isShow)
                row.append(QString());

            return row;
        };

        const auto &printSettings = settings->getPrint();

        QTextTableFormat tableFormat;
        tableFormat.setBorder(printSettings.tableBorderWidth);
        tableFormat.setBorderStyle(static_cast<QTextFrameFormat::BorderStyle>(printSettings.tableBorderStyle));
        tableFormat.setColumns(columnsCount);
        tableFormat.setAlignment(Qt::AlignHCenter);
        tableFormat.setWidth(QTextLength(QTextLength::VariableLength, 100));
        tableFormat.setBorderBrush(QBrush(printSettings.tableBorderColor));
        tableFormat.setCellSpacing(printSettings.cellSpacing);
        tableFormat.setCellPadding(printSettings.cellPadding);

        PrintTable print(columnsCount, tableFormat);
        {
            auto &textFormat = print.getTableBodyTextFormat();
            textFormat.setFont(printSettings.tableTextFont);
            textFormat.setForeground(QBrush(printSettings.tableTextColor));
        }
        {
            auto &textFormat = print.getTableHeadersFormat();
            textFormat.setFont(printSettings.tableHeaderFont);
            textFormat.setForeground(QBrush(printSettings.tableHeaderColor));
        }
        print.setHeaders(columns);

        CalculatedItem::Data allResult;
        for (const auto &deliverer: deliverers)
        {
            row++;

            const CalculatedItem::Data calcItem = deliverer->getCalculations();
            print.addRow(itemToPrintRow(deliverer->name(), calcItem, row));

            allResult += calcItem;
        }

        int mergeCount = 0;
        auto itemRow = itemToPrintRow("Итого", allResult, row);
        for (int i = 0; i < Constants::PrintColumns::Liters; i++) {
            const auto &col = printColumns[i];
            if (col.isShow)
                mergeCount++;
        }
        QTextCharFormat resultFormat;
        resultFormat.setFont(printSettings.tableResultFont);
        resultFormat.setForeground(QBrush(printSettings.tableResultColor));

        print.addRow(itemRow, resultFormat, mergeCount);

        auto &cursor = print.cursor();

        cursor.setPosition(0);

        QTextFrameFormat topFrameFormat;
        topFrameFormat.setPadding(4);
        cursor.insertFrame(topFrameFormat);

        QTextBlockFormat textBlockFormat;
        textBlockFormat.setBottomMargin(4);
        textBlockFormat.setAlignment(Qt::AlignLeft);

        QTextBlockFormat captionBlockFormat;
        captionBlockFormat.setAlignment(Qt::AlignCenter);
        cursor.setBlockFormat(textBlockFormat);

        QTextCharFormat textCharFormat;
        textCharFormat.setFont(printSettings.textFont);
        QTextCharFormat captionCharFormat;
        captionCharFormat.setFont(printSettings.captionTextFont);
        captionCharFormat.setForeground(QBrush(printSettings.captionColor));

        cursor.insertText(settings->getMain().firmName, textCharFormat);
        cursor.insertBlock();

        cursor.setBlockFormat(captionBlockFormat);

        auto dateMin = QDate(), dateMax = QDate();

        if (isCalcByDate()) {
            dateMin = ui->dateEditFilterStart->date();
            dateMax = ui->dateEditFilterEnd->date();
        } else {
            dateMin = milkReception->getMinDeliveryDate();
            dateMax = milkReception->getMaxDeliveryDate();
        }

        const auto s = dateMax == dateMin ? tr("%1 число").arg(dateMin.toString(Constants::defaultDateFormat())) :
                                            tr("период с %1 по %2")
                                            .arg(dateMin.toString(Constants::defaultDateFormat()))
                                            .arg(dateMax.toString(Constants::defaultDateFormat()));

        cursor.insertText(QString(tr("Платежная ведомость №\n"
                                     "за сданное молоко\n"
                                     "за ") + s), captionCharFormat);
        cursor.insertBlock();
        cursor.setBlockFormat(textBlockFormat);

        cursor.insertText(tr("Населенный пункт: ") + m_mainWindow->getCurrentLocalityName(), textCharFormat);
        cursor.insertBlock();
        cursor.insertText(tr("Приемщик молока: ") + settings->getMain().milkInspector, textCharFormat);
        cursor.insertBlock();

        cursor.movePosition(QTextCursor::End);

        QTextFrameFormat bottomFrameFormat;
        bottomFrameFormat.setPadding(4);
        cursor.insertFrame(bottomFrameFormat);

        cursor.setBlockFormat(textBlockFormat);

        const auto minMaxPrice = milkReception->getMinMaxPriceLiter(dateMin, dateMax);
        if (minMaxPrice.first > .0 && minMaxPrice.second > .0) {
            const QString minPrice = QString::number(minMaxPrice.first, f, 2),
                maxPrice = QString::number(minMaxPrice.second, f, 2);

            cursor.insertText(tr("Цена: %1").arg(minPrice == maxPrice ? minPrice : QString("%1 - %2")
                                                                        .arg(minPrice).arg(maxPrice)));
            cursor.insertBlock();
        }
        cursor.insertText(tr("Деньги в сумме: "), textCharFormat);
        cursor.insertBlock();
        cursor.insertText(tr("Получил и выдал согласно ведомости приемщик молока______") + settings->getMain().milkInspector_2,
                          textCharFormat);
        cursor.insertBlock();
        cursor.insertText(tr("Директор ") + settings->getMain().firmName, textCharFormat);

    print.showDialog();
}

QString CalcFrame::getWhereQuery()
{
    auto milkReception = m_mainWindow->database()->milkReception();
    const auto localityId = m_mainWindow->getCurrentLocalityId();

    QStringList whereList;
    if (Utils::Main::isAutoIncrIdIsValid(localityId)) {
        whereList.append(QString("milk_point_id IN(SELECT id FROM milk_points WHERE locality_id = %1)").
                         arg(localityId));
    }
    if (isCalcByDeliverer() || isCalcByDate() || isCalcByMilkPoint()) {
        if (isCalcByDeliverer()) {
            const auto id = ViewUtils::getCurValueFromComboBoxModel(ui->comboBoxFilterDeliverers, DT_ID).toLongLong();
            if (Utils::Main::isAutoIncrIdIsValid(id)) {
                whereList.append(QString("%1 = %2")
                                 .arg(milkReception->getColName(RMT_ID_DELIVERER, true))
                                 .arg(id));
            } else {
                const auto err = tr("id сдатчика не валиден");
                qDebug() << err;
                throw err;
            }
        }

        if (isCalcByDate()) {
            const auto dateMin = ui->dateEditFilterStart->date(),
                    dateMax = ui->dateEditFilterEnd->date();

            if (dateMin.isValid() && dateMax.isValid()) {
                whereList.append(QString("%1 BETWEEN %2 and %3")
                                 .arg(milkReception->getColName(RMT_DELIVERY_DATE, true))
                                 .arg(dateMin.toString(Constants::defaultDateFormat()))
                                 .arg(dateMax.toString(Constants::defaultDateFormat())));
            } else {
                const auto err = tr("Даты не валидны");
                qDebug() << err;
                throw err;
            }
        }

        if (isCalcByMilkPoint()) {
            const auto id = ViewUtils::getCurValueFromComboBoxModel(ui->comboBoxFilterMilkPoints, MPT_ID).toLongLong();
            if (Utils::Main::isAutoIncrIdIsValid(id)) {
                whereList.append(QString("%1 = %2")
                                 .arg(milkReception->getColName(RMT_MILK_POINT_ID, true))
                                 .arg(id));
            } else {
                const auto err =  tr("id молокопункта не валиден");
                qDebug() << err;
                throw err;
            }
        }
    }

    QString where;
    const auto itEnd = whereList.constEnd();
    for (auto it = whereList.constBegin(); it != itEnd;) {
        where.append(*it);
        ++it;
        if (it != itEnd) {
            where.append(" AND ");
        }
    }

    return where;
}

void CalcFrame::refreshTableWidgetCalc()
{
    ui->tableWidgetCalc->setColumnCount(0);
    ui->tableWidgetCalc->setRowCount(0);
    ui->tableWidgetCalc->clear();

    const auto calcColumns = m_mainWindow->settings()->getCalc().columns;

    int colCountToShow = 0;
    for (int i = 0; i < calcColumns.size(); ++i) {
        const auto &calcColumn = calcColumns[i];

        if (calcColumn.isShow) {
            ui->tableWidgetCalc->insertColumn(colCountToShow);
            QTableWidgetItem *headerItem = new QTableWidgetItem(calcColumn.display);
            headerItem->setTextAlignment(Qt::AlignVCenter);

            ui->tableWidgetCalc->setHorizontalHeaderItem(colCountToShow, headerItem);
            colCountToShow++;
        }
    }
}

int CalcFrame::toInt(const CalcFrame::Columns column)
{
    return static_cast<int>(column);
}
