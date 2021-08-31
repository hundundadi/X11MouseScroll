#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <DMainWindow>
#include <DWidget>

#include <QDebug>
#include <QMainWindow>
#include <QApplication>
#include <QMessageBox>

#include "utils.h"
#include "nativeeventfilter.h"
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void slotGlobalHotkey();

    void slotShowTestWindow(int x, int y);
    void slotHideTestWindow();

//    bool eventFilter(QObject *, QEvent *);

private:
    Ui::MainWindow *ui;
    NativeEventFilter *nativeEventFilter;
    QMainWindow *m_testWindow = new QMainWindow();

};

#endif // MAINWINDOW_H
