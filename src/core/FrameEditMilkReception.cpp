#include "FrameEditMilkReception.h"
#include "ui_FrameEditMilkReception.h"

#include "MainWindow.h"
#include "base/Database.h"
#include "SortFilterMilkReceptionTable.h"
#include "ChooseIdDelegate.h"
#include "DateEditDelegate.h"
#include "Utils.h"
// Qt
#include <QMessageBox>
#include <QDebug>

USE_DB_NAMESPACE
using utm = Utils::Main;


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
    localities = m_mainWindow->database()->localities();
    deliverers = m_mainWindow->database()->deliverers();
    milkPoints = m_mainWindow->database()->milkPoints();
    milkReception = m_mainWindow->database()->milkReception();

    m_proxy->setSourceModel(m_mainWindow->database()->milkReception());
    ui->tableViewEditMilkReceptions->setModel(m_proxy);

    ui->comboBoxFilterDeliverers->setModel(deliverers);
    ui->comboBoxFilterDeliverers->setModelColumn(DT_NAME);
    if (deliverers->rowCount() > 0) {
        ui->comboBoxFilterDeliverers->setCurrentIndex(0);
    }

    ui->comboBoxFilterMilkPoints->setModel(milkPoints);
    ui->comboBoxFilterMilkPoints->setModelColumn(MPT_NAME);
    if (milkPoints->rowCount() > 0) {
        ui->comboBoxFilterMilkPoints->setCurrentIndex(0);
    }

    ui->tableViewEditMilkReceptions->setItemDelegateForColumn(RMT_DELIVERER_NAME,
                                                              new ChooseIdDelegate(deliverers,
                                                                                   RMT_ID_DELIVERER,
                                                                                   tr("Выбор сдатчика"), this));
    ui->tableViewEditMilkReceptions->setItemDelegateForColumn(RMT_MILK_POINT_NAME,
                                                              new ChooseIdDelegate(milkPoints,
                                                                                   RMT_MILK_POINT_ID,
                                                                                   tr("Выбор молокопункта"), this));
    ui->tableViewEditMilkReceptions->setItemDelegateForColumn(RMT_DELIVERY_DATE, new DateEditDelegate);

    ui->tableViewEditMilkReceptions->hideColumn(RMT_ID);
    ui->tableViewEditMilkReceptions->hideColumn(RMT_ID_DELIVERER);
    ui->tableViewEditMilkReceptions->hideColumn(RMT_MILK_POINT_ID);
}

void FrameEditMilkReception::chooseDeliverer()
{
    if (ui->groupBoxFilterDeliverers->isChecked()) {
        const auto id = utm::getCurValueFromComboBoxModel(
                    ui->comboBoxFilterDeliverers, DT_ID).toLongLong();
        m_proxy->setFilterDelivererId(id);
    } else
        m_proxy->setFilterDelivererId(-1);
}

void FrameEditMilkReception::chooseMilkPoint()
{
    if (ui->groupBoxFilterMilkPoints->isChecked()) {
        m_proxy->setFilterMilkPointId(utm::getCurValueFromComboBoxModel(
                                          ui->comboBoxFilterMilkPoints, MPT_ID).toLongLong());
    } else
        m_proxy->setFilterMilkPointId(-1);
}

void FrameEditMilkReception::chooseDates()
{
    if (ui->dateEditFilterEnd->date() <= ui->dateEditFilterStart->date())
        ui->dateEditFilterEnd->setDate(ui->dateEditFilterStart->date());

    if (ui->groupBoxFilterDate->isChecked())
        m_proxy->setDatesBetween(ui->dateEditFilterStart->date(), ui->dateEditFilterEnd->date());
    else
        m_proxy->setDatesBetween(QDate(), QDate());
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

    if (utm::yesNoWarnMsgBox(this, tr("Для удаления выбраны(а) %1 строк(а). Желаете продолжить?").arg(rowsCount)))
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
