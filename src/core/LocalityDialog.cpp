#include "LocalityDialog.h"
#include "ui_LocalityDialog.h"

#include "Utils.h"
// Qt
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

USE_DB_NAMESPACE


LocalityDialog::LocalityDialog(LocalitiesTable *localities, const milk_id localityId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LocalityDialog),
    m_localities(localities),
    m_currentId(localityId)
{
    ui->setupUi(this);

    if (!isNeedInsert())
        loadToUi(m_localities->getLocality(m_currentId));
}

LocalityDialog::~LocalityDialog()
{
    delete ui;
}

QString LocalityDialog::getName() const
{
    return ui->lineEditName->text().trimmed();
}

QString LocalityDialog::getDescription() const
{
    return ui->textEditDescription->toPlainText().trimmed();
}

bool LocalityDialog::isNeedInsert() const
{
    return m_currentId < 0;
}

void LocalityDialog::loadToUi(const Locality &locality)
{
    ui->lineEditName->setText(locality.name());
    ui->textEditDescription->setText(locality.description());
}

Locality LocalityDialog::getLocalityFromUi() const
{
    return Locality(m_currentId, getName(), getDescription());
}

bool LocalityDialog::insertLocality()
{
    if (m_localities->insert(getLocalityFromUi())) {
        m_localities->refresh();
        return true;
    }

    return false;
}

bool LocalityDialog::updateLocality()
{
    if (m_localities->update(getLocalityFromUi())) {
        m_currentId = -1;
        m_localities->refresh();
        return true;
    }

    return false;
}

QString LocalityDialog::getDublNameQueryPrepStr() const
{
    auto query = QString("%1 WHERE %2 = ?")
                      .arg(Utils::Main::getSelectStr(m_localities->tableName(),
                           QStringList() << m_localities->getNameColumnName(true)))
                      .arg(m_localities->getNameColumnName(true));
    if (!isNeedInsert())
        query.append(" AND " + m_localities->getFieldId().name() + " != ?");
    return query;
}

void LocalityDialog::accept()
{
    if (getName().isEmpty()) {
        QMessageBox::information(this, tr("Добавить населенный пункт"),
                                 tr("Уникальное название обязательно для заполнения"));
        return;
    }

    QSqlQuery query;
    query.prepare(getDublNameQueryPrepStr());
    query.addBindValue(getName());
    if (!isNeedInsert())
        query.addBindValue(m_currentId);

    bool isOk = true;

    if (!query.exec()) {
        isOk = Utils::Main::yesNoWarnMsgBox(this, tr("Ошибка при проверке существующих названий в бд: ") +
                                             query.lastError().text() + ".\n" +
                                            tr("Все равно желаете продолжить?"));
    } else {
        int count = 0;
        while (query.next())
            count++;

        if (count > 0)
            isOk = Utils::Main::yesNoWarnMsgBox(this, tr("Населенный пункт \"%1\" встречается %2 раз(а). ")
                                                .arg(getName()).arg(count) +
                                                tr("Все равно желаете %1 запись?").arg(isNeedInsert() ? "внести" : "обновить"));
    }
    if (isOk) {
        if (isNeedInsert())
            isOk = insertLocality();
        else
            isOk = updateLocality();

        if (isOk)
            QDialog::accept();
    }
}

void LocalityDialog::clear() {
    ui->lineEditName->clear();
    ui->textEditDescription->clear();
}
