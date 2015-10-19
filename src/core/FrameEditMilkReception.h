#ifndef FRAMEEDITMILKRECEPTION_H
#define FRAMEEDITMILKRECEPTION_H

#include <QFrame>

namespace Ui {
class FrameEditMilkReception;
}
class MainWindow;
class SortFilterMilkReceptionTable;
class LocalitiesTable;
class DeliverersTable;
class MilkPointsTable;
class MilkReceptionTable;


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
    LocalitiesTable *localities;
    DeliverersTable *deliverers;
    MilkPointsTable *milkPoints;
    MilkReceptionTable *milkReception;
    SortFilterMilkReceptionTable *m_proxy;

private slots:
    void chooseDeliverer();
    void chooseMilkPoint();
    void chooseDates();
    void removeChoosenItems();
};

#endif // FRAMEEDITMILKRECEPTION_H
