#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "base/Database.h"
#include "DelivererDialog.h"
#include "LocalityDialog.h"
#include "MilkPointDialog.h"
#include "DialogSettings.h"
#include "UpdatePriceDialog.h"
#include "Settings.h"
#include "Constants.h"
#include "Utils.h"
// Qt
#include <QGroupBox>
#include <QPushButton>
#include <QComboBox>
#include <QFileDialog>
#include <QToolBar>
#include <QMessageBox>
#include <QComboBox>
#include <QDebug>

USE_DB_NAMESPACE


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_groupBoxChooseMainLocality(new QGroupBox(tr("Выбрать населенный пункт"))),
    m_comboBoxChooseMainLocality(new QComboBox()),
    m_settings(new Settings),
    m_database(new Database()),
    m_dialogSettings(nullptr)
{
    ui->setupUi(this);

    setWindowTitle("version: " + Constants::getCurrentVersion().toString());

    m_database->setParent(this);

    ui->frameMilkReceptionAdd->setMainWindow(this);
    ui->frameCalc->setMainWindow(this);
    ui->frameEditReceptionMilk->setMainWindow(this);

    m_groupBoxChooseMainLocality->setParent(this);
    m_groupBoxChooseMainLocality->setCheckable(true);

    QHBoxLayout *hbLayout = new QHBoxLayout;
    hbLayout->addWidget(m_comboBoxChooseMainLocality);
    m_groupBoxChooseMainLocality->setLayout(hbLayout);

    addActionsToMenu();
    addActionsToToolBars();

    _readSettings();

    connect(ui->actionShowDialogSettings, &QAction::triggered, this, &MainWindow::showSettings);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);
    // db
    connect(ui->actionCreateDb, &QAction::triggered, this, &MainWindow::createDb);
    connect(ui->actionOpenDb, &QAction::triggered, this, &MainWindow::chooseDb);
    //    connect(ui->actionCloneDb, &QAction::triggered, this, &MainWindow::);
    // locality
    connect(ui->actionLocalityAdd, &QAction::triggered, this, &MainWindow::addLocality);
    connect(ui->actionLocalityEdit, &QAction::triggered, this, &MainWindow::updateLocality);
    connect(ui->actionLocalityDel, &QAction::triggered, this, &MainWindow::removeLocality);
    connect(m_comboBoxChooseMainLocality, SIGNAL(currentIndexChanged(int)), SLOT(chooseMainLocality()));
    connect(m_groupBoxChooseMainLocality, SIGNAL(toggled(bool)), SLOT(chooseMainLocality()));
    // deliverers
    connect(ui->actionDelivererAdd, &QAction::triggered, this, &MainWindow::addDeliverer);
    connect(ui->actionDelivererEdit, &QAction::triggered, this, &MainWindow::updateDeliverer);
    connect(ui->actionDelivererDel, &QAction::triggered, this, &MainWindow::removeDeliverer);
    // milk points
    connect(ui->actionMilkPointAdd, &QAction::triggered, this, &MainWindow::addMilkPoint);
    connect(ui->actionMilkPointEdit, &QAction::triggered, this, &MainWindow::updateMilkPoint);
    connect(ui->actionMilkPointDel, &QAction::triggered, this, &MainWindow::removeMilkPoint);
    // utils
    connect(ui->actionUpdatePrice, &QAction::triggered, this, &MainWindow::showUpdatePriceDialog);
    // help
    connect(ui->actionAbout, &QAction::triggered, this, [=]() {
        QMessageBox::about(this, Constants::appName(), tr("Версия программы: %1")
                           .arg(Constants::getCurrentVersion().toString()));
    });
    connect(ui->actionAboutQt, &QAction::triggered, this, [=]() {
        QMessageBox::aboutQt(this, Constants::appName());
    });
}

MainWindow::~MainWindow()
{
    _writeSettings();

    delete ui;
    delete m_settings;
}

void MainWindow::chooseDb()
{    
    QFileDialog dialog(this);
    dialog.setWindowTitle(tr("Выбор бд"));
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("Бд milk (*.mdb);; Любые файлы(*.*)");
    if (dialog.exec())
    {
        const QString dbName = dialog.selectedFiles().first();
        if (!dbName.isEmpty())
            openDb(dbName);
    }
}

void MainWindow::addDeliverer()
{
    if (m_database->localities()->isEmpty())
    {
        if(Utils::Main::yesNoWarnMsgBox(this, tr("Чтобы добавить хотя бы одного сдатчика "
                                                 "нужно сначала добавить населенный пункт. "
                                                 "Желаете это сделать сейчас?")))
        {
            addLocality();

            if (!m_database->localities()->isEmpty()) // если добавил
                QMessageBox::information(this, Constants::appName(), "Теперь можете добавить сдатчика!");
        }
    }

    if (!m_database->localities()->isEmpty()) { // если добавил
        DelivererDialog dialog(m_database->deliverers());
        dialog.setComboBoxCurIndex(m_comboBoxChooseMainLocality->currentIndex());
        dialog.exec();
    }
}

void MainWindow::addLocality()
{
    LocalityDialog dialog(m_database->localities());
    dialog.exec();

    m_groupBoxChooseMainLocality->setEnabled(!m_database->localities()->isEmpty());
}

void MainWindow::addMilkPoint()
{
    if (m_database->localities()->isEmpty())
    {
        if(Utils::Main::yesNoWarnMsgBox(this, tr("Чтобы добавить хотя бы один молокопункт "
                                                 "нужно сначала добавить населенный пункт. "
                                                 "Желаете это сделать сейчас?")))
        {
            addLocality();

            if (!m_database->localities()->isEmpty()) // если добавил
                QMessageBox::information(this, Constants::appName(), "Теперь можете добавить молокопункт!");
        }
    }

    if (!m_database->localities()->isEmpty()) {// если добавили
        MilkPointDialog dialog(m_database->milkPoints());
        dialog.setComboBoxCurIndex(m_comboBoxChooseMainLocality->currentIndex());
        dialog.exec();
    }
}

void MainWindow::_readSettings()
{
    m_settings->readSettings();

    ui->frameMilkReceptionAdd->setPrice(m_settings->getMain().priceLiter);
    const auto lastDb = m_settings->getMain().lastChoosenDb;

    if (lastDb.isEmpty() || !QFile(lastDb).exists())
    {
        QMessageBox msgBox;
        msgBox.setText(Constants::appName());
        msgBox.setInformativeText(tr("Не выбрана база данных. Желаете выбрать сейчас?"));

        QPushButton *createBtn = msgBox.addButton(tr("Создать"), QMessageBox::ActionRole);
        QPushButton *openBtn = msgBox.addButton(tr("Открыть"), QMessageBox::ActionRole);
        msgBox.addButton(QMessageBox::Cancel);

        msgBox.exec();

        if (msgBox.clickedButton() == openBtn)
            chooseDb();
        else if (msgBox.clickedButton() == createBtn)
            createDb();
    } else
        openDb(lastDb);
}

void MainWindow::addActionsToMenu()
{
    ui->menuDb->addAction(ui->actionCreateDb);
    ui->menuDb->addAction(ui->actionOpenDb);

    ui->menuFile->addAction(ui->actionShowDialogSettings);
    ui->menuFile->addAction(ui->actionExit);

    ui->menuLocalities->addAction(ui->actionLocalityAdd);
    ui->menuLocalities->addAction(ui->actionLocalityEdit);
    ui->menuLocalities->addAction(ui->actionLocalityDel);
    ui->menuLocalities->addAction(ui->actionRemoveLocalities);

    ui->menuDeliverers->addAction(ui->actionDelivererAdd);
    ui->menuDeliverers->addAction(ui->actionDelivererEdit);
    ui->menuDeliverers->addAction(ui->actionDelivererDel);
    ui->menuDeliverers->addAction(ui->actionRemoveDeliverers);

    ui->menuMilkPoints->addAction(ui->actionMilkPointAdd);
    ui->menuMilkPoints->addAction(ui->actionMilkPointEdit);
    ui->menuMilkPoints->addAction(ui->actionMilkPointDel);
    ui->menuMilkPoints->addAction(ui->actionRemoveMilkPoints);

    ui->menuHelp->addAction(ui->actionAbout);
    ui->menuHelp->addAction(ui->actionAboutQt);

    ui->menuUtils->addAction(ui->actionUpdatePrice);
}

void MainWindow::addActionsToToolBars()
{
    ui->toolBarDb->addAction(ui->actionCreateDb);
    ui->toolBarDb->addAction(ui->actionOpenDb);

    ui->toolBarLocalities->addAction(ui->actionLocalityAdd);
    ui->toolBarLocalities->addAction(ui->actionLocalityEdit);
    ui->toolBarLocalities->addAction(ui->actionLocalityDel);
    ui->toolBarLocalities->addWidget(m_groupBoxChooseMainLocality);

    ui->toolBarDeliverers->addAction(ui->actionDelivererAdd);
    ui->toolBarDeliverers->addAction(ui->actionDelivererEdit);
    ui->toolBarDeliverers->addAction(ui->actionDelivererDel);

    ui->toolBarMilkPoints->addAction(ui->actionMilkPointAdd);
    ui->toolBarMilkPoints->addAction(ui->actionMilkPointEdit);
    ui->toolBarMilkPoints->addAction(ui->actionMilkPointDel);
}

void MainWindow::createDb()
{
    QFileDialog dialog(this);
    dialog.setWindowTitle("Создание бд");
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setDirectory(QDir::currentPath());
    dialog.setDefaultSuffix(Constants::defaultMilkDbSuffix());
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter("Бд milk (*." + Constants::defaultMilkDbSuffix() +  ");; Любые файлы(*.*)");

    if (dialog.exec())
    {
        const QString fileName = dialog.selectedFiles().first();
        if(!fileName.isNull())
        {
            if (createDbFromTemplate(fileName)) {
                QMessageBox::information(this, Constants::appName(), fileName + tr(" успешно создана"));

                if (Utils::Main::yesNoWarnMsgBox(this, tr("Выбрать созданную бд в качестве текущей?")))
                    openDb(fileName);
            }
        }
    }
}

bool MainWindow::createDbFromTemplate(const QString &pathWithName)
{
    QFile templateBdfile(":/db/milk.mdb");

    if (!templateBdfile.exists())
    {
        QMessageBox::critical(this, Constants::appName(), tr("Отсутствует файл ") +
                              templateBdfile.fileName() + tr(" для копирования"));
        return false;
    }

    QFile newDbFile(pathWithName);
    if (newDbFile.exists())
        newDbFile.remove();
    if (templateBdfile.copy(pathWithName))
    {
        return QFile::setPermissions(pathWithName, QFile::ReadOwner | QFile::WriteOwner |
                                     QFile::ExeOwner | QFile::ReadGroup | QFile::ExeGroup |
                                     QFile::ReadOther | QFile::ExeOther);
    }

    return false;
}

void MainWindow::openDb(const QString &dbName)
{
    if (m_database->openDb(dbName))
    {
        setWindowTitle(QString("%1: %2 version %3")
                       .arg(Constants::appName())
                       .arg(m_database->choosenDatabase())
                       .arg(Constants::getCurrentVersion().toString()));

        m_comboBoxChooseMainLocality->setModel(m_database->localities());
        m_comboBoxChooseMainLocality->setModelColumn(LT_NAME);

        m_groupBoxChooseMainLocality->setChecked(false);

        for (auto table: m_database->tables()) {
            // show tables errors
            connect(table, &Table::error, this, [=](const QString &error) {
                QMessageBox::critical(this, table->tableName(), error);
            });
            // set fetch on refresh
            table->setIsFetchOnRefresh(m_settings->getMain().isFetchTablesOnRefresh);
        }
        connect(m_database->localities(), &Table::refreshed, this, [=]() {
            m_comboBoxChooseMainLocality->setCurrentIndex(0);
        });
        ui->frameMilkReceptionAdd->setup();
        ui->frameEditReceptionMilk->setup();
        ui->frameCalc->setup();
        m_groupBoxChooseMainLocality->setEnabled(!m_database->localities()->isEmpty());

        if (m_database->milkReception()->getIsFetchOnRefresh())
        {
            while (m_database->milkReception()->canFetchMore())
                m_database->milkReception()->fetchMore();
        }
    }
}

void MainWindow::removeDeliverer()
{
    if (!Utils::Main::showWarnMsgIfNoRows(this, tr("Отсутствуют сдатчики"),
                                          m_database->deliverers()))
    {
        const auto idDeliverer = Utils::Main::getIdFromDialog(m_database->deliverers(), tr("Удаление сдатчика"));
        if (Utils::Main::isAutoIncrIdIsValid(idDeliverer))
        {
            if (Utils::Main::yesNoWarnMsgBox(this, tr("Это также удалит все сдачи молока этого сдатчика."
                                                      "Продолжить?"))) {
                if (m_database->deliverers()->remove(idDeliverer))
                    m_database->deliverers()->refresh();
            }
        }
    }
}

void MainWindow::updateDeliverer()
{
    if (!Utils::Main::showWarnMsgIfNoRows(this, tr("Отсутствуют сдатчики"),
                                          m_database->deliverers()))
    {
        const auto idDeliverer = Utils::Main::getIdFromDialog(m_database->deliverers(), tr("Изменение сдатчика"));
        if (Utils::Main::isAutoIncrIdIsValid(idDeliverer)) {
            DelivererDialog dialog(m_database->deliverers(), idDeliverer);
            dialog.exec();
        }
    }
}

void MainWindow::removeLocality()
{
    if (!Utils::Main::showWarnMsgIfNoRows(this, tr("Отсутствуют населенные пункты"),
                                          m_database->localities()))
    {

        const auto idLocality = Utils::Main::getIdFromDialog(m_database->localities(), tr("Удаление населенного пункта"));
        if (Utils::Main::isAutoIncrIdIsValid(idLocality))
        {
            if (Utils::Main::yesNoWarnMsgBox(this, tr("Это также удалит все молокопункты населенного пункта, "
                                                      "сдачи молока в эти пункты,"
                                                      "а также сдатчиков, относящихся к этому населенному пункту."
                                                      "Продолжить?")))
            {
                if (m_database->localities()->remove(idLocality))
                {
                    m_database->localities()->refresh();
                    m_database->milkPoints()->refresh();
                    m_database->deliverers()->refresh();

                    m_groupBoxChooseMainLocality->setEnabled(!m_database->localities()->isEmpty());
                }
            }
        }
    }
}

void MainWindow::updateLocality()
{
    if (!Utils::Main::showWarnMsgIfNoRows(this, tr("Отсутствуют населенные пункты"),
                                          m_database->localities()))
    {
        const auto idLocality = Utils::Main::getIdFromDialog(m_database->localities(), tr("Изменение населенного пункта"));
        if (Utils::Main::isAutoIncrIdIsValid(idLocality)) {
            LocalityDialog dialog(m_database->localities(), idLocality);
            dialog.exec();
        }
    }
}

void MainWindow::removeMilkPoint()
{
    if (!Utils::Main::showWarnMsgIfNoRows(this, tr("Отсутствуют молокопункты"),
                                          m_database->milkPoints()))
    {
        const auto idMilkPoint = Utils::Main::getIdFromDialog(m_database->milkPoints(), tr("Удаление молокопункта"));
        if (Utils::Main::isAutoIncrIdIsValid(idMilkPoint)) {
            if (Utils::Main::yesNoWarnMsgBox(this, tr("Это также удалит все сдачи молока, "
                                                      "относящиеся к этому молокопункту. Продолжить?")))
            {
                if (m_database->milkPoints()->remove(idMilkPoint))
                    m_database->milkPoints()->refresh();
            }
        }
    }
}

void MainWindow::updateMilkPoint()
{
    if (!Utils::Main::showWarnMsgIfNoRows(this, tr("Отсутствуют молокопункты"),
                                          m_database->milkPoints()))
    {
        const auto idMilkPoint = Utils::Main::getIdFromDialog(m_database->milkPoints(), tr("Изменение молокопункта"));
        if (Utils::Main::isAutoIncrIdIsValid(idMilkPoint)) {
            MilkPointDialog dialog(m_database->milkPoints(), idMilkPoint);
            dialog.exec();
        }
    }
}

void MainWindow::showUpdatePriceDialog() const
{
    UpdatePriceDialog dialog(m_database->milkReception());
    dialog.exec();
}

void MainWindow::showSettings()
{
    if (getDialogSettings()->exec() == QDialog::Accepted)
    {
        for (auto table: m_database->tables()) {
            const auto isFetchOnRefresh = m_settings->getMain().isFetchTablesOnRefresh;
            // set fetch on refresh
            table->setIsFetchOnRefresh(isFetchOnRefresh);
            if (isFetchOnRefresh)
            {
                while (table->canFetchMore())
                    table->fetchMore();
            }
        }
    }
}

void MainWindow::chooseMainLocality()
{    
    if (!m_database->isTablesCreated())
        return;

    auto deliverers = m_database->deliverers();
    auto milkPoints = m_database->milkPoints();
    auto milkReception = m_database->milkReception();

    const auto idLocality = getCurrentLocalityId();
    if (Utils::Main::isAutoIncrIdIsValid(idLocality))
    {
        deliverers->setQuery(QString("%1 WHERE %2 = %3")
                             .arg(deliverers->selectAll())
                             .arg(deliverers->getColName(DT_LOCALITY_ID))
                             .arg(idLocality));
        milkPoints->setQuery(QString("%1 WHERE %2 = %3")
                             .arg(milkPoints->selectAll())
                             .arg(milkPoints->getColName(MPT_LOCALITY_ID))
                             .arg(idLocality));

        milkReception->setQuery(QString("%1 WHERE %2 IN(SELECT %3 FROM %4 WHERE %5 = %6)")
                                .arg(milkReception->selectAll())
                                .arg(milkReception->getColName(RMT_MILK_POINT_ID))
                                .arg(milkPoints->getColName(MPT_ID))
                                .arg(milkPoints->tableName())
                                .arg(milkPoints->getColName(MPT_LOCALITY_ID))
                                .arg(idLocality));
    } else
    {
        deliverers->setQuery(deliverers->selectAll());
        milkPoints->setQuery(milkPoints->selectAll());
        milkReception->setQuery(milkReception->selectAll());
    }

    ui->frameMilkReceptionAdd->setup();
    ui->frameEditReceptionMilk->setup();
    ui->frameCalc->setup();
}

Settings *MainWindow::getSettings() const
{
    return m_settings;
}

QString MainWindow::getCurrentLocalityName() const
{
    const auto localities = m_database->localities();

    if (localities->isEmpty())
        return QString();

    if (localities->rowCount() == 1)
        return m_comboBoxChooseMainLocality->itemText(0);

    if (!m_groupBoxChooseMainLocality->isChecked())
        return QString();

    return m_comboBoxChooseMainLocality->currentText();
}

qlonglong MainWindow::getCurrentLocalityId() const
{
    if (!m_groupBoxChooseMainLocality->isChecked())
        return -1;

    return Utils::Main::getCurValueFromComboBoxModel(m_comboBoxChooseMainLocality, LT_ID).toLongLong();
}

void MainWindow::_writeSettings()
{
    m_settings->setMain().priceLiter = ui->frameMilkReceptionAdd->price();
    m_settings->getMain().lastChoosenDb = m_database->choosenDatabase();

    m_settings->writeMainSettings();
}

DialogSettings *MainWindow::getDialogSettings()
{
    if (!m_dialogSettings)
        m_dialogSettings = new DialogSettings(this);

    return m_dialogSettings;
}

Database *MainWindow::database() const
{
    return m_database;
}
