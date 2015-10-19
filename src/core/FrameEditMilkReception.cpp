#include "FrameEditMilkReception.h"
#include "ui_FrameEditMilkReception.h"

#include "MainWindow.h"
#include "base/Database.h"
#include "SortFilterMilkReceptionTable.h"
#include "ChooseIdDelegate.h"
#include "DateEditDelegate.h"
#include "Utils.h"
// qt
#include <QMessageBox>
#include <QDebug>

FrameEditMilkReception::FrameEditMilkReception(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FrameEditMilkReception),
    m_mainWindow(nullptr),
    localities(nullptr),
    deliverers(nullptr),
    milkPoints(nullptr),
    milkReception(nullptr),
    m_proxy(new SortFilterMilkReceptionTable)
{
    ui->setupUi(this);
    m_proxy->setParent(this);

    connect(ui->groupBoxFilterDeliverers, SIGNAL(toggled(bool)), SLOT(chooseDeliverer()));
    connect(ui->comboBoxFilterDeliverers, SIGNAL(currentIndexChanged(int)), SLOT(chooseDeliverer()));
    connect(ui->groupBoxFilterMilkPoints, SIGNAL(toggled(bool)), SLOT(chooseMilkPoint()));
    connect(ui->comboBoxFilterMilkPoints, SIGNAL(currentIndexChanged(int)), SLOT(chooseMilkPoint()));
    connect(ui->groupBoxFilterDate, SIGNAL(toggled(bool)), SLOT(chooseDates()));
    connect(ui->dateEditFilterStart, SIGNAL(dateChanged(QDate)), SLOT(chooseDates()));
    connect(ui->dateEditFilterEnd, SIGNAL(dateChanged(QDate)), SLOT(chooseDates()));
    connect(ui->pushButtonRemove, &QPushButton::clicked, this, &FrameEditMilkReception::removeChoosenItems);

    ui->dateEditFilterStart->setDate(QDate::currentDate());
    ui->dateEditFilterEnd->setDate(ui->dateEditFilterStart->date());
}

FrameEditMilkReception::~FrameEditMilkReception()
{
    delete ui;
}

void FrameEditMilkReception::setMainWindow(MainWindow *mainWindow)
{
    m_mainWindow = mainWindow;
}

void FrameEditMilkReception::setup()
{
    localities = m_mainWindow->getDatabase()->localities();
    deliverers = m_mainWindow->getDatabase()->deliverers();
    milkPoints = m_mainWindow->getDatabase()->milkPoints();
    milkReception = m_mainWindow->getDatabase()->milkReception();

    m_proxy->setSourceModel(m_mainWindow->getDatabase()->milkReception());
    ui->tableViewEditMilkReceptions->setModel(m_proxy);

    const auto delivNameCol = deliverers->getColumnPosition(deliverers->getNameColumnName()),
            milkPointNameCol = milkPoints->getColumnPosition(milkPoints->getNameColumnName()),
            mrColId = milkReception->getColumnPosition(milkReception->getNameColumnId()),
            mrColNameDeliv = milkReception->getColumnPosition(milkReception->getNameColumnDelivererName()),
            mrColNameMilkPoint = milkReception->getColumnPosition(milkReception->getNameColumnMilkPointName()),
            mrColIdDeliv = milkReception->getColumnPosition(milkReception->getNameColumnIdDeliverer()),
            mrColIdMilkPoint = milkReception->getColumnPosition(milkReception->getNameColumnMilkPointId()),
            mrColDelivDate = milkReception->getColumnPosition(milkReception->getNameColumnDeliveryDate());

    ui->comboBoxFilterDeliverers->setModel(deliverers);
    ui->comboBoxFilterDeliverers->setModelColumn(delivNameCol);

    ui->comboBoxFilterMilkPoints->setModel(milkPoints);
    ui->comboBoxFilterMilkPoints->setModelColumn(milkPointNameCol);

    ui->tableViewEditMilkReceptions->setItemDelegateForColumn(mrColNameDeliv, new ChooseIdDelegate(deliverers, mrColIdDeliv,
                                                                                                   tr("Выбор сдатчика"), this));
    ui->tableViewEditMilkReceptions->setItemDelegateForColumn(mrColNameMilkPoint, new ChooseIdDelegate(milkPoints, mrColIdMilkPoint,
                                                                                                       tr("Выбор молокопункта"), this));
    ui->tableViewEditMilkReceptions->setItemDelegateForColumn(mrColDelivDate, new DateEditDelegate);

    ui->tableViewEditMilkReceptions->hideColumn(mrColId);
    ui->tableViewEditMilkReceptions->hideColumn(mrColIdDeliv);
    ui->tableViewEditMilkReceptions->hideColumn(mrColIdMilkPoint);
}

void FrameEditMilkReception::chooseDeliverer()
{
    if (ui->groupBoxFilterDeliverers->isChecked()) {
        const auto delivIdCol = deliverers->getColumnPosition(deliverers->getNameColumnId());

        const auto id = Utils::Main::getCurValueFromComboBoxModel(
                    ui->comboBoxFilterDeliverers, delivIdCol).toLongLong();
        m_proxy->setFilterDelivererId(id);
    } else
        m_proxy->setFilterDelivererId(-1);
}

void FrameEditMilkReception::chooseMilkPoint()
{
    if (ui->groupBoxFilterMilkPoints->isChecked()) {
        const auto milkPointsIdCol = milkPoints->getColumnPosition(milkPoints->getNameColumnId());
        m_proxy->setFilterMilkPointId(Utils::Main::getCurValueFromComboBoxModel(
                                          ui->comboBoxFilterMilkPoints, milkPointsIdCol).toLongLong());
    } else
        m_proxy->setFilterMilkPointId(-1);
}

void FrameEditMilkReception::chooseDates()
{
    if (ui->dateEditFilterEnd->date() <= ui->dateEditFilterStart->date())
        ui->dateEditFilterEnd->setDate(ui->dateEditFilterStart->date());

    if (ui->groupBoxFilterDate->isChecked()) {
        m_proxy->setFilterMinimumDate(ui->dateEditFilterStart->date());
        m_proxy->setFilterMaximumDate(ui->dateEditFilterEnd->date());
    } else {
        m_proxy->setFilterMinimumDate(QDate());
        m_proxy->setFilterMaximumDate(QDate());
    }
}

void FrameEditMilkReception::removeChoosenItems()
{
    const auto selectionModel = ui->tableViewEditMilkReceptions->selectionModel();

    if (!selectionModel->hasSelection()) {
        QMessageBox::information(this, Constants::appName(), tr("Отсутствуют данные для удаления"));
        return;
    }

    const auto selectedRows = selectionModel->selectedRows();

    const auto rowsCount = selectedRows.size();

    if (Utils::Main::yesNoWarnMsgBox(this, tr("Для удаления выбраны(а) %1 строк(а). Желаете продолжить?").arg(rowsCount)))
    {
        for(const auto &index: selectedRows)
        {
            const auto modelIndex = m_proxy->mapToSource(index);
            const auto id = milkReception->index(modelIndex.row(), 0).data().toLongLong();
            milkReception->remove(id);
        }
    }
    milkReception->refresh();
}
