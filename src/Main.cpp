#include <QtGui/QApplication>
#include "MainWindow.h"
#include "RenderController.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow mw;
    RenderController rc(&mw);

    return a.exec();
}
