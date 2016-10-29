#ifndef LOCALITYADDDIALOG_H
#define LOCALITYADDDIALOG_H

#include "tables/localities/LocalitiesTable.h"
// Qt
#include <QDialog>

namespace Ui {
class LocalityDialog;
}


class LocalityDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LocalityDialog(DB_NAMESPACE::LocalitiesTable *localities, const milk_id localityId = -1,
                            QWidget *parent = Q_NULLPTR);
    ~LocalityDialog();

    void accept() Q_DECL_OVERRIDE;

    QString getName() const;
    QString getDescription() const;

private:
    Ui::LocalityDialog *ui;

    DB_NAMESPACE::LocalitiesTable *m_localities;
    milk_id m_currentId;

    bool isNeedInsert() const;
    void loadToUi(const DB_NAMESPACE::Locality &locality);
    DB_NAMESPACE::Locality getLocalityFromUi() const;
    bool insertLocality();
    bool updateLocality();

    QString getDublNameQueryPrepStr() const;
    void clear();
};

#endif // LOCALITYADDDIALOG_H
