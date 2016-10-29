#include "DialogGetItem.h"
#include "ui_DialogGetId.h"

#include "Utils.h"
#include "tables/deliverers/DeliverersTable.h"
#include "tables/localities/LocalitiesTable.h"
#include "tables/milk_points/MilkPointsTable.h"
// Qt
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QMessageBox>
#include <QSortFilterProxyModel>
#include <QDebug>

USE_DB_NAMESPACE


DialogGeItem::DialogGeItem(Table *table, const QString &title, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGetId),
    m_proxyModel(new QSortFilterProxyModel),
    m_localities(qobject_cast<LocalitiesTable *>(table)),
    m_deliverers(qobject_cast<DeliverersTable *>(table)),
    m_milkPoints(qobject_cast<MilkPointsTable *>(table)),
    m_isItemChoosed(false)
{
    ui->setupUi(this);

    m_proxyModel->setParent(this);
    m_proxyModel->setSourceModel(table);
    m_proxyModel->setDynamicSortFilter(true);
    /*auto helpSearchWidget = new QHelpSearchQueryWidget();
    auto gridLayout = qobject_cast<QGridLayout *>(layout());
    gridLayout->addWidget(helpSearchWidget, 0, 0);*/

    ui->comboBox->setModel(m_proxyModel);

    auto showColumn = -1;
    if (m_deliverers) {
        //        setWindowIcon();
        if (title.isEmpty())
            setWindowTitle(tr("Сдатчики"));
        showColumn = m_deliverers->getColumnPosition(m_deliverers->getNameColumnName());
        ui->toolButtonInfo->setToolTip(tr("Информация о сдатчике"));
    } else if (m_localities) {
        if (title.isEmpty())
            setWindowTitle(tr("Населенные пункты"));
        showColumn = m_localities->getColumnPosition(m_localities->getNameColumnName());
        ui->toolButtonInfo->setToolTip(tr("Информация о населенном пункте"));
    } else if (m_milkPoints) {
        if (title.isEmpty())
            setWindowTitle(tr("Молокопункты"));
        showColumn = m_milkPoints->getColumnPosition(m_milkPoints->getNameColumnName());
        ui->toolButtonInfo->setToolTip(tr("Информация о молокопункте"));
    }

    m_proxyModel->setFilterKeyColumn(showColumn);
    ui->comboBox->setModelColumn(showColumn);

    connect(ui->toolButtonRefresh, &QToolButton::clicked, this, &DialogGeItem::refresh);
    connect(ui->toolButtonInfo, &QToolButton::clicked, this, &DialogGeItem::showInfo);
    connect(ui->lineEditSearch, &QLineEdit::textChanged, m_proxyModel, &QSortFilterProxyModel::setFilterFixedString);
    connect(ui->checkBoxCaseSensitivity, &QCheckBox::toggled, this, &DialogGeItem::searchEnableCaseSensitivity);
}

DialogGeItem::~DialogGeItem()
{
    delete ui;
}

qlonglong DialogGeItem::getId() const
{
    const auto idColumn = getTable()->getColumnPosition(getTable()->primaryField().name());

    const auto index = getIdModelIndex();
    const auto record = getTable()->record(index.row());
    const auto field = record.field(idColumn);

    if (field.value().isValid())
        return field.value().toLongLong();

    return -1;
}

void DialogGeItem::showInfo()
{
    QString title, text;

    const auto id = getId();
    const auto isIdValid = Utils::Main::isAutoIncrIdIsValid(id);

    if (isIdValid) {
        if (m_deliverers) {
            title = tr("Информация о сдатчике");
            const auto data = m_deliverers->getDeliverer(id);
            text = QString("Сдатчик %1: inn = %2, address = %3, phoneNumber = %4.")
                    .arg(data.name()).arg(data.inn()).arg(data.address()).arg(data.phoneNumber());
        } else if (m_localities) {
            title = tr("Информация о населенном пункте");
            const auto locality = m_localities->getLocality(id);
            text = QString::fromUtf8("%1: описание = %2.").
                    arg(locality.name()).arg(locality.description());
        } else if (m_milkPoints) {
            title = tr("Информация о молокопункте");
            const auto mp = m_milkPoints->getMilkPoint(id);
            text = QString::fromUtf8("Молочный пункт %1: описание = %2").arg(mp.name()).arg(mp.description());
        }

        QMessageBox::information(this, title, text);
    } else {
        QMessageBox::warning(this, tr(""), tr("Выбор пуст. Невозможно отобразить информацию"));
    }
}

bool DialogGeItem::getIsItemChoosed() const
{
    return m_isItemChoosed;
}

void DialogGeItem::searchEnableCaseSensitivity(const bool isEnabled)
{
    if (isEnabled)
        m_proxyModel->setFilterCaseSensitivity(Qt::CaseSensitive);
    else
        m_proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
}

Table *DialogGeItem::getTable() const
{
    if (m_localities)
        return m_localities;
    if (m_deliverers)
        return m_deliverers;
    if (m_milkPoints)
        return m_milkPoints;

    return nullptr;
}

QModelIndex DialogGeItem::getIdModelIndex() const
{
    const auto idColumn = getTable()->getColumnPosition(getTable()->primaryField().name());
    const auto proxyIndex = m_proxyModel->index(ui->comboBox->currentIndex(), idColumn);

    return m_proxyModel->mapToSource(proxyIndex);
}

void DialogGeItem::setCurrentItemById(const qlonglong _id)
{
    const auto column = getTable()->getColumnPosition(getTable()->primaryField().name());
    const auto &index = Utils::Main::getIndexFromModelById(getTable(), column,  _id);

    if (index.isValid())
        ui->comboBox->setCurrentIndex(m_proxyModel->mapFromSource(index).row());
    else
        QMessageBox::warning(this, Constants::appName(), tr("Не удалось установить значение с id = ") + QString::number(_id));
}

void DialogGeItem::setCurrentItem(const QModelIndex &index)
{
    if (index.isValid()) {
        ui->comboBox->setCurrentIndex(m_proxyModel->mapFromSource(index).row());
    }
}

QString DialogGeItem::value() const
{
    const auto index = getIdModelIndex();
    const auto record = getTable()->record(index.row());
    const auto field = record.field(ui->comboBox->modelColumn());

    if (field.value().isValid())
        return field.value().toString();

    return QString();
}

void DialogGeItem::refresh()
{
    getTable()->refresh();
    ui->comboBox->setCurrentIndex(0);
}

void DialogGeItem::accept()
{
    m_isItemChoosed = true;
    QDialog::accept();
}

void DialogGeItem::reject()
{
    m_isItemChoosed = false;
    QDialog::reject();
}
