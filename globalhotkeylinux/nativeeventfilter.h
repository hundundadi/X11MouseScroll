#ifndef NATIVEEVENTFILTER_H
#define NATIVEEVENTFILTER_H

#include <QDebug>
#include <QObject>
#include <QAbstractNativeEventFilter>
#include <QVector>
#include <QProcess>


#include <QX11Info>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xlibint.h>
#include <X11/Xresource.h>
#include <X11/Xutil.h>
#include <X11/cursorfont.h>
#include <X11/extensions/XTest.h>
#include <X11/extensions/Xfixes.h>
#include <X11/extensions/record.h>
#include <X11/keysym.h>
#include <X11/keysymdef.h>

#include <X11/XKBlib.h>
#include <X11/Xatom.h>
#include <X11/extensions/Xinerama.h>
#include <X11/cursorfont.h>

#include <dlfcn.h>
#include <xcb/xcb.h>


typedef struct charcodemap {
    wchar_t key; /** the letter for this key, like 'a' */
    KeyCode code; /** the keycode that this key is on */
    KeySym symbol; /** the symbol representing this key */
    int group; /** the keyboard group that has this key in it */
    int modmask; /** the modifiers to apply when sending this key */
    /** if this key need to be bound at runtime because it does not
     * exist in the current keymap, this will be set to 1. */
    int needs_binding;
} charcodemap_t;

class NativeEventFilter : public QObject, public QAbstractNativeEventFilter
{
    Q_OBJECT


    /**
     * @internal
     * Map character to whatever information we need to be able to send
     * this key (keycode, modifiers, group, etc)
     */
public:
    explicit NativeEventFilter(QObject *parent = 0);

    // переопределяем метод nativeEventFilter
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result);
    void setShortcut();     // Добавляем метод установки хоткея
    void unsetShortcut();   // и метод удаления хоткея для полноты картины
    void mouseClick(Display *display, int button);
    int xdo_get_active_modifiers1(Display *display, charcodemap_t **keys, int *nkeys);
    unsigned int xdo_get_input_state1(Display *display);
    void xdo_get_mouse_location3(Display *xdpy, int *x_ret, int *y_ret,
                                 int *screen_num_ret, Window *window_ret);
    int xdo_find_window_client(Display *xdpy, Window window, Window *window_ret,
                               int direction) ;
    unsigned char *xdo_get_window_property_by_atom(Display *xdpy, Window window, Atom atom,
                                                   long *nitems, Atom *type, int *size);
    void setConnection(void *connection);
signals:
    void activated();       // Сигнал активации хоткея

    void showTestWindow(int x, int y);
    void hideTestWindwo();

public slots:

public:
    QProcess m_process;
    xcb_connection_t *s_con = nullptr;
    Display *m_display; // Соединение с сервером X11

};

#endif // NATIVEEVENTFILTER_H
