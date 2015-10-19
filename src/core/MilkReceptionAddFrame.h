#ifndef MILKRECEPTIONADDFRAME_H
#define MILKRECEPTIONADDFRAME_H

#include <QFrame>

namespace Ui {
class MilkReceptionAddFrame;
}
class MainWindow;
class LocalitiesTable;
class DeliverersTable;
class MilkPointsTable;
class MilkReceptionTable;


class MilkReceptionAddFrame : public QFrame
{
    Q_OBJECT

    enum class ColumnType: int {
        Date = 111,
        Liters,
        Fat
    };
    enum class Columns: int {
        Date = 0,
        Liters,
        Fat
    };
public:
    explicit MilkReceptionAddFrame(QWidget *parent = 0);
    ~MilkReceptionAddFrame();

    void setup();

    void setMainWindow(MainWindow *mainWindow);

    void setPrice(const float price);
    float price() const;

private:
    Ui::MilkReceptionAddFrame *ui;

    MainWindow *m_mainWindow;
    LocalitiesTable *localities;
    DeliverersTable *deliverers;
    MilkPointsTable *milkPoints;
    MilkReceptionTable *milkReception;


private slots:
    void refresheLocalities();
    void refresheDeliverers();
    void refresheMilkPoints();

    void initAddTableWidget();
    void changeRowsCount(const int value);

    void insertReceptionMilk();
};

#endif // MILKRECEPTIONADDFRAME_H
