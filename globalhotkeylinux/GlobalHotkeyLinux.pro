#-------------------------------------------------
#
# Project created by QtCreator 2016-02-12T23:41:57
#
#-------------------------------------------------

QT       += core gui
QT       += x11extras

QT += widgets

CONFIG    += c++11
CONFIG    += link_pkgconfig
PKGCONFIG += x11
PKGCONFIG += dtkwidget
PKGCONFIG += xcb xcb-util dframeworkdbus

TARGET = GlobalHotkeyLinux
TEMPLATE = app


SOURCES +=main.cpp \
mainwindow.cpp \
nativeeventfilter.cpp \
utils.cpp \

HEADERS  += mainwindow.h \
nativeeventfilter.h \
utils.h \
LIBS += -lX11 -lXext -lXtst -lXfixes -lopencv_core -lopencv_imgproc
LIBS += -L"libprocps" -lprocps
LIBS +=  /usr/lib/x86_64-linux-gnu/libXext.so.6

FORMS    += mainwindow.ui
