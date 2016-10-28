#include "CalcFrame.h"
#include "ui_CalcFrame.h"

#include "MainWindow.h"
#include "base/Database.h"
#include "PrintTable.h"
#include "Settings.h"
#include "DialogSettings.h"
#include "Constants.h"
#include "Utils.h"
// qt
#include <QMap>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDir>
#include <QTextTable>
#include <QTextDocument>
#include <QDebug>


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

void CalcFrame::calc()
{
    auto milkReception = m_mainWindow->getDatabase()->milkReception();
    if (!milkReception) {
        Utils::Main::showMsgIfDbNotChoosed(this);
        return;
    }

    fillTableWidget(getItemsData());
}

void CalcFrame::setup()
{
    const auto deliverers = m_mainWindow->getDatabase()->deliverers();
    const auto milkPoints = m_mainWindow->getDatabase()->milkPoints();
    const auto delivNameCol = deliverers->getColumnPosition(deliverers->getNameColumnName()),
            milkPointNameCol = milkPoints->getColumnPosition(milkPoints->getNameColumnName());

    ui->comboBoxFilterDeliverers->setModel(m_mainWindow->getDatabase()->deliverers());
    ui->comboBoxFilterDeliverers->setModelColumn(delivNameCol);
    ui->comboBoxFilterMilkPoints->setModel(m_mainWindow->getDatabase()->milkPoints());
    ui->comboBoxFilterMilkPoints->setModelColumn(milkPointNameCol);

    if (deliverers->rowCount() > 0) {
        ui->comboBoxFilterDeliverers->setCurrentIndex(0);
    }
    if (milkPoints->rowCount() > 0) {
        ui->comboBoxFilterMilkPoints->setCurrentIndex(0);
    }
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
    const auto milkReception = m_mainWindow->getDatabase()->milkReception();

    if (!milkReception) {
        Utils::Main::showMsgIfDbNotChoosed(this);
        return;
    }
    const auto items = getItemsData();
    if (items.isEmpty())
    {
        QMessageBox::information(this, tr("Печать"), tr("Отсутствуют данные для печати"));
        return;
    }

    const auto &printColumns = m_mainWindow->getSettings()->getPrint().columns;

    auto itemToPrintRow = [=](const Item &item, const int rowPos = -1)->QStringList
    {
        QStringList row;
        const auto &snCol = printColumns[Constants::PrintColumns::SerialNumber],
                &delivNameCol = printColumns[Constants::PrintColumns::DeliverersName],
                &litersCol = printColumns[Constants::PrintColumns::Liters],
                &fatCol = printColumns[Constants::PrintColumns::Fat],
                &proteinCol = printColumns[Constants::PrintColumns::Protein],
                &fatUnitsCol = printColumns[Constants::PrintColumns::FatUnits],
                &rankWeightCol = printColumns[Constants::PrintColumns::RankWeight],
                &payCol = printColumns[Constants::PrintColumns::PayWithOutPrem],
                &permiumCol = printColumns[Constants::PrintColumns::Premium],
                &sumCol = printColumns[Constants::PrintColumns::Sum];

        if (snCol.isShow)
            row.append(rowPos >= 0 ? QString::number(rowPos) : QString());
        if (delivNameCol.isShow)
            row.append(item.delivererName);
        if (litersCol.isShow)
            row.append(QString::number(item.liters, 'f', litersCol.prec));
        if (fatCol.isShow)
            row.append(QString::number(item.fat, 'f', fatCol.prec));
        if (proteinCol.isShow)
            row.append(QString::number(item.protein, 'f', proteinCol.prec));
        if (fatUnitsCol.isShow)
            row.append(QString::number(item.fatUnits, 'f', fatCol.prec));
        if (rankWeightCol.isShow)
            row.append(QString::number(item.rankWeight, 'f', rankWeightCol.prec));
        if (payCol.isShow)
            row.append(QString::number(item.paymentWithOutPremium, 'f', payCol.prec));
        if (permiumCol.isShow)
            row.append(QString::number(item.premiumForFat, 'f', permiumCol.prec));
        if (sumCol.isShow)
            row.append(QString::number(floor(item.sum), 'f', sumCol.prec));
        if (printColumns[Constants::PrintColumns::Sign].isShow)
            row.append(QString());

        return row;
    };

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

    const auto settings = m_mainWindow->getSettings();
    const auto &printSettings = settings->getPrint();

    QTextTableFormat tableFormat;
    tableFormat.setBorder(printSettings.tableBorderWidth);
    tableFormat.setBorderStyle((QTextFrameFormat::BorderStyle)printSettings.tableBorderStyle);
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

    const auto uniqueKeys = items.uniqueKeys();

    Item itemResults(tr("Итого"), QString());

    int row = 0;

    for (const auto delivererId: uniqueKeys)
    {
        row++;

        const auto milkRecepItemsByDeliv = items.values(delivererId);

        Item itemResultByDeliv(milkRecepItemsByDeliv.first().delivererName);
        for(const auto &milkRecepItem: milkRecepItemsByDeliv)
            sumItems(itemResultByDeliv, milkRecepItem);


        setSomeCalc(itemResultByDeliv);

        print.addRow(itemToPrintRow(itemResultByDeliv, row));

        sumItems(itemResults, itemResultByDeliv);
    }

    setSomeCalc(itemResults);

    int mergeCount = 0;
    auto itemRow = itemToPrintRow(itemResults);
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

    cursor.insertText(settings->getFirmName(), textCharFormat);
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
    cursor.insertText(tr("Приемщик молока: ") + settings->getMilkInspector(), textCharFormat);
    cursor.insertBlock();

    cursor.movePosition(QTextCursor::End);

    QTextFrameFormat bottomFrameFormat;
    bottomFrameFormat.setPadding(4);
    cursor.insertFrame(bottomFrameFormat);

    cursor.setBlockFormat(textBlockFormat);

    const auto minMaxPrice = milkReception->getMinMaxPriceLiter(dateMin, dateMax);
    if (!minMaxPrice.isEmpty()) {
        cursor.insertText(tr("Цена: %1").arg(minMaxPrice.first() == minMaxPrice.last() ?
                                                 QString::number(minMaxPrice.first()) :
                                                 QString::number(minMaxPrice.first(), 'f', 2) + " - " +
                                                 QString::number(minMaxPrice.last(), 'f', 2)));
        cursor.insertBlock();
    }
    cursor.insertText(tr("Деньги в сумме: "), textCharFormat);
    cursor.insertBlock();
    cursor.insertText(tr("Получил и выдал согласно ведомости приемщик молока______") + settings->getMilkInspector_2(),
                      textCharFormat);
    cursor.insertBlock();
    cursor.insertText(tr("Директор ") + settings->getFirmName(), textCharFormat);

    print.showDialog();
}

CalcFrame::CalcItems CalcFrame::getItemsData()
{
    auto milkReception = m_mainWindow->getDatabase()->milkReception();

    CalcItems items;

    QSqlQuery query;
    query.prepare(getPrepQueryStr());
    if (!addBindValueToQuery(query))
        return items;
    if (!query.exec()) {
        QMessageBox::critical(this, Constants::appName(), tr("Не удалось выполнить запрос данных для расчетов "
                                                             "по причине: \n\t\"") + query.lastError().text() + "\"");
        return items;
    }

    // номера столбцов соответствуют запросу
    const auto //mrIdColPos = milkReception->getColumnPosition(milkReception->getNameColumnId()),
            mrIdDelivColPos = milkReception->getColumnPosition(milkReception->getNameColumnIdDeliverer()),
            mrNameDelivColPos = milkReception->getColumnPosition(milkReception->getNameColumnDelivererName()),
            //            mrIdMilkPointColPos = milkReception->getColumnPosition(milkReception->getNameColumnMilkPointId()),
            mrNameMilkPointColPos = milkReception->getColumnPosition(milkReception->getNameColumnMilkPointName()),
            mrDeliveryDateColPos = milkReception->getColumnPosition(milkReception->getNameColumnDeliveryDate()),
            mrPriceLiterColPos = milkReception->getColumnPosition(milkReception->getNameColumnPriceLiter()),
            mrLitersColPos = milkReception->getColumnPosition(milkReception->getNameColumnLiters()),
            mrFatColPos = milkReception->getColumnPosition(milkReception->getNameColumnFat());
    int row = 0;

    while (query.next())
    {
        /*      query.value(mrIdMilkPointColPos).toLongLong();
        query.value(mrIdColPos).toLongLong();*/
        Item item;
        item.delivererName = query.value(mrNameDelivColPos).toString();
        item.milkPointName = query.value(mrNameMilkPointColPos).toString();
        item.deliveryDate = query.value(mrDeliveryDateColPos).toDate();
        item.priceLiter = query.value(mrPriceLiterColPos).toFloat();
        item.liters = query.value(mrLitersColPos).toFloat();
        item.fat = query.value(mrFatColPos).toFloat();

        setAllCalc(item);
        items.insert(query.value(mrIdDelivColPos).toLongLong(), item);

        row++;
    }

    return items;
}

QString CalcFrame::getPrepQueryStr() const
{
    auto milkReception = m_mainWindow->getDatabase()->milkReception();
    const auto select = milkReception->selectAll();

    auto where = QString();

    if (isCalcByDeliverer() || isCalcByDate() || isCalcByMilkPoint()) {

        if (isCalcByDeliverer())
            where.append(milkReception->getNameColumnIdDeliverer(true) + " = ?");

        if (isCalcByDate()) {
            if (!where.isEmpty())
                where.append(" AND ");
            where.append(milkReception->getNameColumnDeliveryDate(true) + " BETWEEN ? and ?");
        }
        if (isCalcByMilkPoint()) {
            if (!where.isEmpty())
                where.append(" AND ");
            where.append(milkReception->getNameColumnMilkPointId(true) + " = ?");
        }

        if (!where.isEmpty())
            where.prepend(" WHERE ");
    }

    return select + where;
}

bool CalcFrame::addBindValueToQuery(QSqlQuery &query)
{
    auto milkReception = m_mainWindow->getDatabase()->milkReception();

    auto isOk = true;

    if (isCalcByDeliverer()) {
        const auto idColumn = milkReception->getDeliverers()->getColumnPosition(
                    milkReception->getDeliverers()->getNameColumnId());
        const auto _id = Utils::Main::getCurValueFromComboBoxModel(ui->comboBoxFilterDeliverers, idColumn).toLongLong();
        if (Utils::Main::isAutoIncrIdIsValid(_id))
            query.addBindValue(_id);
        else {
            QMessageBox::critical(this, Constants::appName(), tr("Ошибка взятия id сдатчика"));
            isOk = false;
        }
    }
    if (isCalcByDate()) {
        const auto dateMin = ui->dateEditFilterStart->date(),
                dateMax = ui->dateEditFilterEnd->date();

        if (dateMin.isValid() && dateMax.isValid()) {
            query.addBindValue(dateMin.toString(Constants::defaultDateFormat()));
            query.addBindValue(dateMax.toString(Constants::defaultDateFormat()));
        } else {
            QMessageBox::critical(this, Constants::appName(), tr("Ошибка взятия даты"));
            isOk = false;
        }
    }
    if (isCalcByMilkPoint()) {
        const auto idColumn = milkReception->getMilkPoints()->getColumnPosition(
                    milkReception->getMilkPoints()->getNameColumnId());
        const auto _id = Utils::Main::getCurValueFromComboBoxModel(ui->comboBoxFilterMilkPoints, idColumn).toLongLong();
        if (Utils::Main::isAutoIncrIdIsValid(_id))
            query.addBindValue(_id);
        else {
            QMessageBox::critical(this, Constants::appName(), tr("Ошибка взятия id молокопункта"));
            isOk = false;
        }
    }

    return isOk;
}

void CalcFrame::fillTableWidget(const CalcItems &items)
{
    const auto &calcSettings = m_mainWindow->getSettings()->getCalc();

    ui->tableWidgetCalc->setColumnCount(0);
    ui->tableWidgetCalc->setRowCount(0);
    ui->tableWidgetCalc->clear();

    int colCountToShow = 0;
    const auto &calcColumns = calcSettings.columns;
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

    const auto uniqueKeys = items.uniqueKeys();

    const auto itemsCount = items.size();
    ui->tableWidgetCalc->setRowCount(itemsCount);

    Item itemResults(tr("Итого"), "-");

    int row = 0;
    for (const auto delivererId: uniqueKeys)
    {
        const auto milkRecepItemsByDeliv = items.values(delivererId);
        const auto firstMr = milkRecepItemsByDeliv.first();
        Item itemResultByDeliv(QString("->%1<-").arg(firstMr.delivererName), firstMr.milkPointName);

        const auto oldRow = row;
        for(const auto &milkRecepItem: milkRecepItemsByDeliv)
        {
            sumItems(itemResultByDeliv, milkRecepItem);

            setTableWidgetItem(row, milkRecepItem, calcSettings.textBackColor,
                               calcSettings.textFont);
            row++;
        }

        setSomeCalc(itemResultByDeliv);

        if (row - oldRow > 1) {
            ui->tableWidgetCalc->insertRow(row);
            setTableWidgetItem(row, itemResultByDeliv, calcSettings.delivResultColor,
                               calcSettings.delivResultFont);
            row++;
        }
        sumItems(itemResults, itemResultByDeliv);
    }

    setSomeCalc(itemResults);

    if (itemsCount > 1) {
        ui->tableWidgetCalc->insertRow(row);
        setTableWidgetItem(row, itemResults, calcSettings.allResultColor,
                           calcSettings.allResultFont);
    }

    //    ui->tableWidgetCalc->resizeColumnsToContents();
}

void CalcFrame::setTableWidgetItem(const int row, const Item &item, const QColor &color, const QFont &font)
{
    const auto &calcColumns = m_mainWindow->getSettings()->getCalc().columns;

    int colCountToShow = 0;
    for (int i = 0; i < calcColumns.size(); ++i) {
        const auto &col = calcColumns[i];

        if (col.isShow) {
            auto _item = new QTableWidgetItem(getValueFromItem(item, (Columns)i));
            _item->setBackgroundColor(color);
            _item->setFont(font);
            ui->tableWidgetCalc->setItem(row, colCountToShow, _item);

            colCountToShow++;
        }
    }
}

QString CalcFrame::getValueFromItem(const CalcFrame::Item &item, const Columns column) const
{
    auto value = .0f;

    switch (column)
    {
    case Columns::Name:
        return item.delivererName;
    case Columns::MilkPointName:
        return item.milkPointName;
    case Columns::Date:
        return item.deliveryDate.toString(m_mainWindow->getSettings()->getCalc().dateFormat);
    case Columns::PriceLiter:
        value = item.priceLiter;
        break;
    case Columns::Liters:
        value = item.liters;
        break;
    case Columns::Fat:
        value = item.fat;
        break;
    case Columns::Protein:
        value = item.protein;
        break;
    case Columns::FatUnits:
        value = item.fatUnits;
        break;
    case Columns::RankWeight:
        value = item.rankWeight;
        break;
    case Columns::PayWithOutPrem:
        value = item.paymentWithOutPremium;
        break;
    case Columns::Premium:
        value = item.premiumForFat;
        break;
    case Columns::Sum:
        value = item.sum;
        break;
    default:
        return QString();
    }

    const auto &calcColumn = m_mainWindow->getSettings()->getCalc().columns[(int)column];
    return QString::number(value, 'f', calcColumn.prec);
}

void CalcFrame::setAllCalc(CalcFrame::Item &item)
{
    const auto _calc = Utils::Calc::getCalculations(item.liters, item.fat, item.priceLiter);
    item.protein = _calc.protein;
    item.fatUnits = _calc.fatUnits;
    item.rankWeight = _calc.rankWeight;
    item.paymentWithOutPremium = _calc.paymentWithOutPremium;
    item.premiumForFat = _calc.premiumForFat;
    item.sum = _calc.sum;
}

void CalcFrame::setSomeCalc(CalcFrame::Item &item)
{
    item.fat = Utils::Calc::fat(item.fatUnits, item.liters);
    item.protein = Utils::Calc::protein(item.fat);
    item.rankWeight = Utils::Calc::rankWeight(item.fatUnits);
}

void CalcFrame::sumItems(CalcFrame::Item &left, const CalcFrame::Item &right)
{
    left.liters += right.liters;
    left.fatUnits += right.fatUnits;
    left.paymentWithOutPremium += right.paymentWithOutPremium;
    left.premiumForFat += right.premiumForFat;
    left.sum += right.sum;
}

CalcFrame::Item::Item():
    delivererName(QString()),
    milkPointName(QString()),
    deliveryDate(QDate()),
    priceLiter(.0f),
    liters(.0f),
    fat(.0f),
    protein(.0f),
    fatUnits(.0f),
    rankWeight(.0f),
    paymentWithOutPremium(.0f),
    premiumForFat(.0f),
    sum(.0f)
{

}

CalcFrame::Item::Item(const QString &_delivererName, const QString &_milkPointName,
                      const QDate &_deliveryDate, const float _liters, const float _fat,
                      const float _priceLiter, const float _protein, const float _fatUnits, const float _rankWeight,
                      const float _paymentWithOutPremium, const float _premiumForFat, const float _sum):
    delivererName(_delivererName),
    milkPointName(_milkPointName),
    deliveryDate(_deliveryDate),
    priceLiter(_priceLiter),
    liters(_liters),
    fat(_fat),
    protein(_protein),
    fatUnits(_fatUnits),
    rankWeight(_rankWeight),
    paymentWithOutPremium(_paymentWithOutPremium),
    premiumForFat(_premiumForFat),
    sum(_sum)
{

}
