#include "UpdatePriceDialog.h"
#include "ui_UpdatePriceDialog.h"

#include "tables/milk_reception/MilkReceptionTable.h"
#include "ViewUtils.h"
// Qt
#include <QSqlQuery>
#include <QMessageBox>

USE_DB_NAMESPACE


UpdatePriceDialog::UpdatePriceDialog(MilkReceptionTable *mrTable, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdatePriceDialog),
    m_mrTable(mrTable)
{
    ui->setupUi(this);

    ui->dateEditFrom->setDate(QDate::currentDate());
    ui->dateEditTo->setDate(ui->dateEditFrom->date());
    ui->doubleSpinBoxNewPrice->setValue(.0);
}

UpdatePriceDialog::~UpdatePriceDialog()
{
    delete ui;
}

double UpdatePriceDialog::getPrice() const
{
    return ui->doubleSpinBoxNewPrice->value();
}

QDate UpdatePriceDialog::getDateFrom() const
{
    return ui->dateEditFrom->date();
}

QDate UpdatePriceDialog::getDateTo() const
{
    return ui->dateEditTo->date();
}

void UpdatePriceDialog::accept()
{
    if (getPrice() <= .0)
    {
        QMessageBox::information(this, tr("Цена"),
                                 tr("Цена должна быть указана больше нуля"));
        return;
    }

    if (ViewUtils::yesNoWarnMsgBox(this, QString("Вы уверены?")))
    {
        auto isOk = m_mrTable->updatePriceLiters(getPrice(), getDateFrom(), getDateTo());

        if (isOk) {
            QDialog::accept();
            m_mrTable->refresh();
        }
    }
}
