#include "mainwindow.h"
#include <QApplication>
#include <DApplication>
#include <DMainWindow>
#include <DWidgetUtil>
DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Dtk::Widget::moveToCenter(&w);

    w.show();

    return a.exec();
}
