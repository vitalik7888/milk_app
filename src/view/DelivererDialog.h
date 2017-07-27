#ifndef DELIVERERADDDIALOG_H
#define DELIVERERADDDIALOG_H

#include "tables/deliverers/DeliverersTable.h"
// Qt
#include <QDialog>

namespace Ui {
class DelivererDialog;
}


class DelivererDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DelivererDialog(DB_NAMESPACE::DeliverersTable *deliverers,
                             const milk_id delivererId = -1, QWidget *parent = Q_NULLPTR);
    ~DelivererDialog();

    void accept() override;

    QString getName() const;
    milk_id getLocalityId() const;
    milk_inn getInn() const;
    QString getAddress() const;
    QString getPhoneNumber() const;

    void setComboBoxCurIndex(const int position);

private:
    Ui::DelivererDialog *ui;

    DB_NAMESPACE::DeliverersTable *m_deliverers;
    milk_id m_currentId;

    bool isNeedInsert() const;
    void loadDelivererToUi(const DB_NAMESPACE::DelivererData &deliverer);
    DB_NAMESPACE::DelivererData getDelivererFromUi() const;

    void loadLocalities();

    bool insertDeliverer();
    bool updateDeliverer();

    QString getDublNameQueryPrepStr() const;
    void clear();
};

#endif // DELIVERERADDDIALOG_H
