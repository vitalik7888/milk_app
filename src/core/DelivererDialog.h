#ifndef DELIVERERADDDIALOG_H
#define DELIVERERADDDIALOG_H

#include <QDialog>

#include "tables/deliverers/DeliverersTable.h"

namespace Ui {
class DelivererDialog;
}


class DelivererDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DelivererDialog(DeliverersTable *deliverers, const qlonglong delivererId = -1, QWidget *parent = 0);
    ~DelivererDialog();

    void accept() override;

    QString getName() const;
    qlonglong getLocalityId() const;
    qlonglong getInn() const;
    QString getAddress() const;
    QString getPhoneNumber() const;

private:
    Ui::DelivererDialog *ui;

    DeliverersTable *m_deliverers;
    qlonglong m_currentId;

    bool isNeedInsert() const;
    void loadDelivererToUi(const Deliverer &deliverer);
    Deliverer getDelivererFromUi() const;

    void loadLocalities();

    bool insertDeliverer();
    bool updateDeliverer();

    QString getDublNameQueryPrepStr() const;
    void clear();
};

#endif // DELIVERERADDDIALOG_H
