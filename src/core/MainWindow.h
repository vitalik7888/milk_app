#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfo>

namespace Ui {
class MainWindow;
}
class Database;
class Settings;
class QGroupBox;
class QComboBox;
class DialogSettings;


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Database *getDatabase() const;

    DialogSettings *getDialogSettings();

    Settings *getSettings() const;

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

    void showSettings();

    void chooseMainLocality();

private:
    Ui::MainWindow *ui;
    QGroupBox *m_groupBoxChooseMainLocality;
    QComboBox *m_comboBoxChooseMainLocality;

    Settings *m_settings;
    Database *database;

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
