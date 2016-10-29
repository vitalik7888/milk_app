#ifndef UPDATEPRICEDIALOG_H
#define UPDATEPRICEDIALOG_H

#include "dbconstants.h"
// Qt
#include <QDialog>
DB_BEGIN_NAMESPACE
    class MilkReceptionTable;
DB_END_NAMESPACE

namespace Ui {
class UpdatePriceDialog;
}

class UpdatePriceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdatePriceDialog(DB_NAMESPACE::MilkReceptionTable *mrTable, QWidget *parent = 0);
    ~UpdatePriceDialog();

private:
    Ui::UpdatePriceDialog *ui;

    DB_NAMESPACE::MilkReceptionTable *m_mrTable;

    double getPrice() const;
    QDate getDateFrom() const;
    QDate getDateTo() const;

public slots:
    void accept() Q_DECL_OVERRIDE;
};

#endif // UPDATEPRICEDIALOG_H
