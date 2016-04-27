#ifndef UPDATEPRICEDIALOG_H
#define UPDATEPRICEDIALOG_H

#include <QDialog>

class MilkReceptionTable;

namespace Ui {
class UpdatePriceDialog;
}

class UpdatePriceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdatePriceDialog(MilkReceptionTable *mrTable, QWidget *parent = 0);
    ~UpdatePriceDialog();

private:
    Ui::UpdatePriceDialog *ui;

    MilkReceptionTable *m_mrTable;

    double getPrice() const;
    QDate getDateFrom() const;
    QDate getDateTo() const;

public slots:
    void accept() Q_DECL_OVERRIDE;
};

#endif // UPDATEPRICEDIALOG_H
