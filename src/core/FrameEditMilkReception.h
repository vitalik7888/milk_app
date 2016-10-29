#ifndef FRAMEEDITMILKRECEPTION_H
#define FRAMEEDITMILKRECEPTION_H

#include "dbconstants.h"
// Qt
#include <QFrame>

namespace Ui {
class FrameEditMilkReception;
}
class MainWindow;
class SortFilterMilkReceptionTable;
DB_BEGIN_NAMESPACE
    class LocalitiesTable;
    class DeliverersTable;
    class MilkPointsTable;
    class MilkReceptionTable;
DB_END_NAMESPACE


class FrameEditMilkReception : public QFrame
{
    Q_OBJECT

public:
    explicit FrameEditMilkReception(QWidget *parent = 0);
    ~FrameEditMilkReception();

    void setMainWindow(MainWindow *mainWindow);
    void setup();

private:
    Ui::FrameEditMilkReception *ui;

    MainWindow *m_mainWindow;
    DB_NAMESPACE::LocalitiesTable *localities;
    DB_NAMESPACE::DeliverersTable *deliverers;
    DB_NAMESPACE::MilkPointsTable *milkPoints;
    DB_NAMESPACE::MilkReceptionTable *milkReception;
    SortFilterMilkReceptionTable *m_proxy;

private slots:
    void chooseDeliverer();
    void chooseMilkPoint();
    void chooseDates();
    void removeChoosenItems();
};

#endif // FRAMEEDITMILKRECEPTION_H
