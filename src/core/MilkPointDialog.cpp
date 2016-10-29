#include "MilkPointDialog.h"
#include "ui_MilkPointDialog.h"

#include "tables/localities/LocalitiesTable.h"
#include "Utils.h"
// qt
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

USE_DB_NAMESPACE


MilkPointDialog::MilkPointDialog(MilkPointsTable *milkPoints, const milk_id milkPointId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MilkPointDialog),
    m_milkPointsTable(milkPoints),
    m_currentId(milkPointId)
{
    ui->setupUi(this);

    loadLocalities();

    if (!isNeedInsert())
        loadToUi(m_milkPointsTable->getMilkPoint(m_currentId));
}

MilkPointDialog::~MilkPointDialog()
{
    delete ui;
}

void MilkPointDialog::accept()
{
    if (getName().isEmpty())
    {
        QMessageBox::information(this, tr("Добавить молочный пункт"),
                                 tr("Наименование обязательно для заполнения"));
        return;
    }

    QSqlQuery query;
    query.prepare(getDublNameQueryPrepStr());
    query.addBindValue(getName());
    if (!isNeedInsert())
        query.addBindValue(m_currentId);

    bool isOk = true;

    if (!query.exec()) {
        isOk = Utils::Main::yesNoWarnMsgBox(this, tr("Ошибка при проверке существующих наименований в бд: ") +
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
            isOk = Utils::Main::yesNoWarnMsgBox(this, tr("Молокопункт(ы) с данным именем существует: \n") + dublicates +
                                                tr("Все равно желаете %1 запись?").arg(isNeedInsert() ? "внести" : "обновить"));
    }
    if (isOk) {
        if (isNeedInsert())
            isOk = insertMilkPoint();
        else
            isOk = updateMilkPoint();

        if (isOk)
            QDialog::accept();
    }
}

QString MilkPointDialog::getName() const
{
    return ui->lineEditName->text().trimmed();
}

QString MilkPointDialog::getDescription() const
{
    return ui->textEditDescription->toPlainText().trimmed();
}

milk_id MilkPointDialog::getLocalityId() const
{
    const auto locIdColPos = m_milkPointsTable->getLocalities()->getColumnPosition(
                m_milkPointsTable->getLocalities()->getNameColumnId(false));

    return Utils::Main::getCurValueFromComboBoxModel(ui->comboBoxLocalities,
                                                     locIdColPos).toLongLong();
}

void MilkPointDialog::setComboBoxCurIndex(const int position)
{
    ui->comboBoxLocalities->setCurrentIndex(position);
}

bool MilkPointDialog::isNeedInsert() const
{
    return m_currentId < 0;
}

void MilkPointDialog::loadLocalities()
{
    const auto locNameColPos = m_milkPointsTable->getLocalities()->getColumnPosition(
                m_milkPointsTable->getLocalities()->getNameColumnName(false));

    LocalitiesTable *localities = m_milkPointsTable->getLocalities();
    ui->comboBoxLocalities->setModel(localities);
    ui->comboBoxLocalities->setModelColumn(locNameColPos);

    QObject::connect(ui->toolButtonRefresh, &QToolButton::clicked, [=](){
        localities->refresh();
        ui->comboBoxLocalities->setCurrentIndex(0);
    });
}

void MilkPointDialog::loadToUi(const db::MilkPointData &milkPoint)
{
    const auto locIdColPos = m_milkPointsTable->getLocalities()->getColumnPosition(
                m_milkPointsTable->getLocalities()->getNameColumnId(false));

    const auto &index = Utils::Main::getIndexFromModelById(m_milkPointsTable->getLocalities(),
                                                             locIdColPos, milkPoint.localityId());
    ui->lineEditName->setText(milkPoint.name());
    ui->textEditDescription->setText(milkPoint.description());

    if (index.isValid())
        ui->comboBoxLocalities->setCurrentIndex(index.row());
    else
        QMessageBox::critical(this, tr("Молокопункт"), tr("Не удалось установить текущий "
                                                          "населенный пункт у молокопункта \"") +
                                                          milkPoint.name() + "\"");
}

db::MilkPointData MilkPointDialog::getFromUi() const
{
    return MilkPointData(m_currentId, getLocalityId(), getName(), getDescription());
}

bool MilkPointDialog::insertMilkPoint()
{
    if (m_milkPointsTable->insert(getFromUi())) {
        m_milkPointsTable->refresh();
        return true;
    }

    return false;
}

bool MilkPointDialog::updateMilkPoint()
{
    if (m_milkPointsTable->update(getFromUi())) {
        m_currentId = -1;
        m_milkPointsTable->refresh();
        return true;
    }

    return false;
}

QString MilkPointDialog::getDublNameQueryPrepStr() const
{
    const auto select = Utils::Main::getSelectStr(m_milkPointsTable->tableName(),
                    QStringList() << m_milkPointsTable->getLocalities()->getNameColumnName(true));
    auto query = QString("%1 LEFT JOIN %2 ON %4 = %5 WHERE %6 = ?")
            .arg(select)
            .arg(m_milkPointsTable->getLocalities()->tableName())
            .arg(m_milkPointsTable->getNameColumnLocalityId(true))
            .arg(m_milkPointsTable->getLocalities()->getNameColumnId(true))
            .arg(m_milkPointsTable->getNameColumnName(true));

    if (!isNeedInsert())
        query.append(" AND " + m_milkPointsTable->getNameColumnId(true) + " != ?");

    return query;
}

void MilkPointDialog::clear()
{
    ui->lineEditName->clear();
    ui->textEditDescription->clear();
}
