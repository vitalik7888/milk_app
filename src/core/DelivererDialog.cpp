#include "DelivererDialog.h"
#include "ui_DelivererDialog.h"

#include "tables/localities/LocalitiesTable.h"
#include "Utils.h"
// qt
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>


DelivererDialog::DelivererDialog(DeliverersTable *deliverers, const qlonglong delivererId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DelivererDialog),
    m_deliverers(deliverers),
    m_currentId(delivererId)
{
    ui->setupUi(this);

    loadLocalities();

    if (!isNeedInsert())
        loadDelivererToUi(m_deliverers->getDeliverer(m_currentId));
}

DelivererDialog::~DelivererDialog()
{
    delete ui;
}

void DelivererDialog::loadLocalities()
{
    const auto locNameColPos = m_deliverers->getLocalities()->getColumnPosition(
                m_deliverers->getLocalities()->getNameColumnName());

    LocalitiesTable *localities = m_deliverers->getLocalities();
    ui->comboBoxLocality->setModel(localities);
    ui->comboBoxLocality->setModelColumn(locNameColPos);

    QObject::connect(ui->toolButtonRefresh, &QToolButton::clicked, [=](){
        localities->refresh();
        ui->comboBoxLocality->setCurrentIndex(0);
    });
}

void DelivererDialog::accept()
{
    if (getName().isEmpty())
    {
        QMessageBox::information(this, tr("Добавить сдатчика"),
                                 tr("Фио сдатчика обязательно для заполнения"));
        return;
    }

    QSqlQuery query;
    query.prepare(getDublNameQueryPrepStr());
    query.addBindValue(getName());
    if (!isNeedInsert())
        query.addBindValue(m_currentId);

    bool isOk = true;

    if (!query.exec()) {
        isOk = Utils::Main::yesNoWarnMsgBox(this, tr("Ошибка при проверке существующих имен в бд: ") +
                                            query.lastError().text() + ".\n" +
                                            tr("Все равно желаете продолжить?"));
    } else {
        QString dublicates = QString();
        while (query.next()) {
            dublicates.append("\t");
            dublicates.append(tr("в населенном пункте ") + query.value(0).toString());
            dublicates.append("\n");
        }

        if (!dublicates.isEmpty())
            isOk = Utils::Main::yesNoWarnMsgBox(this, tr("Сдатчик(и) с данным именем существует: \n") + dublicates +
                                                tr("Все равно желаете %1 запись?").arg(isNeedInsert() ? "внести" : "обновить"));
    }
    if (isOk) {
        if (isNeedInsert())
            isOk = insertDeliverer();
        else
            isOk = updateDeliverer();

        if (isOk)
            QDialog::accept();
    }
}

QString DelivererDialog::getName() const
{
    return ui->lineEditName->text().trimmed();
}

qlonglong DelivererDialog::getLocalityId() const
{
    const auto locIdColPos = m_deliverers->getLocalities()->getColumnPosition(
                m_deliverers->getLocalities()->getNameColumnId());

    return Utils::Main::getCurValueFromComboBoxModel(ui->comboBoxLocality, locIdColPos).toLongLong();
}

qlonglong DelivererDialog::getInn() const
{
    return ui->lineEditInn->text().toLongLong();
}

QString DelivererDialog::getAddress() const
{
    return ui->textEditAddress->toPlainText();
}

QString DelivererDialog::getPhoneNumber() const
{
    const auto phoneNumber = ui->lineEditPhoneNumber->text(),
            inputMask = ui->lineEditPhoneNumber->inputMask();
    if (inputMask == phoneNumber)
        return "";

    return phoneNumber;
}

bool DelivererDialog::isNeedInsert() const
{
    return m_currentId < 0;
}

void DelivererDialog::loadDelivererToUi(const Deliverer &deliverer)
{
    const auto locIdColPos = m_deliverers->getLocalities()->getColumnPosition(
                m_deliverers->getLocalities()->getNameColumnId());
    const auto &index = Utils::Main::getIndexFromModelById(m_deliverers->getLocalities(),
                                                           locIdColPos, deliverer.locality().id());
    if (index.isValid())
        ui->comboBoxLocality->setCurrentIndex(index.row());
    else
        QMessageBox::critical(this, tr("Молокопункт"),
                              tr("Не удалось установить текущий населенный пункт у сдатчика ") +
                              deliverer.name() + "\"");
    ui->lineEditName->setText(deliverer.name());
    ui->lineEditInn->setText(QString::number(deliverer.inn()));
    ui->textEditAddress->setText(deliverer.address());
    ui->lineEditPhoneNumber->setText(deliverer.phoneNumber());
}

Deliverer DelivererDialog::getDelivererFromUi() const
{
    return Deliverer(getName(), m_deliverers->getLocalities()->getLocality(getLocalityId()),
                     getInn(), getAddress(), getPhoneNumber(), m_currentId);
}

bool DelivererDialog::insertDeliverer()
{
    if (m_deliverers->insert(getDelivererFromUi())) {
        m_deliverers->refresh();
        return true;
    }
    return false;
}

bool DelivererDialog::updateDeliverer()
{
    if (m_deliverers->update(getDelivererFromUi())) {
        m_currentId = -1;
        m_deliverers->refresh();
        return true;
    }

    return false;
}

QString DelivererDialog::getDublNameQueryPrepStr() const
{
    const auto select = Utils::Main::getSelectStr(m_deliverers->tableName(),
                    QStringList() << m_deliverers->getLocalities()->getNameColumnName(true));
    auto query = QString("%1 LEFT JOIN %2 ON %4 = %5 WHERE %6 = ?")
            .arg(select)
            .arg(m_deliverers->getLocalities()->tableName())
            .arg(m_deliverers->getNameColumnLocalityId(true))
            .arg(m_deliverers->getLocalities()->getNameColumnId(true))
            .arg(m_deliverers->getNameColumnName(true));

    if (!isNeedInsert())
        query.append(" AND " + m_deliverers->getNameColumnId(true) + " != ?");

    return query;
}

void DelivererDialog::clear()
{
    ui->lineEditName->clear();
    ui->lineEditInn->clear();
    ui->textEditAddress->clear();
    ui->lineEditPhoneNumber->setText(ui->lineEditPhoneNumber->inputMask());
}
