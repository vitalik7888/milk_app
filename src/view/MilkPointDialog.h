#ifndef MILKPOINTADDDIALOG_H
#define MILKPOINTADDDIALOG_H

#include "tables/milk_points/MilkPointsTable.h"
// Qt
#include <QDialog>

namespace Ui {
class MilkPointDialog;
}


class MilkPointDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MilkPointDialog(DB_NAMESPACE::MilkPointsTable *milkPoints,
                             const milk_id milkPointId = -1, QWidget *parent = Q_NULLPTR);
    ~MilkPointDialog();

    void accept() Q_DECL_OVERRIDE;

    QString getName() const;
    QString getDescription() const;
    milk_id getLocalityId() const;

    void setComboBoxCurIndex(const int position);

private:
    Ui::MilkPointDialog *ui;

    DB_NAMESPACE::MilkPointsTable *m_milkPointsTable;
    milk_id m_currentId;

    bool isNeedInsert() const;
    void loadLocalities();
    void loadToUi(const DB_NAMESPACE::MilkPointData &milkPoint);
    DB_NAMESPACE::MilkPointData getFromUi() const;
    bool insertMilkPoint();
    bool updateMilkPoint();

    QString getDublNameQueryPrepStr() const;
    void clear();
};

#endif // MILKPOINTADDDIALOG_H
