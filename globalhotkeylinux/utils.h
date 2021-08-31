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

#ifndef UTILS_H
#define UTILS_H
#include <QDebug>
#include <QObject>
#include <QtX11Extras/QX11Info>
#include <xcb/xproto.h>
#include <X11/Xlib.h>

#include <X11/Xlibint.h>
#include <X11/extensions/shape.h>
class Utils : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief 对目标区域做穿透处理
     * @param 窗口id
     * @param 区域位置x坐标
     * @param 区域位置y坐标
     * @param 区域宽
     * @param 区域高
     */
    static void getInputEvent(const int wid, const short x, const short y, const unsigned short width, const unsigned short height);
    /**
     * @brief 取消对目标区域的穿透处理
     * @param wid  窗口id
     * @param x  区域位置x坐标
     * @param y  区域位置y坐标
     * @param width  区域宽
     * @param height  区域高
     */
    static void cancelInputEvent(const int wid, const short x, const short y, const unsigned short width, const unsigned short height);

    /**
     * @brief 取消对目标区域的穿透处理
     * @param wid  窗口id
     * @param x  区域位置x坐标
     * @param y  区域位置y坐标
     * @param width  区域宽
     * @param height  区域高
     */
    static void cancelInputEvent1(const int wid, const short x, const short y, const unsigned short width, const unsigned short height);

    /**
     * @brief 对穿透区域屏蔽鼠标事件
     * @param wid
     */
    static void maskMouseEvents(const int wid);

    void mouseClick(Display *display, int button);

};

#endif //UTILS_H
