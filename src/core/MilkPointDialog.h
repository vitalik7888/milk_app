#ifndef MILKPOINTADDDIALOG_H
#define MILKPOINTADDDIALOG_H

#include <QDialog>

#include "tables/milk_points/MilkPointsTable.h"

namespace Ui {
class MilkPointDialog;
}


class MilkPointDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MilkPointDialog(MilkPointsTable *milkPoints, const qlonglong milkPointId = -1, QWidget *parent = 0);
    ~MilkPointDialog();

    void accept() Q_DECL_OVERRIDE;

    QString getName() const;
    QString getDescription() const;
    qlonglong getLocalityId() const;

    void setComboBoxCurIndex(const int position);

private:
    Ui::MilkPointDialog *ui;

    MilkPointsTable *m_milkPointsTable;
    qlonglong m_currentId;

    bool isNeedInsert() const;
    void loadLocalities();
    void loadToUi(const MilkPoint &milkPoint);
    MilkPoint getFromUi() const;
    bool insertMilkPoint();
    bool updateMilkPoint();

    QString getDublNameQueryPrepStr() const;
    void clear();
};

#endif // MILKPOINTADDDIALOG_H
