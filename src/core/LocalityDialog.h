#ifndef LOCALITYADDDIALOG_H
#define LOCALITYADDDIALOG_H

#include <QDialog>

#include "tables/localities/LocalitiesTable.h"

namespace Ui {
class LocalityDialog;
}


class LocalityDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LocalityDialog(LocalitiesTable *localities, const qlonglong localityId = -1, QWidget *parent = 0);
    ~LocalityDialog();

    void accept() Q_DECL_OVERRIDE;

    QString getName() const;
    QString getDescription() const;

private:
    Ui::LocalityDialog *ui;

    LocalitiesTable *m_localities;
    qlonglong m_currentId;

    bool isNeedInsert() const;
    void loadToUi(const Locality &locality);
    Locality getLocalityFromUi() const;
    bool insertLocality();
    bool updateLocality();

    QString getDublNameQueryPrepStr() const;
    void clear();
};

#endif // LOCALITYADDDIALOG_H
