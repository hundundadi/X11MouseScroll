#include "mainwindow.h"

DWIDGET_USE_NAMESPACE
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMinimumSize(500, 500);
    installEventFilter(this);

    //this->setStyleSheet ("background-color: rgb(120, 120, 120);border: 1px solid black;");
    //Qt::FramelessWindowHint 生成无边框窗口
    //Qt::X11BypassWindowManagerHint 完全绕过窗口管理器。这会导致完全不受管理的无边框窗口（即，除非您手动调用QWidget::activateWindow ()，否则没有键盘输入）。
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
    this->setStyleSheet("border: 1px solid black;");
    this->setAttribute(Qt::WA_TranslucentBackground, true);

    nativeEventFilter = new NativeEventFilter(this);    // Инициализируем фильтр
    qApp->installNativeEventFilter(nativeEventFilter);  // Устанавилваем его на приложение
    // подключаем сигнал фильтра к слоту
    connect(nativeEventFilter, &NativeEventFilter::activated, this, &MainWindow::slotGlobalHotkey);
    connect(nativeEventFilter, &NativeEventFilter::showTestWindow, this, &MainWindow::slotShowTestWindow);
    connect(nativeEventFilter, &NativeEventFilter::hideTestWindwo, this, &MainWindow::slotHideTestWindow);

    DWidget *widget = new DWidget(this);
    widget->setMinimumSize(200, 200);
    widget->setStyleSheet("background-color: rgb(0, 120, 120);");
    widget->move(this->x() + this->width() / 2 - widget->width() / 2, this->y() + this->height() / 2 - widget->height() / 2);
    Utils::getInputEvent(
        static_cast<int>(this->winId()),
        static_cast<short>(widget->x()),
        static_cast<short>(widget->y()),
        static_cast<unsigned short>(widget->width()),
        static_cast<unsigned short>(widget->height()));

    nativeEventFilter->setShortcut();   // Устанавилваем хоткей

    m_testWindow->resize(500, 500);
    m_testWindow->hide();

//    nativeEventFilter->setConnection(qApp->property("x11Connection").value<void *>());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotGlobalHotkey()
{
    // И сообщаем пользователю, если он нажал нужный нам HotKey
    QMessageBox::information(this, "Global Hotkey", "Global Hotkey is worked", QMessageBox::Ok);
}

void MainWindow::slotShowTestWindow(int x, int y)
{
    m_testWindow->move(x, y);
    m_testWindow->show();

}

void MainWindow::slotHideTestWindow()
{

    m_testWindow->hide();
}

//bool MainWindow::eventFilter(QObject *, QEvent *event)
//{
//    qDebug() << "event->type():" << event->type();
//    return false;
//}
