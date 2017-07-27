#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "src/database/dbconstants.h"
// Qt
#include <QMainWindow>
#include <QFileInfo>

namespace Ui {
class MainWindow;
}
DB_BEGIN_NAMESPACE
    class Database;
DB_END_NAMESPACE
class MilkCore;
class Settings;
class QGroupBox;
class QComboBox;
class DialogSettings;


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(MilkCore *core, QWidget *parent = nullptr);
    ~MainWindow();

    DB_NAMESPACE::Database *database() const;

    DialogSettings *getDialogSettings();

    Settings *settings() const;

    QString getCurrentLocalityName() const;
    qlonglong getCurrentLocalityId() const;

public slots:
    void chooseDb();

    void addDeliverer();
    void addLocality();
    void addMilkPoint();
    void removeDeliverer();
    void updateDeliverer();
    void removeLocality();
    void updateLocality();
    void removeMilkPoint();
    void updateMilkPoint();

    void showUpdatePriceDialog() const;

    void showSettings();

    void chooseMainLocality();

private:
    Ui::MainWindow *ui;

    MilkCore *m_core;
    QGroupBox *m_groupBoxChooseMainLocality;
    QComboBox *m_comboBoxChooseMainLocality;

    DialogSettings *m_dialogSettings;

    void _readSettings();
    void _writeSettings();

    void addActionsToMenu();
    void addActionsToToolBars();
    void createDb();
    bool createDbFromTemplate(const QString &pathWithName);
    void openDb(const QString &dbName);
};

#endif // MAINWINDOW_H
