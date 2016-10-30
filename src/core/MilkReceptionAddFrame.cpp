#include "MilkReceptionAddFrame.h"
#include "ui_MilkReceptionAddFrame.h"

#include "MainWindow.h"
#include "base/Database.h"
#include "src/delegates/DateEditDelegate.h"
#include "src/delegates/DoubleSpinBoxDelegate.h"
#include "Constants.h"
#include "Utils.h"
// Qt
#include <QMessageBox>
#include <QDebug>

USE_DB_NAMESPACE


MilkReceptionAddFrame::MilkReceptionAddFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::MilkReceptionAddFrame),
    m_mainWindow(nullptr),
    localities(nullptr),
    deliverers(nullptr),
    milkPoints(nullptr),
    milkReception(nullptr)
{
    ui->setupUi(this);

    initAddTableWidget();

    connect(ui->spinBoxReceptionCount, SIGNAL(valueChanged(int)), this, SLOT(changeRowsCount(int)));
    connect(ui->pushButtonInsert, &QPushButton::clicked, this, &MilkReceptionAddFrame::insertReceptionMilk);

    changeRowsCount(ui->spinBoxReceptionCount->value());

    /*auto p = ui->listViewDeliverers->palette();
    p.setColor(QPalette::Highlight, Qt::red);
    p.setColor(QPalette::Normal, QPalette::Highlight, Qt::red);
    p.setColor(QPalette::Disabled, QPalette::Highlight, Qt::red);
    ui->listViewDeliverers->setPalette(p);*/
}

MilkReceptionAddFrame::~MilkReceptionAddFrame()
{
    delete ui;
}

void MilkReceptionAddFrame::setMainWindow(MainWindow *mainWindow)
{
    m_mainWindow = mainWindow;
}

void MilkReceptionAddFrame::setPrice(const float price)
{
    ui->doubleSpinBoxPrice->setValue(static_cast<double>(price));
}

float MilkReceptionAddFrame::price() const
{
    return static_cast<float>(ui->doubleSpinBoxPrice->value());
}

void MilkReceptionAddFrame::setup()
{
    localities = m_mainWindow->getDatabase()->localities();
    deliverers = m_mainWindow->getDatabase()->deliverers();
    milkPoints = m_mainWindow->getDatabase()->milkPoints();
    milkReception = m_mainWindow->getDatabase()->milkReception();

    ui->listViewDeliverers->setModel(deliverers);
    ui->listViewDeliverers->setModelColumn(DT_NAME);
    ui->comboBoxMilkPoints->setModel(milkPoints);
    ui->comboBoxMilkPoints->setModelColumn(MPT_NAME);

    connect(localities, &Table::refreshed, this, &MilkReceptionAddFrame::refresheLocalities);
    connect(deliverers, &Table::refreshed, this, &MilkReceptionAddFrame::refresheDeliverers);
    connect(milkPoints, &Table::refreshed, this, &MilkReceptionAddFrame::refresheMilkPoints);
}

void MilkReceptionAddFrame::refresheLocalities()
{
    refresheDeliverers();
    refresheMilkPoints();
}

void MilkReceptionAddFrame::refresheDeliverers()
{
    ui->listViewDeliverers->setCurrentIndex(ui->listViewDeliverers->model()->index(0, 0));
}

void MilkReceptionAddFrame::refresheMilkPoints()
{
    ui->comboBoxMilkPoints->setCurrentIndex(0);
}

void MilkReceptionAddFrame::initAddTableWidget()
{
    ui->tableWidgetAddMilkReception->setColumnCount(3);

    QTableWidgetItem *dateHeaderItem = new QTableWidgetItem(tr("Дата сдачи"), (int)ColumnType::Date);
    dateHeaderItem->setTextAlignment(Qt::AlignVCenter);
    QTableWidgetItem *litersHeaderItem = new QTableWidgetItem(tr("Литры"), (int)ColumnType::Liters);
    litersHeaderItem->setTextAlignment(Qt::AlignVCenter);
    QTableWidgetItem *fatHeaderItem = new QTableWidgetItem(tr("Жиры"), (int)ColumnType::Fat);
    fatHeaderItem->setTextAlignment(Qt::AlignVCenter);

    ui->tableWidgetAddMilkReception->setHorizontalHeaderItem((int)Columns::Date, dateHeaderItem);
    ui->tableWidgetAddMilkReception->setHorizontalHeaderItem((int)Columns::Liters, litersHeaderItem);
    ui->tableWidgetAddMilkReception->setHorizontalHeaderItem((int)Columns::Fat, fatHeaderItem);

    ui->tableWidgetAddMilkReception->setItemDelegateForColumn((int)Columns::Date, new DateEditDelegate(this));
    ui->tableWidgetAddMilkReception->setItemDelegateForColumn((int)Columns::Liters, new DoubleSpinBoxDelegate(1.0f, this));
    ui->tableWidgetAddMilkReception->setItemDelegateForColumn((int)Columns::Fat, new DoubleSpinBoxDelegate(1.0f, this));
}

void MilkReceptionAddFrame::changeRowsCount(const int value)
{
    ui->tableWidgetAddMilkReception->setRowCount(value);
}

void MilkReceptionAddFrame::insertReceptionMilk()
{
    if (price() == 0) {
        QMessageBox::warning(this, Constants::appName(), tr("Укажите цену"));
        return;
    }
    if (!ui->listViewDeliverers->currentIndex().isValid()) {
        QMessageBox::warning(this, Constants::appName(), tr("Выберите сдатчика"));
        return;
    }

    auto deliverers = m_mainWindow->getDatabase()->deliverers();
    auto milkPoints = m_mainWindow->getDatabase()->milkPoints();

    const auto isNoDeliverers = deliverers->isEmpty(),
            isNoMilkPoints = milkPoints->isEmpty();

    if (isNoDeliverers || isNoMilkPoints) {
        if (isNoDeliverers) {
            if (Utils::Main::yesNoWarnMsgBox(this, tr("Чтобы внести сдачу молока необходим сдатчик. "
                                                      "Желаете добавить сейчас?"))) {
                m_mainWindow->addDeliverer();
            }
        }
        if (isNoMilkPoints) {
            if (Utils::Main::yesNoWarnMsgBox(this, tr("Чтобы внести сдачу молока необходим молокопункт. "
                                                      "Желаете добавить сейчас?"))) {
                m_mainWindow->addMilkPoint();
            }
        }

        return;
    }

    const auto idDeliverer = Utils::Main::getCurValueFromItemViewModel(ui->listViewDeliverers,
                                 DT_ID).toLongLong();
    if (!Utils::Main::isAutoIncrIdIsValid(idDeliverer)) {
        QMessageBox::critical(this, Constants::appName(), tr("Ошибка получения id сдатчика"));
        return;
    }

    const auto idMilkPoint = Utils::Main::getCurValueFromComboBoxModel(ui->comboBoxMilkPoints,
                                          MPT_ID).toLongLong();

    if (!Utils::Main::isAutoIncrIdIsValid(idMilkPoint)) {
        QMessageBox::critical(this, Constants::appName(), tr("Ошибка получения id молокопункта"));
        return;
    }

    auto allErrors = QString(), allWarnings = QString();

    auto milkReception = m_mainWindow->getDatabase()->milkReception();

    const auto headerTextDate = ui->tableWidgetAddMilkReception->horizontalHeaderItem((int)Columns::Date)->text(),
            headerTextLiters = ui->tableWidgetAddMilkReception->horizontalHeaderItem((int)Columns::Liters)->text(),
            headerTextFat = ui->tableWidgetAddMilkReception->horizontalHeaderItem((int)Columns::Fat)->text();

    for (int i = 0; i < ui->tableWidgetAddMilkReception->rowCount(); ++i)
    {
        auto error = QString(), warnings = QString();

        const auto indexDate = ui->tableWidgetAddMilkReception->model()->index(i, (int)Columns::Date),
                indexLiters = ui->tableWidgetAddMilkReception->model()->index(i, (int)Columns::Liters),
                indexFat = ui->tableWidgetAddMilkReception->model()->index(i, (int)Columns::Fat);

        if ((indexLiters.data().isNull() && indexFat.data().isNull()) ||
                (!indexLiters.isValid() && !indexFat.isValid()))
            continue;

        const auto deliveryDate = indexDate.data().toDate();
        const auto liters = indexLiters.data().toFloat(),
                fat = indexFat.data().toFloat();

        if (fat <= 0 && liters <= 0) {
            warnings.append(tr("Строка ") + QString::number(i + 1) + tr(" пропущенна"));
            allWarnings.append("\n" + warnings);
            continue;
        }

        if (!deliveryDate.isValid())
            error.append(QString("\tСтрока №%1 в столбце \"%2\": дата пуста или указана неверно.\n")
                         .arg(i + 1).arg(headerTextDate));

        if (liters <= .0f)
            error.append(QString("\tСтрока №%1 в столбце \"%2\": литры <= 0.\n")
                         .arg(i + 1).arg(headerTextLiters));
        if (fat <= .0f)
            error.append(QString("\tСтрока №%1 в столбце \"%2\": жиры <= 0.\n")
                         .arg(i + 1).arg(headerTextFat));

        if (fat > 6.0f)
            warnings.append(QString("\tСтрока №%1 в столбце \"%2\": жиры слишком велики.\n")
                            .arg(i + 1).arg(headerTextFat));

        if (!warnings.isEmpty())
            allWarnings.append("\n" + warnings);

        if (error.isEmpty())
        {
            MilkReceptionData mrd;
            mrd.setDelivererId(idDeliverer);
            mrd.setMilkPointId(idMilkPoint);
            mrd.setDeliveryDate(deliveryDate);
            mrd.setPriceLiter(price());
            mrd.setLiters(liters);
            mrd.setFat(fat);

            try {
                milkReception->insert(mrd);
                ui->tableWidgetAddMilkReception->model()->setData(indexLiters, .0f);
                ui->tableWidgetAddMilkReception->model()->setData(indexFat, .0f);
            } catch (const QString &err) {
                QMessageBox::warning(this, tr("Сдача молока"), tr("Ошибка присдаче молока: ") + err);
            }
        } else
            allErrors.append("\n" + error);
    }

    if (!allErrors.isEmpty())
        QMessageBox::critical(this, Constants::appName(), tr("Не удалось внести все данные из-за следующих ошибок: \n") + allErrors);
    else
        milkReception->refresh();

    if (!allWarnings.isEmpty())
        QMessageBox::information(this, Constants::appName(), tr("Возможно вы допустили следующие ошибки"
                                                                "(если это не так, просто, проигнорируйте данной уведомление): \n") + allWarnings);
}
