/*
 * Copyright (C) 2020 ~ 2021 Uniontech Software Technology Co.,Ltd.
 *
 * Author:     He MingYang <hemingyang@uniontech.com>
 *
 * Maintainer: Liu Zheng <liuzheng@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "utils.h"


//DWM_USE_NAMESPACE

void Utils::getInputEvent(const int wid, const short x, const short y, const unsigned short width, const unsigned short height)
{
    XRectangle *reponseArea = new XRectangle;
    reponseArea->x = x;
    reponseArea->y = y;
    reponseArea->width = width;
    reponseArea->height = height;
    /*
     *XShapeCombineRectangles:
     * param1:
     * param2:
     * param3:
     * param4:
     * param5:
     * param6:为NULL（参数为XRectangle*类型），那整个窗口都将被穿透
     * param7:控制设置穿透的，为0时表示设置鼠标穿透，为1时表示取消鼠标穿透，当取消设置鼠标穿透的时候，必须设置区域，
     * param8:
     * param9:
     */
    XShapeCombineRectangles(QX11Info::display(), static_cast<unsigned long>(wid), ShapeInput, 0, 0, reponseArea, 1, ShapeSubtract, YXBanded);
    delete reponseArea;

}

void Utils::cancelInputEvent(const int wid, const short x, const short y, const unsigned short width, const unsigned short height)
{
    XRectangle *reponseArea = new XRectangle;
    reponseArea->x = x;
    reponseArea->y = y;
    reponseArea->width = width;
    reponseArea->height = height;

    XShapeCombineRectangles(QX11Info::display(), static_cast<unsigned long>(wid), ShapeInput, 0, 0, reponseArea, 1, ShapeSet, YXBanded);
    delete reponseArea;

}

void Utils::cancelInputEvent1(const int wid, const short x, const short y, const unsigned short width, const unsigned short height)
{
    XRectangle *reponseArea = new XRectangle;
    reponseArea->x = x;
    reponseArea->y = y;
    reponseArea->width = width;
    reponseArea->height = height;

    XShapeCombineRectangles(QX11Info::display(), static_cast<unsigned long>(wid), ShapeInput, 0, 0, reponseArea, 0, ShapeSubtract, YXBanded);
    delete reponseArea;

}

void Utils::maskMouseEvents(const int wid)
{
    Display *dpy;
    dpy = QX11Info::display();
//    int g = XGrabPointer(dpy,DefaultRootWindow(dpy), false,
//                       ButtonPressMask
//                       ,GrabModeAsync,GrabModeAsync, None, None, CurrentTime);

    int g = XGrabPointer(dpy, static_cast<unsigned long>(wid), true,
                         ButtonPressMask
                         , GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
//   int g = XGrabButton(dpy, Button1 | Button2 | Button3 | Button4 | Button5, AnyModifier, static_cast<unsigned long>(wid), True,
//        Button1Mask | Button2Mask, GrabModeAsync, GrabModeAsync, None, None);

//    qDebug() << "GrabSuccess: " << GrabSuccess;
//    qDebug() << "g: " << g;
//    qDebug() << "DefaultRootWindow(dpy): " << DefaultRootWindow(dpy);
//    qDebug() << "wid: " << wid;

//    if (g == GrabSuccess)
//        qDebug() << "GrabSuccess: " << __func__;
//    if (g == GrabNotViewable)
//        qDebug() << "GrabNotViewable: " << __func__;
//    if (g == AlreadyGrabbed)
//        qDebug() << "AlreadyGrabbed: " << __func__;
//    if (g == GrabFrozen)
//        qDebug() << "GrabFrozen: " << __func__;
//    if (g == GrabInvalidTime)
//        qDebug() << "GrabInvalidTime: " << __func__;

//    xcb_connection_t* m_xcbConn = xcb_connect(NULL, NULL);

//    auto cookie = xcb_grab_pointer(m_xcbConn,             /* display */
//                                   1,                     /* owner_events */
//                                   static_cast<unsigned long>(wid),                 /* grab_window */
//                                   0,                     /* event_mask */
//                                   XCB_GRAB_MODE_ASYNC,   /* pointer_mode */
//                                   XCB_GRAB_MODE_ASYNC,   /* keyboard_mode */
//                                   static_cast<unsigned long>(wid),                 /* confine_to */
//                                   XCB_NONE,              /* cursor */
//                                   XCB_CURRENT_TIME       /* time */
//                                   );
//    xcb_flush(m_xcbConn);

//    xcb_generic_error_t *e = nullptr;

//    //事件处理
//    XEvent  ev;
//    int k = 0;
//    static const char *event_names[] = {
//        "", "", "KeyPress", "KeyRelease", "ButtonPress", "ButtonRelease",
//        "MotionNotify", "EnterNotify", "LeaveNotify", "FocusIn", "FocusOut",
//        "KeymapNotify", "Expose", "GraphicsExpose", "NoExpose", "VisibilityNotify",
//        "CreateNotify", "DestroyNotify", "UnmapNotify", "MapNotify", "MapRequest",
//        "ReparentNotify", "ConfigureNotify", "ConfigureRequest", "GravityNotify",
//        "ResizeRequest", "CirculateNotify", "CirculateRequest", "PropertyNotify",
//        "SelectionClear", "SelectionRequest", "SelectionNotify", "ColormapNotify",
//        "ClientMessage", "MappingNotify"
//    };
//    for (;;) {
//        XNextEvent(dpy, &ev);
//        if (ev.xbutton.button == Button1) {
//            fprintf(stderr,
//                    "%04d: BLOCK!     %-18s %d\n",
//                    k++, event_names[ev.type],
//                    ev.xbutton.button);
//            continue;
//        }
//        fprintf(stderr, "%04d: PASS! Work %-18s", k++, event_names[ev.type]);
//        switch (ev.type) {
//            case ButtonPress:
//            case ButtonRelease:
//                fprintf(stderr, " %d", ev.xbutton.button);
//                break;
//        }
//    }
//    putchar('\n');
//    //获取鼠标位置
//    Window root_ret;
//    Window child_ret;
//    int x_root, y_root;
//    int x_win, y_win;
//    unsigned int mask;
//    XQueryPointer(
//                dpy, DefaultRootWindow(dpy),
//                &root_ret, &child_ret,
//                &x_root, &y_root, &x_win, &y_win,
//                &mask);
//    qDebug() << "root_ret: " << root_ret;
//    qDebug() << "child_ret: " << child_ret;
//    qDebug() << "x_root: " << x_root << ",y_root: " << y_root<< ",x_win: " << x_win<< ",y_win: " << y_win;


}

void Utils::mouseClick(Display *display, int button)
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

    if (XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) {
        qDebug() << ("Errore nell'invio dell'evento !!!\n");
    }

    XFlush(display);

    XCloseDisplay(display);
}


