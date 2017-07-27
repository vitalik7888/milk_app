#include "src/core/MilkCore.h"
#include "src/view/MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MilkCore core;

    MainWindow w(&core);
    w.show();

    return a.exec();
}
