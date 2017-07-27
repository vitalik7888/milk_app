#include "LocalityDialog.h"
#include "ui_LocalityDialog.h"

#include "ViewUtils.h"
#include "src/core/Utils.h"
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

    if (!isNeedInsert()) {
        try {
            loadToUi(m_localities->getLocality(m_currentId));
        } catch (const QString &errDescr) {
            QMessageBox::warning(this, "", tr("Ошибка получения данных о населенном пункте: ") + errDescr);
        }
    }
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

void LocalityDialog::loadToUi(const LocalityData &locality)
{
    ui->lineEditName->setText(locality.name());
    ui->textEditDescription->setText(locality.description());
}

LocalityData LocalityDialog::getLocalityFromUi() const
{
    return LocalityData(m_currentId, getName(), getDescription());
}

bool LocalityDialog::insertLocality()
{
    try {
        m_localities->insert(getLocalityFromUi());
        m_localities->refresh();
    } catch (const QString &errorDescr) {
        QMessageBox::warning(this, tr("Населенный пункт"), tr("Ошибка внесения данных: ") + errorDescr);
        return false;
    }

    return true;
}

bool LocalityDialog::updateLocality()
{
    try {
        m_localities->update(getLocalityFromUi());
        m_currentId = -1;
        m_localities->refresh();
    } catch (const QString &errorDescr) {
        QMessageBox::warning(this, tr("Населенный пункт"), tr("Ошибка обновления данных: ") + errorDescr);
        return false;
    }

    return true;
}

QString LocalityDialog::getDublNameQueryPrepStr() const
{
    auto query = QString("%1 WHERE %2 = ?").arg(Utils::Main::getSelectStr(m_localities->tableName(),
                                                { m_localities->getColName(LT_NAME, true) }))
            .arg(m_localities->getColName(LT_NAME, true));
    if (!isNeedInsert())
        query.append(" AND " + m_localities->getColName(LT_ID) + " != ?");
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
        isOk = ViewUtils::yesNoWarnMsgBox(this, tr("Ошибка при проверке существующих названий в бд: ") +
                                            query.lastError().text() + ".\n" +
                                            tr("Все равно желаете продолжить?"));
    } else {
        int count = 0;
        while (query.next())
            count++;

        if (count > 0)
            isOk = ViewUtils::yesNoWarnMsgBox(this, tr("Населенный пункт \"%1\" встречается %2 раз(а). ")
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
