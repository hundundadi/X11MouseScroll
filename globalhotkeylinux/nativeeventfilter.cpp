#include "nativeeventfilter.h"

namespace {

QVector<quint32> maskModifiers()
{
    return QVector<quint32>()
           << 0 << Mod2Mask << LockMask << (Mod2Mask | LockMask);
}
} // namespace



NativeEventFilter::NativeEventFilter(QObject *parent) : QObject(parent)
{
//    m_display = XOpenDisplay(nullptr);
//    if (m_display == NULL) {
//        /* Can't use _xdo_eprintf yet ... */
//        qDebug() << (stderr, "Error: Can't open display\n");
//    }
    m_display = QX11Info::display(); // Создадим подключение к серверу建立服务器连接
}

void print_modifiers(uint32_t mask)
{
    const char **mod,
          *mods[] = {"Shift",   "Lock",    "Ctrl",   "Alt",     "Mod2",
                     "Mod3",    "Mod4",    "Mod5",   "Button1", "Button2",
                     "Button3", "Button4", "Button5"
                    };
    printf("Modifier mask: ");
    for (mod = mods; mask; mask >>= 1, mod++)
        if (mask & 1)
            printf(*mod);
    putchar('\n');
}


bool NativeEventFilter::nativeEventFilter(const QByteArray &eventType,
                                          void *message, long *result)
{
    Q_UNUSED(eventType)
    Q_UNUSED(result)

    QStringList args;
    args.append("getmouselocation");
    m_process.start("xdotool", args);
    // 等待进程结束
    m_process.waitForFinished();
    m_process.waitForReadyRead();
    QString str_output = m_process.readAllStandardOutput();
    m_process.close();
    Window tempWin = 0;
    int tempX = 0, tempY = 0;
    if (str_output.contains("window")) {
        QStringList str_list = str_output.split(":");
//        for (int i = 0; i < str_list.length(); i++) {
//            qDebug() << "str_list[" << i << "]: " << str_list[i];
//        }
        tempX = str_list[1].left(str_list[1].length() - 2).toInt();
        tempY = str_list[2].left(str_list[2].length() - 7).toInt();
        QString str = str_list[str_list.length() - 1];
        str = str.left(str.length() - 1);
        tempWin = str.toULong();
    }
//    qDebug() << "tempWin: " << tempWin;
//    qDebug() << "tempX: " << tempX;
//    qDebug() << "tempY: " << tempY;

    if (eventType == "xcb_generic_event_t") {
        // кастуем сообщение собственно в xcb событие  消息本身就是xcb事件。
        xcb_generic_event_t *event = static_cast<xcb_generic_event_t *>(message);
        switch (event->response_type & ~0x80) {
        case XCB_BUTTON_PRESS: { // XCB_BUTTON_PRESS = 4
            xcb_button_press_event_t *ev = (xcb_button_press_event_t *)event;
            qDebug() << "======= Button" << ev->detail << " start press! =======";
            qDebug() << "str_output: " << str_output;

//            qDebug() << "ev->child : " << ev->child;
//            qDebug() << "ev->response_type : " << ev->response_type;
//            qDebug() << "ev->detail : " << ev->detail;
//            qDebug() << "ev->sequence : " << ev->sequence;
//            qDebug() << "ev->time : " << ev->time;
//            qDebug() << "ev->root : " << ev->root;
//            qDebug() << "ev->event : " << ev->event;
//            qDebug() << "ev->root_x : " << ev->root_x;
//            qDebug() << "ev->root_y : " << ev->root_y;
//            qDebug() << "ev->event_x : " << ev->event_x;
//            qDebug() << "ev->event_y : " << ev->event_y;
//            qDebug() << "ev->state : " << ev->state;
//            qDebug() << "ev->same_screen : " << ev->same_screen;
//            qDebug() << "ev->pad0 : " << ev->pad0;
            //鼠标滚轮事件4：鼠标滚轮上滑动 5：鼠标滚轮下滑动
            if (ev->detail == Button4) {
                qDebug() << "鼠标滚轮在窗口 : " << ev->event;
                qDebug() << "移动到坐标 : " << ev->event_x << "," << ev->event_y;
//                unsetShortcut();
//                int ret = 0;
//                int screen = 0;
//                XButtonEvent xbpe;
//                charcodemap_t *active_mod;
//                int active_mod_n;
//                Window window = tempWin;
//                int is_press = 1;
//                int button = Button4;
//                xdo_get_mouse_location3(m_display, &xbpe.x_root, &xbpe.y_root, &screen, NULL);
//                xdo_get_active_modifiers1(m_display, &active_mod, &active_mod_n);

//                xbpe.window = window;
//                xbpe.button = button;
//                xbpe.display = m_display;
//                xbpe.root = RootWindow(m_display, screen);
//                xbpe.same_screen = True;
//                xbpe.state = xdo_get_input_state1(m_display);
//                xbpe.subwindow = None;
//                xbpe.time = CurrentTime;
//                xbpe.type = (is_press ? ButtonPress : ButtonRelease);

//                /* Get the coordinates of the cursor relative to xbpe.window and also find what
//                 * subwindow it might be on */
//                //获取光标相对于xbpe窗口的坐标。并找到它可能打开的子窗口
//                XTranslateCoordinates(m_display, xbpe.root, xbpe.window,
//                                      xbpe.x_root, xbpe.y_root, &xbpe.x, &xbpe.y, &xbpe.subwindow);

//                xbpe.x = tempX;
//                xbpe.y = tempY;
//                xbpe.send_event = true;
//                /* Normal behavior of 'mouse up' is that the modifier mask includes
//                 * 'ButtonNMotionMask' where N is the button being released. This works the
//                 * same way with keys, too. */
//                if (!is_press) { /* is mouse up */
//                    switch (button) {
//                    case 1: xbpe.state |= Button1MotionMask; break;
//                    case 2: xbpe.state |= Button2MotionMask; break;
//                    case 3: xbpe.state |= Button3MotionMask; break;
//                    case 4: xbpe.state |= Button4MotionMask; break;
//                    case 5: xbpe.state |= Button5MotionMask; break;
//                    }
//                }
//                qDebug() << "Button4 >> xbpe.type: " << xbpe.type;
//                qDebug() << "Button4 >> xbpe.serial: " << xbpe.serial;
//                qDebug() << "Button4 >> xbpe.send_event: " << xbpe.send_event;
//                qDebug() << "Button4 >> xbpe.display: " << xbpe.display;
//                qDebug() << "Button4 >> xbpe.window: " << xbpe.window;
//                qDebug() << "Button4 >> xbpe.root: " << xbpe.root;
//                qDebug() << "Button4 >> xbpe.subwindow: " << xbpe.subwindow;
//                qDebug() << "Button4 >> xbpe.time: " << xbpe.time;
//                qDebug() << "Button4 >> xbpe.x: " << xbpe.x;
//                qDebug() << "Button4 >> xbpe.y: " << xbpe.y;
//                qDebug() << "Button4 >> xbpe.x_root: " << xbpe.x_root;
//                qDebug() << "Button4 >> xbpe.y_root: " << xbpe.y_root;
//                qDebug() << "Button4 >> xbpe.state: " << xbpe.state;
//                qDebug() << "Button4 >> xbpe.button: " << xbpe.button;
//                qDebug() << "Button4 >> xbpe.same_screen: " << xbpe.same_screen;
//                ret = XSendEvent(m_display, window, True, ButtonPressMask, (XEvent *)&xbpe);
//                XFlush(m_display);
//                free(active_mod);

            } else if (ev->detail == Button5) {
//                qDebug() << "鼠标滚轮在窗口 : " << ev->event;
//                qDebug() << "移动到坐标 : " << ev->event_x << "," << ev->event_y;
//                int ret = 0;
//                int screen = 0;
//                XButtonEvent xbpe;
//                charcodemap_t *active_mod;
//                int active_mod_n;
//                Window window = tempWin;
//                int is_press = 1;
//                int button = Button5;
//                xdo_get_mouse_location3(m_display, &xbpe.x_root, &xbpe.y_root, &screen, NULL);
//                xdo_get_active_modifiers1(m_display, &active_mod, &active_mod_n);

//                qDebug() << "1 >> window: " << window;

//                xbpe.window = window;
//                xbpe.button = button;
//                xbpe.display = m_display;
//                xbpe.root = RootWindow(m_display, screen);
//                xbpe.same_screen = True;
//                xbpe.state = xdo_get_input_state1(m_display);
//                xbpe.subwindow = None;
//                xbpe.time = CurrentTime;
//                xbpe.type = (is_press ? ButtonPress : ButtonRelease);

//                /* Get the coordinates of the cursor relative to xbpe.window and also find what
//                 * subwindow it might be on */
//                //获取光标相对于xbpe窗口的坐标。并找到它可能打开的子窗口
//                XTranslateCoordinates(m_display, xbpe.root, xbpe.window,
//                                      xbpe.x_root, xbpe.y_root, &xbpe.x, &xbpe.y, &xbpe.subwindow);

//                xbpe.x = tempX;
//                xbpe.y = tempY;
//                xbpe.send_event = true;
//                /* Normal behavior of 'mouse up' is that the modifier mask includes
//                 * 'ButtonNMotionMask' where N is the button being released. This works the
//                 * same way with keys, too. */
//                if (!is_press) { /* is mouse up */
//                    switch (button) {
//                    case 1: xbpe.state |= Button1MotionMask; break;
//                    case 2: xbpe.state |= Button2MotionMask; break;
//                    case 3: xbpe.state |= Button3MotionMask; break;
//                    case 4: xbpe.state |= Button4MotionMask; break;
//                    case 5: xbpe.state |= Button5MotionMask; break;
//                    }
//                }
//                qDebug() << "Button5 >> xbpe.type: " << xbpe.type;
//                qDebug() << "Button5 >> xbpe.serial: " << xbpe.serial;
//                qDebug() << "Button5 >> xbpe.send_event: " << xbpe.send_event;
//                qDebug() << "Button5 >> xbpe.display: " << xbpe.display;
//                qDebug() << "Button5 >> xbpe.window: " << xbpe.window;
//                qDebug() << "Button5 >> xbpe.root: " << xbpe.root;
//                qDebug() << "Button5 >> xbpe.subwindow: " << xbpe.subwindow;
//                qDebug() << "Button5 >> xbpe.time: " << xbpe.time;
//                qDebug() << "Button5 >> xbpe.x: " << xbpe.x;
//                qDebug() << "Button5 >> xbpe.y: " << xbpe.y;
//                qDebug() << "Button5 >> xbpe.x_root: " << xbpe.x_root;
//                qDebug() << "Button5 >> xbpe.y_root: " << xbpe.y_root;
//                qDebug() << "Button5 >> xbpe.state: " << xbpe.state;
//                qDebug() << "Button5 >> xbpe.button: " << xbpe.button;
//                qDebug() << "Button5 >> xbpe.same_screen: " << xbpe.same_screen;
//                ret = XSendEvent(m_display, window, True, ButtonPressMask, (XEvent *)&xbpe);
//                XFlush(m_display);
//                free(active_mod);
            } else if (ev->detail == Button1) {
                qDebug() << "Button1 pressed in window "
                         << ev->event << ", at coordinates " << ev->event_x
                         << ev->event_y;
                setShortcut();
                //mouseClick(m_display, Button1);

            } else if (ev->detail == Button2) {
                qDebug() << "Button2 pressed in window "
                         << ev->event << ", at coordinates " << ev->event_x
                         << ev->event_y;
                setShortcut();
            } else if (ev->detail == Button3) {
                qDebug() << "Button3 pressed in window "
                         << ev->event << ", at coordinates " << ev->event_x
                         << ev->event_y;
//                mouseClick(m_display, Button3);

                setShortcut();
            }
            qDebug() << "======= Button" << ev->detail << " end press! =======";

            break;
        }
        case XCB_BUTTON_RELEASE: { // XCB_BUTTON_RELEASE 5
            xcb_button_release_event_t *ev = (xcb_button_release_event_t *)event;
            qDebug() << "======= Button" << ev->detail << " start release! =======";
            //鼠标滚轮事件4：鼠标滚轮上滑动 5：鼠标滚轮下滑动
            if (ev->detail == Button4) {
                qDebug() << "鼠标滚轮在窗口 : " << ev->event;
                qDebug() << "移动到坐标 : " << ev->event_x << "," << ev->event_y;

                int ret = 0;
                int screen = 0;
                XButtonEvent xbpe;
                charcodemap_t *active_mod;
                int active_mod_n;

                Window window = tempWin;
                int is_press = 0;
                int button = Button4;
                xdo_get_mouse_location3(m_display, &xbpe.x_root, &xbpe.y_root, &screen, NULL);
                xdo_get_active_modifiers1(m_display, &active_mod, &active_mod_n);
                xbpe.window = window;
                xbpe.button = button;
                xbpe.display = m_display;
                xbpe.root = RootWindow(m_display, screen);
                xbpe.same_screen = True;
                xbpe.state = xdo_get_input_state1(m_display);
                xbpe.subwindow = None;
                xbpe.time = CurrentTime;
                xbpe.type = (is_press ? ButtonPress : ButtonRelease);

                /* Get the coordinates of the cursor relative to xbpe.window and also find what
                 * subwindow it might be on */
                //获取光标相对于xbpe窗口的坐标。并找到它可能打开的子窗口
                XTranslateCoordinates(m_display, xbpe.root, xbpe.window,
                                      xbpe.x_root, xbpe.y_root, &xbpe.x, &xbpe.y, &xbpe.subwindow);
                xbpe.x = tempX;
                xbpe.y = tempY;
                xbpe.send_event = true;
                /* Normal behavior of 'mouse up' is that the modifier mask includes
                 * 'ButtonNMotionMask' where N is the button being released. This works the
                 * same way with keys, too. */
                if (!is_press) { /* is mouse up */
                    switch (button) {
                    case 1: xbpe.state |= Button1MotionMask; break;
                    case 2: xbpe.state |= Button2MotionMask; break;
                    case 3: xbpe.state |= Button3MotionMask; break;
                    case 4: xbpe.state |= Button4MotionMask; break;
                    case 5: xbpe.state |= Button5MotionMask; break;
                    }
                }
                qDebug() << "Button4 >> xbpe.type: " << xbpe.type;
                qDebug() << "Button4 >> xbpe.serial: " << xbpe.serial;
                qDebug() << "Button4 >> xbpe.send_event: " << xbpe.send_event;
                qDebug() << "Button4 >> xbpe.display: " << xbpe.display;
                qDebug() << "Button4 >> xbpe.window: " << xbpe.window;
                qDebug() << "Button4 >> xbpe.root: " << xbpe.root;
                qDebug() << "Button4 >> xbpe.subwindow: " << xbpe.subwindow;
                qDebug() << "Button4 >> xbpe.time: " << xbpe.time;
                qDebug() << "Button4 >> xbpe.x: " << xbpe.x;
                qDebug() << "Button4 >> xbpe.y: " << xbpe.y;
                qDebug() << "Button4 >> xbpe.x_root: " << xbpe.x_root;
                qDebug() << "Button4 >> xbpe.y_root: " << xbpe.y_root;
                qDebug() << "Button4 >> xbpe.state: " << xbpe.state;
                qDebug() << "Button4 >> xbpe.button: " << xbpe.button;
                qDebug() << "Button4 >> xbpe.same_screen: " << xbpe.same_screen;
                ret = XSendEvent(m_display, window, True, ButtonReleaseMask, (XEvent *)&xbpe);
                XFlush(m_display);
                free(active_mod);

            } else if (ev->detail == Button5) {
                qDebug() << "鼠标滚轮在窗口 : " << ev->event;
                qDebug() << "移动到坐标 : " << ev->event_x << "," << ev->event_y;
                int ret = 0;
                int screen = 0;
                XButtonEvent xbpe;
                charcodemap_t *active_mod;
                int active_mod_n;
                Window window = tempWin;
                int is_press = 0;
                int button = Button5;
                xdo_get_mouse_location3(m_display, &xbpe.x_root, &xbpe.y_root, &screen, NULL);
                xdo_get_active_modifiers1(m_display, &active_mod, &active_mod_n);

                qDebug() << "1 >> window: " << window;

                xbpe.window = window;
                xbpe.button = button;
                xbpe.display = m_display;
                xbpe.root = RootWindow(m_display, screen);
                xbpe.same_screen = True;
                xbpe.state = xdo_get_input_state1(m_display);
                xbpe.subwindow = None;
                xbpe.time = CurrentTime;
                xbpe.type = (is_press ? ButtonPress : ButtonRelease);

                /* Get the coordinates of the cursor relative to xbpe.window and also find what
                 * subwindow it might be on */
                //获取光标相对于xbpe窗口的坐标。并找到它可能打开的子窗口
                XTranslateCoordinates(m_display, xbpe.root, xbpe.window,
                                      xbpe.x_root, xbpe.y_root, &xbpe.x, &xbpe.y, &xbpe.subwindow);

                xbpe.x = tempX;
                xbpe.y = tempY;
                xbpe.send_event = true;
                /* Normal behavior of 'mouse up' is that the modifier mask includes
                 * 'ButtonNMotionMask' where N is the button being released. This works the
                 * same way with keys, too. */
                if (!is_press) { /* is mouse up */
                    switch (button) {
                    case 1: xbpe.state |= Button1MotionMask; break;
                    case 2: xbpe.state |= Button2MotionMask; break;
                    case 3: xbpe.state |= Button3MotionMask; break;
                    case 4: xbpe.state |= Button4MotionMask; break;
                    case 5: xbpe.state |= Button5MotionMask; break;
                    }
                }
                qDebug() << "Button5 >> xbpe.type: " << xbpe.type;
                qDebug() << "Button5 >> xbpe.serial: " << xbpe.serial;
                qDebug() << "Button5 >> xbpe.send_event: " << xbpe.send_event;
                qDebug() << "Button5 >> xbpe.display: " << xbpe.display;
                qDebug() << "Button5 >> xbpe.window: " << xbpe.window;
                qDebug() << "Button5 >> xbpe.root: " << xbpe.root;
                qDebug() << "Button5 >> xbpe.subwindow: " << xbpe.subwindow;
                qDebug() << "Button5 >> xbpe.time: " << xbpe.time;
                qDebug() << "Button5 >> xbpe.x: " << xbpe.x;
                qDebug() << "Button5 >> xbpe.y: " << xbpe.y;
                qDebug() << "Button5 >> xbpe.x_root: " << xbpe.x_root;
                qDebug() << "Button5 >> xbpe.y_root: " << xbpe.y_root;
                qDebug() << "Button5 >> xbpe.state: " << xbpe.state;
                qDebug() << "Button5 >> xbpe.button: " << xbpe.button;
                qDebug() << "Button5 >> xbpe.same_screen: " << xbpe.same_screen;
                ret = XSendEvent(m_display, window, True, ButtonReleaseMask, (XEvent *)&xbpe);
                XFlush(m_display);
                free(active_mod);
            } else if (ev->detail == Button1) {
                qDebug() << "Button1 pressed in window "
                         << ev->event << ", at coordinates " << ev->event_x
                         << ev->event_y;
//                setShortcut();

            } else if (ev->detail == Button2) {
                qDebug() << "Button2 pressed in window "
                         << ev->event << ", at coordinates " << ev->event_x
                         << ev->event_y;
//                setShortcut();
            } else if (ev->detail == Button3) {
                qDebug() << "Button3 pressed in window "
                         << ev->event << ", at coordinates " << ev->event_x
                         << ev->event_y;
//                mouseClick(m_display, Button3);
//                setShortcut();
            }
            qDebug() << "======= Button" << ev->detail << " end release! =======";

            break;
        }
        default:
            /* Unknown event type, ignore it */
            //qDebug() << "未知的事件: " << event->response_type;
//            setShortcut();

            break;
        }
        return false;
    }
}

void NativeEventFilter::setShortcut()
{
    int g = XGrabPointer(m_display, DefaultRootWindow(m_display), true,
                         ButtonPressMask |
                         ButtonReleaseMask, GrabModeAsync,
                         GrabModeAsync, None, None, CurrentTime);

    return;

    unsetShortcut(); /* Вначале для перестраховки отключим предполагаемый хоткей,
                    * даже несмотря на то, что будет мусор в первый раз в
                    * параметрах хоткея.
                    * */
}

void NativeEventFilter::unsetShortcut()
{
    int g = XUngrabPointer(m_display, CurrentTime);
}

void NativeEventFilter::mouseClick(Display *display, int button)
{
    XEvent event;

    if (display == NULL) {

        qDebug() << ("Errore nell'apertura del Display !!!\n");
        return;
    }

    memset(&event, 0x00, sizeof(event));

    event.type = ButtonPress;
    event.xbutton.button = button;
    event.xbutton.same_screen = True;

    XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

    event.xbutton.subwindow = event.xbutton.window;

    qDebug() << "3 >> event.type: " << event.type;
    qDebug() << "3 >> event.xbutton.button: " << event.xbutton.button;
    qDebug() << "3 >> event.xbutton.same_screen: " << event.xbutton.same_screen;
    qDebug() << "3 >> event.xbutton.root: " << event.xbutton.root;
    qDebug() << "3 >> event.xbutton.window: " << event.xbutton.window;
    qDebug() << "3 >> event.xbutton.x_root: " << event.xbutton.x_root;
    qDebug() << "3 >> event.xbutton.y_root: " << event.xbutton.y_root;
    qDebug() << "3 >> event.xbutton.x: " << event.xbutton.x;
    qDebug() << "3 >> event.xbutton.y: " << event.xbutton.y;
    qDebug() << "3 >> event.xbutton.state: " << event.xbutton.state;
    qDebug() << "3 >> event.xbutton.subwindow: " << event.xbutton.subwindow;
    event.xbutton.state = 0x1000;

    while (event.xbutton.subwindow) {
        event.xbutton.window = event.xbutton.subwindow;

        XQueryPointer(display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    }

    if (XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) {
        qDebug() << ("Errore nell'invio dell'evento !!!\n");
    }
    XFlush(display);
    event.type = ButtonRelease;
    event.xbutton.state = 0x100;
    qDebug() << "4 >> event.type: " << event.type;

    qDebug() << "4 >> event.xbutton.button: " << event.xbutton.button;
    qDebug() << "4 >> event.xbutton.same_screen: " << event.xbutton.same_screen;
    qDebug() << "4 >> event.xbutton.root: " << event.xbutton.root;
    qDebug() << "4 >> event.xbutton.window: " << event.xbutton.window;
    qDebug() << "4 >> event.xbutton.x_root: " << event.xbutton.x_root;
    qDebug() << "4 >> event.xbutton.y_root: " << event.xbutton.y_root;
    qDebug() << "4 >> event.xbutton.x: " << event.xbutton.x;
    qDebug() << "4 >> event.xbutton.y: " << event.xbutton.y;
    qDebug() << "4 >> event.xbutton.state: " << event.xbutton.state;
    qDebug() << "4 >> event.xbutton.subwindow: " << event.xbutton.subwindow;

    if (XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) {
        qDebug() << ("Errore nell'invio dell'evento !!!\n");
    }

    XFlush(display);

    //    XCloseDisplay(display);
}

//保留
void NativeEventFilter::xdo_get_mouse_location3(Display *xdpy, int *x_ret, int *y_ret, int *screen_num_ret, Window *window_ret)
{
    int ret = False;
    int x = 0, y = 0, screen_num = 0;
    int i = 0;
    Window window = 0;
    Window root = 0;
    int dummy_int = 0;
    unsigned int dummy_uint = 0;
    int screencount = ScreenCount(xdpy);

    for (i = 0; i < screencount; i++) {
        Screen *screen = ScreenOfDisplay(xdpy, i);
        ret = XQueryPointer(xdpy, RootWindowOfScreen(screen),
                            &root, &window,
                            &x, &y, &dummy_int, &dummy_int, &dummy_uint);
        if (ret == True) {
            screen_num = i;
            break;
        }
    }
    //printf("mouseloc root: %ld\n", root);
    //printf("mouseloc window: %ld\n", window);

    if (ret == True) {
        if (x_ret != NULL) *x_ret = x;
        if (y_ret != NULL) *y_ret = y;
        if (screen_num_ret != NULL) *screen_num_ret = screen_num;
        if (window_ret != NULL) *window_ret = window;
    }
    if (window_ret != NULL) {
        /* Find the client window if we are not root. */
        if (window != root && window != 0) {
            int findret;
            Window client = 0;

            /* Search up the stack for a client window for this window */
            findret = xdo_find_window_client(xdpy, window, &client, 0);
            if (findret == 1) {
                /* If no client found, search down the stack */
                findret = xdo_find_window_client(xdpy, window, &client, 1);
            }
            //fprintf(stderr, "%ld, %ld, %ld, %d\n", window, root, client, findret);
            if (findret == 0) {
                window = client;
            }
        } else {
            window = root;
        }
    }
}

int NativeEventFilter::xdo_find_window_client(Display *xdpy, Window window, Window *window_ret, int direction)
{
    /* for XQueryTree */
    Window dummy, parent, *children = NULL;
    unsigned int nchildren;
    Atom atom_wmstate = XInternAtom(xdpy, "WM_STATE", False);

    int done = False;
    while (!done) {
        if (window == 0) {
            return 1;
        }

        long items;
        xdo_get_window_property_by_atom(xdpy, window, atom_wmstate, &items, NULL, NULL);

        if (items == 0) {
            /* This window doesn't have WM_STATE property, keep searching. */
            XQueryTree(xdpy, window, &dummy, &parent, &children, &nchildren);

            if (direction == 0) {
                /* Don't care about the children, but we still need to free them */
                if (children != NULL)
                    XFree(children);
                window = parent;
            } else if (direction == 1) {
                unsigned int i = 0;
                int ret;
                done = True; /* recursion should end us */
                for (i = 0; i < nchildren; i++) {
                    ret = xdo_find_window_client(xdpy, children[i], &window, direction);
                    //fprintf(stderr, "findclient: %ld\n", window);
                    if (ret == 0) {
                        *window_ret = window;
                        break;
                    }
                }
                if (nchildren == 0) {
                    return 1;
                }
                if (children != NULL)
                    XFree(children);
            } else {
                fprintf(stderr, "Invalid find_client direction (%d)\n", direction);
                *window_ret = 0;
                if (children != NULL)
                    XFree(children);
                return 1;
            }
        } else {
            *window_ret = window;
            done = True;
        }
    }
    return 0;
}

unsigned char *NativeEventFilter::xdo_get_window_property_by_atom(Display *xdpy, Window window, Atom atom, long *nitems, Atom *type, int *size)
{
    Atom actual_type;
    int actual_format;
    unsigned long _nitems;
    /*unsigned long nbytes;*/
    unsigned long bytes_after; /* unused */
    unsigned char *prop;
    int status;

    status = XGetWindowProperty(xdpy, window, atom, 0, (~0L),
                                False, AnyPropertyType, &actual_type,
                                &actual_format, &_nitems, &bytes_after,
                                &prop);
    if (status == BadWindow) {
        fprintf(stderr, "window id # 0x%lx does not exists!", window);
        return NULL;
    } if (status != Success) {
        fprintf(stderr, "XGetWindowProperty failed!");
        return NULL;
    }

    /*
     *if (actual_format == 32)
     *  nbytes = sizeof(long);
     *else if (actual_format == 16)
     *  nbytes = sizeof(short);
     *else if (actual_format == 8)
     *  nbytes = 1;
     *else if (actual_format == 0)
     *  nbytes = 0;
     */

    if (nitems != NULL) {
        *nitems = _nitems;
    }

    if (type != NULL) {
        *type = actual_type;
    }

    if (size != NULL) {
        *size = actual_format;
    }
    return prop;
}

void NativeEventFilter::setConnection(void *connection)
{
    s_con = reinterpret_cast<xcb_connection_t *>(connection);
}

//保留
int NativeEventFilter::xdo_get_active_modifiers1(Display *display, charcodemap_t **keys, int *nkeys)
{
    /* For each keyboard device, if an active key is a modifier,
     * then add the keycode to the keycode list */

    char keymap[32]; /* keycode map: 256 bits */
    int keys_size = 10;
    int keycode = 0;
    int mod_index, mod_key;
    XModifierKeymap *modifiers = XGetModifierMapping(display);
    *nkeys = 0;
    *keys = static_cast<charcodemap_t *>(malloc(keys_size * sizeof(charcodemap_t)));

    XQueryKeymap(display, keymap);

    for (mod_index = ShiftMapIndex; mod_index <= Mod5MapIndex; mod_index++) {
        for (mod_key = 0; mod_key < modifiers->max_keypermod; mod_key++) {
            keycode = modifiers->modifiermap[mod_index * modifiers->max_keypermod + mod_key];
            if (keycode && keymap[(keycode / 8)] & (1 << (keycode % 8))) {
                /* This keycode is active and is a modifier, record it. */

                /* Zero the charcodemap_t entry before using it.
                 * Fixes a bug reported by Hong-Leong Ong - where
                 * 'xdotool key --clearmodifiers ...' sometimes failed trying
                 * to clear modifiers that didn't exist since charcodemap_t's modmask was
                 * uninitialized */
                memset(*keys + *nkeys, 0, sizeof(charcodemap_t));

                (*keys)[*nkeys].code = keycode;
                (*nkeys)++;

                if (*nkeys == keys_size) {
                    keys_size *= 2;
                    *keys = static_cast<charcodemap_t * >(realloc(keys, keys_size * sizeof(charcodemap_t)));
                }
            }
        }
    }

    XFreeModifiermap(modifiers);

    return 0;
}

//保留
unsigned int NativeEventFilter::xdo_get_input_state1(Display *display)
{
    Window root, dummy;
    int root_x, root_y, win_x, win_y;
    unsigned int mask;
    root = DefaultRootWindow(display);

    XQueryPointer(display, root, &dummy, &dummy,
                  &root_x, &root_y, &win_x, &win_y, &mask);

    return mask;
}


