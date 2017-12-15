#include "MilkCore.h"

#include <DbUtils.h>
#include <HtmlBuilder.h>
#include <HtmlTable.h>
// Qt
#include <QDebug>
#include <QPrinter>
#include <QTextDocument>
#include <QPrintDialog>
#include <QPrintPreviewDialog>

using SC = SettingsConstants;
using COLTYPE = SC::SettingsColumnType;
using DBC = DbConstants;


MilkCore::MilkCore(QObject *parent) :
    QObject(parent)
{
    m_settings = new Settings();
    m_database = new Database();

    auto print = m_settings->print();
    print->setSettingsColumns(
    {
                    new SettingsColumn(QObject::tr("№ п/п"), COLTYPE::SerialNumber, SC::COL_DEF_PREC, true, print),
                    new SettingsColumn(QObject::tr("Ф. И. О."), COLTYPE::String, SC::COL_DEF_PREC, true, print),
                    new SettingsColumn(QObject::tr("Физ. вес"), COLTYPE::Double, SC::COL_DEF_PREC, true, print),
                    new SettingsColumn(QObject::tr("% жир"), COLTYPE::Double, SC::COL_DEF_PREC, true, print),
                    new SettingsColumn(QObject::tr("Белок"), COLTYPE::Double, SC::COL_DEF_PREC, true, print),
                    new SettingsColumn(QObject::tr("Жироед."), COLTYPE::Double, SC::COL_DEF_PREC, false, print),
                    new SettingsColumn(QObject::tr("Зачет. вес"), COLTYPE::Double, SC::COL_DEF_PREC, true, print),
                    new SettingsColumn(QObject::tr("Оплата(без премии)"), COLTYPE::Double, SC::COL_DEF_PREC, false, print),
                    new SettingsColumn(QObject::tr("Премия"), COLTYPE::Double, SC::COL_DEF_PREC, false, print),
                    new SettingsColumn(QObject::tr("Сумма"), COLTYPE::Double, SC::COL_DEF_PREC, true, print),
                    new SettingsColumn(QObject::tr("Подпись"), COLTYPE::String, SC::COL_DEF_PREC, true, print)
                });
    auto calc = m_settings->calc();
    calc->setSettingsColumns(
    {
                    new SettingsColumn(QObject::tr("Ф. И. О."), COLTYPE::String, SC::COL_DEF_PREC, true, calc),
                    new SettingsColumn(QObject::tr("Молокопункты"), COLTYPE::String, SC::COL_DEF_PREC, true, calc),
                    new SettingsColumn(QObject::tr("Дата сдачи"), COLTYPE::Date, SC::COL_DEF_PREC, true, calc),
                    new SettingsColumn(QObject::tr("Цена за литр"), COLTYPE::Double, SC::COL_DEF_PREC, true, calc),
                    new SettingsColumn(QObject::tr("Литры"), COLTYPE::Double, SC::COL_DEF_PREC, true, calc),
                    new SettingsColumn(QObject::tr("Жиры"), COLTYPE::Double, SC::COL_DEF_PREC, true, calc),
                    new SettingsColumn(QObject::tr("Белок"), COLTYPE::Double, SC::COL_DEF_PREC, true, calc),
                    new SettingsColumn(QObject::tr("Жироед."), COLTYPE::Double, SC::COL_DEF_PREC, true, calc),
                    new SettingsColumn(QObject::tr("Зачет. вес"), COLTYPE::Double, SC::COL_DEF_PREC, true, calc),
                    new SettingsColumn(QObject::tr("Оплата(без премии)"), COLTYPE::Double, SC::COL_DEF_PREC, true, calc),
                    new SettingsColumn(QObject::tr("Премия"), COLTYPE::Double, SC::COL_DEF_PREC, true, calc),
                    new SettingsColumn(QObject::tr("Сумма"), COLTYPE::Double, SC::COL_DEF_PREC, true, calc)
                });
}

MilkCore::~MilkCore() {}

Settings *MilkCore::settings() const { return m_settings; }

Database *MilkCore::database() const { return m_database; }

CalculatedItem *MilkCore::getCalculations(const QString &where)
{
    auto root = new CalculatedItem;
    root->setDelivererName("All");

    QHash<int, MilkPointData> milkPointsData;
    QHash<int, CalculatedItem *> deliverersCi;

    auto getMilkPoint = [this, &milkPointsData](const int id) -> MilkPointData {
        if (milkPointsData.contains(id))
            return milkPointsData[id];
        else {
            const auto mpdOptional = database()->milkPoints()->getMilkPointData(id);
            if (mpdOptional) {
                milkPointsData.insert(id, mpdOptional.value());
                return mpdOptional.value();
            }
        }
        return {};
    };

    auto getDelivererCi = [this, &deliverersCi](const int id) -> CalculatedItem* {
        if (deliverersCi.contains(id))
            return deliverersCi[id];
        else {
            const auto delivererOptional = database()->deliverers()->getDelivererData(id);
            if (delivererOptional) {
                const auto delivererData = delivererOptional.value();

                auto delivererCi = new CalculatedItem;
                delivererCi->setDelivererName(delivererData.name());

                deliverersCi.insert(id, delivererCi);
                return delivererCi;
            }
        }

        return Q_NULLPTR;
    };

    const auto milkReceptions = database()->milkReception()->getMilkReceptionsData(where);
    for (const auto mr : milkReceptions) {
        auto delivererCi = getDelivererCi(mr.delivererId());

        const auto milkPointData = getMilkPoint(mr.milkPointId());

        auto milkReceptionCalcItem = new CalculatedItem(mr.liters(), mr.fat(), mr.priceLiter(), delivererCi);
        milkReceptionCalcItem->setDeliveryDate(mr.deliveryDate());
        milkReceptionCalcItem->setMilkPointName(milkPointData.name());

        delivererCi->addItem(milkReceptionCalcItem);
    }
    for (auto item : deliverersCi) {
        item->setParent(root);
        root->addItem(item);
    }

    return root;
}

CalcItemModel *MilkCore::getCalcItemModel(const qlonglong delivererId, const qlonglong milkPointId,
                                          const QDate &dateFrom, const QDate &dateTo)
{
    const auto delivererWhere = delivererId <= 0 ?
                "" : QString("%1 = %2")
                .arg(DBC::TMR_FN_ID_DELIVERER)
                .arg(delivererId);
    const auto milkPointWhere = milkPointId <= 0 ?
                "" : QString("%1 = %2")
                .arg((delivererWhere.isEmpty() ? "" : " AND ") + DBC::TMR_FN_MILK_POINT_ID)
                .arg(milkPointId);
    const auto dateWhere = !dateFrom.isValid() ?
                "" : QString("%1 BETWEEN %2 AND %3")
                .arg((milkPointWhere.isEmpty() ? "" : " AND ") + DBC::TMR_FN_DELIVERY_DATE)
                .arg(dateFrom.toString(SC::defaultDateFormat()))
                .arg(dateTo.toString(SC::defaultDateFormat()));

    auto model = new CalcItemModel(getCalculations(delivererWhere + milkPointWhere + dateWhere), this);
    model->setDateFormat(SC::defaultDateFormat());
    return model;
}

void MilkCore::printHtml(const QString &html, bool isShowPreview)
{
    QPrinter printer(QPrinter::HighResolution);

    auto print = [&printer, &html]() {
        QTextDocument doc;
        doc.setHtml(html);
        doc.print(&printer);
    };

    if(!isShowPreview)
    {
        QPrintDialog dialog(&printer);
        dialog.setWindowTitle(tr("Печать документа"));
        if (dialog.exec() == QDialog::Accepted) {
            print();
        }
    } else {
        QPrintPreviewDialog dialog(&printer);
        dialog.setWindowFlags(Qt::Window);
        connect(&dialog, &QPrintPreviewDialog::paintRequested, this, print);
        dialog.exec();
    }
}

void MilkCore::printCalculations(CalculatedItem *calcItem, bool isShowPreview)
{
    auto printSet = settings()->print();
    const auto columns = printSet->getColumns();

    auto headerRow = new HtmlTableHeaderRow;
    {
        const auto font = printSet->tableHeaderFont();
        const auto color = printSet->tableHeaderColor();
        for (SettingsColumn *column : columns) {
            if (column->isShow())
                headerRow->addHeader(new HtmlTableHeader{
                                         { new HtmlFont(font, color, {new HtmlContent(column->display())}), }
                                     });
        }
    }

    auto addStrContent = [](HtmlTableCell *cell, const QString &content,
            const QFont &font, const QColor &color)
    {
        if (cell)
            cell->addElement(new HtmlFont(font, color, {new HtmlContent(content)}));
    };

    auto addFloatContent = [&columns, &addStrContent](HtmlTableCell *cell, const int colPos,
            const float value, const QFont &font, const QColor &color)
    {
        if (cell)
            addStrContent(cell, QString::number(value, 'f', columns[colPos]->prec()), font, color);
    };

    auto createCell = [&columns](HtmlTableRow *row, const int colPos) -> HtmlTableCell*
    {
        if (columns[colPos]->isShow()) {
            auto cell = new HtmlTableCell();
            row->addCell(cell);
            return cell;
        }
        return Q_NULLPTR;
    };

    int c = 0;
    TableRows rows;
    {
        const auto font = printSet->tableTextFont();
        const auto color = printSet->tableTextColor();
        for (CalculatedItem *item : calcItem->getItems()) {
            auto row = new HtmlTableRow;
            addStrContent(createCell(row, 0), QString::number(++c), font, color);
            addStrContent(createCell(row, 1), item->delivererName(), font, color);
            addFloatContent(createCell(row, 2), 2, item->liters(), font, color);
            addFloatContent(createCell(row, 3), 3, item->fat(), font, color);
            addFloatContent(createCell(row, 4), 4, item->protein(), font, color);
            addFloatContent(createCell(row, 5), 5, item->fatUnits(), font, color);
            addFloatContent(createCell(row, 6), 6, item->rankWeight(), font, color);
            addFloatContent(createCell(row, 7), 7, item->paymentWithOutPremium(), font, color);
            addFloatContent(createCell(row, 8), 8, item->premiumForFat(), font, color);
            addFloatContent(createCell(row, 9), 9, item->sum(), font, color);
            addStrContent(createCell(row, 10), "", font, color);
            rows.append(row);
        }
    }

    {
        const auto font = printSet->tableResultFont();
        const auto color = printSet->tableResultColor();
        auto row = new HtmlTableRow;
        if (HtmlTableCell *cell = createCell(row, 1)) {
            cell->addAttribute({"colspan=2"});
            addStrContent(cell, calcItem->delivererName(), font, color);
        }
        addFloatContent(createCell(row, 2), 2, calcItem->liters(), font, color);
        addFloatContent(createCell(row, 3), 3, calcItem->fat(), font, color);
        addFloatContent(createCell(row, 4), 4, calcItem->protein(), font, color);
        addFloatContent(createCell(row, 5), 5, calcItem->fatUnits(), font, color);
        addFloatContent(createCell(row, 6), 6, calcItem->rankWeight(), font, color);
        addFloatContent(createCell(row, 7), 7, calcItem->paymentWithOutPremium(), font, color);
        addFloatContent(createCell(row, 8), 8, calcItem->premiumForFat(), font, color);
        addFloatContent(createCell(row, 9), 9, calcItem->sum(), font, color);
        addStrContent(createCell(row, 10), "", font, color);
        rows.append(row);
    }

    HtmlBuilder builder;
    builder.setTitle("Example")
            ->addBodyElement(
                (new HtmlTable(new HtmlTableCaption({new HtmlFont(printSet->captionTextFont(),
                                                     printSet->captionColor(),
                                                     {new HtmlContent("Caption")})
                                                    }),
    {
                                   {QString("width=%1%").arg(printSet->tableWidth())},
                                   {QString("border=%1").arg(printSet->tableBorderWidth())},
                                   {QString("cellspacing=%1").arg(printSet->cellSpacing())},
                                   {QString("cellspadding=%1").arg(printSet->cellPadding())},
                               }))
                ->setHeaderRow(headerRow)
                ->setRows(rows));

    printHtml(builder.toString(), isShowPreview);
}

